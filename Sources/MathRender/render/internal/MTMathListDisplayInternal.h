//
//  MTMathListDisplay+Internal.h
//  iosMath
//
//  Created by Kostub Deshmukh on 6/21/16.
//
//  This software may be modified and distributed under the terms of the
//  MIT license. See the LICENSE file for details.
//

#import <MTMathListDisplay.h>

@interface MTDisplay ()

@property (nonatomic) CGFloat ascent;
@property (nonatomic) CGFloat descent;
@property (nonatomic) CGFloat width;
@property (nonatomic) NSRange range;
@property (nonatomic) BOOL hasScript;

@end

// The Downshift protocol allows an MTDisplay to be shifted down by a given amount.
@protocol DownShift <NSObject>

@property (nonatomic) CGFloat shiftDown;

@end

@interface MTMathListDisplay ()

- (nonnull instancetype)init NS_UNAVAILABLE;

- (nonnull instancetype) initWithDisplays:(NSArray<MTDisplay*>*_Nonnull) displays range:(NSRange) range NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readwrite) MTLinePosition type;
@property (nonatomic, readwrite) NSUInteger index;

@end

@interface MTCTLineDisplay ()

- (nonnull instancetype)initWithString:(nonnull NSAttributedString*) attrString position:(CGPoint)position range:(NSRange) range font:(nonnull  MTFont*) font atoms:(nonnull NSArray<MTMathAtom*>*) atoms NS_DESIGNATED_INITIALIZER;

- (nonnull instancetype)init NS_UNAVAILABLE;

@end

@interface MTFractionDisplay ()

- (nonnull instancetype)initWithNumerator:(nonnull MTMathListDisplay*) numerator denominator:(nonnull MTMathListDisplay*) denominator position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

- (nonnull instancetype)init NS_UNAVAILABLE;

@property (nonatomic) CGFloat numeratorUp;
@property (nonatomic) CGFloat denominatorDown;
@property (nonatomic) CGFloat linePosition;
@property (nonatomic) CGFloat lineThickness;

@end

@interface MTRadicalDisplay ()

- (nonnull instancetype)initWitRadicand:(nonnull MTMathListDisplay*) radicand glpyh:(nonnull MTDisplay*) glyph position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

- (void) setDegree:(nonnull MTMathListDisplay *)degree fontMetrics:(nonnull MTFontMathTable*) fontMetrics;

@property (nonatomic) CGFloat topKern;
@property (nonatomic) CGFloat lineThickness;

@end

// Rendering of an large glyph as an MTDisplay
@interface MTGlyphDisplay() <DownShift>

- (nonnull instancetype)initWithGlpyh:(CGGlyph) glyph range:(NSRange) range font:(nonnull MTFont*) font NS_DESIGNATED_INITIALIZER;

@end

// Rendering of a constructed glyph as an MTDisplay
@interface MTGlyphConstructionDisplay : MTDisplay<DownShift>

- (nonnull instancetype) init NS_UNAVAILABLE;
- (nonnull instancetype) initWithGlyphs:(nonnull NSArray<NSNumber*>*) glyphs offsets:(nonnull NSArray<NSNumber*>*) offsets font:(nonnull MTFont*) font NS_DESIGNATED_INITIALIZER;

@end

@interface MTLargeOpLimitsDisplay ()

- (nonnull instancetype) initWithNucleus:(nonnull MTDisplay*) nucleus upperLimit:(nonnull MTMathListDisplay*) upperLimit lowerLimit:(nonnull MTMathListDisplay*) lowerLimit limitShift:(CGFloat) limitShift extraPadding:(CGFloat) extraPadding NS_DESIGNATED_INITIALIZER;

- (nonnull instancetype)init NS_UNAVAILABLE;

@property (nonatomic) CGFloat upperLimitGap;
@property (nonatomic) CGFloat lowerLimitGap;

@end

@interface MTLineDisplay ()

- (nonnull instancetype)initWithInner:(nonnull MTMathListDisplay*) inner position:(CGPoint) position range:(NSRange) range NS_DESIGNATED_INITIALIZER;

// How much the line should be moved up.
@property (nonatomic) CGFloat lineShiftUp;
@property (nonatomic) CGFloat lineThickness;

@end

@interface MTAccentDisplay ()

- (nonnull instancetype)initWithAccent:(nonnull MTGlyphDisplay*) glyph accentee:(nonnull MTMathListDisplay*) accentee range:(NSRange) range NS_DESIGNATED_INITIALIZER;

@end


@interface MTInnerDisplay ()

- (nonnull instancetype) initWithInner:(nonnull MTMathListDisplay*) inner leftDelimiter:(nonnull MTDisplay*) leftDelimiter rightDelimiter:(nonnull MTDisplay*) rightDelimiter atIndex:(NSUInteger) index NS_DESIGNATED_INITIALIZER;

@property (nonatomic, nullable) MTMathListDisplay* inner;

@property (nonatomic, nullable) MTDisplay* leftDelimiter;
@property (nonatomic, nullable) MTDisplay* rightDelimiter;

@property (nonatomic) NSUInteger index;

@end
