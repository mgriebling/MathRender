//
//  MTFont.m
//  iosMath
//
//  Created by Kostub Deshmukh on 5/18/16.
//
//  This software may be modified and distributed under the terms of the
//  MIT license. See the LICENSE file for details.
//

#import "MTFont.h"
#import "internal/MTFont+Internal.h"

@interface MTFont ()

@property (nonatomic, assign) CGFontRef defaultCGFont;
@property (nonatomic, assign) CTFontRef ctFont;
@property (nonatomic, strong) MTFontMathTable* mathTable;
@property (nonatomic, strong) NSDictionary* rawMathTable;

@end

@implementation MTFont

- (instancetype)initFontWithName:(NSString *)name size:(CGFloat)size
{
    self = [super init];
    if (self != nil) {
        // CTFontCreateWithName does not load the complete math font, it only has about half the glyphs of the full math font.
        // In particular it does not have the math italic characters which breaks our variable rendering.
        // So we first load a CGFont from the file and then convert it to a CTFont.

        NSBundle* bundle = [MTFont fontBundle];
        NSString* fontPath = [bundle pathForResource:name ofType:@"otf"];
        CGDataProviderRef fontDataProvider = CGDataProviderCreateWithFilename(fontPath.UTF8String);
        self.defaultCGFont = CGFontCreateWithDataProvider(fontDataProvider);
        CFRelease(fontDataProvider);

        self.ctFont = CTFontCreateWithGraphicsFont(self.defaultCGFont, size, nil, nil);

        NSString* mathTablePlist = [bundle pathForResource:name ofType:@"plist"];
        NSDictionary* dict = [NSDictionary dictionaryWithContentsOfFile:mathTablePlist];
        self.rawMathTable = dict;
        self.mathTable = [[MTFontMathTable alloc] initWithFont:self mathTable:_rawMathTable];
    }
    return self;
}

- (void)setDefaultCGFont:(CGFontRef)defaultCGFont
{
    if (_defaultCGFont != nil) {
        CFRelease(_defaultCGFont);
    }
    if (defaultCGFont != nil) {
        CFRetain(defaultCGFont);
    }
    _defaultCGFont = defaultCGFont;
}

- (void)setCtFont:(CTFontRef)ctFont {
    if (_ctFont != nil) {
        CFRelease(_ctFont);
    }
    if (ctFont != nil) {
        CFRetain(ctFont);
    }
    _ctFont = ctFont;
}

+ (NSBundle*) fontBundle
{
    // Uses bundle for class so that this can be access by the unit tests.
//    return [NSBundle bundleWithURL:[[NSBundle bundleForClass:[self class]] URLForResource:@"mathFonts" withExtension:@"bundle"]];
    NSBundle *cover = [NSBundle bundleWithIdentifier:@"MathRender_MathRender"];
    return [NSBundle bundleWithIdentifier:@"mathFonts"];
}

- (MTFont *)copyFontWithSize:(CGFloat)size
{
    MTFont* copyFont = [[[self class] alloc] init];
    copyFont.defaultCGFont = self.defaultCGFont;
    // Retain the font as we are adding another reference to it.
    CGFontRetain(copyFont.defaultCGFont);
    copyFont.ctFont = CTFontCreateWithGraphicsFont(self.defaultCGFont, size, nil, nil);
    copyFont.rawMathTable = self.rawMathTable;
    copyFont.mathTable = [[MTFontMathTable alloc] initWithFont:copyFont mathTable:copyFont.rawMathTable];
    return copyFont;
}

-(NSString*) getGlyphName:(CGGlyph) glyph
{
    NSString* name = CFBridgingRelease(CGFontCopyGlyphNameForGlyph(self.defaultCGFont, glyph));
    return name;
}

- (CGGlyph)getGlyphWithName:(NSString *)glyphName
{
    return CGFontGetGlyphWithGlyphName(self.defaultCGFont, (__bridge CFStringRef) glyphName);
}

- (CGFloat)fontSize
{
    return CTFontGetSize(self.ctFont);
}

- (void)dealloc
{
    self.defaultCGFont=nil;
    self.ctFont=nil;
}
@end
