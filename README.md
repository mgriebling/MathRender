# MathRender

`MathRender` provides a Swift package interface to the guts of [iosMath](https://travis-ci.org/kostub/iosMath) 
for displaying beautifully rendered math equations in iOS and MacOS applications. It typesets formulae written 
using LaTeX in a `UILabel` equivalent class. It uses the same typesetting rules as LaTeX and
so the equations are rendered exactly as LaTeX would render them. 

`MathRender` prepackages everything needed for direct access via the Swift Package Manager.
No need for complicated alien pods that never seem to work quite right.

It is similar to [MathJax](https://www.mathjax.org) or
[KaTeX](https://github.com/Khan/KaTeX) for the web but for native iOS or MacOS
applications without having to use a `UIWebView` and Javascript. More
importantly, it is significantly faster than using a `UIWebView`.

## Examples
Here are screenshots of some formulae that were rendered with this library:

![Quadratic Formula](img/quadratic.png) 

![Calculus](img/calculus.png)

![AM-GM](img/amgm.png)

![Ramanujan Identity](img/ramanujan.png)

More examples are included in [EXAMPLES](EXAMPLES.md)
 
## Requirements
`MathRender` works on iOS 6+ or MacOS 10.8+ and requires ARC to build. It depends
on the following Apple frameworks:

* Foundation.framework
* CoreGraphics.framework
* QuartzCore.framework
* CoreText.framework

Additionally for iOS it requires:
* UIKit.framework

Additionally for MacOS it requires:
* AppKit.framework

## Installation

### Swift Package

`MathRender` is available from [MathRender](https://github.com/mgriebling/MathRender.git). 
To use it in your code, just add the https://github.com/mgriebling/MathRender.git path to
XCode's package manager.

## Usage

The library provides a class `MTMathUILabel` which is a `UIView` that
supports rendering math equations. To display an equation simply create
an `MTMathUILabel` as follows:

```swift

import MathRender

let label = MTMathUILabel()
label.latex = "x = \\frac{-b \\pm \\sqrt{b^2-4ac}}{2a}"

```
Adding `MTMathUILabel` as a sub-view of your `UIView` will render the
quadratic formula example shown above.

The following code creates a SwiftUI component called `MathView` encapsulating the MTMathUILabel:

```swift
import SwiftUI
import MathRender

struct MathView: UIViewRepresentable {

    @Binding var equation: String
    @Binding var fontSize: CGFloat
    
    func makeUIView(context: Context) -> MTMathUILabel {
        let view = MTMathUILabel()
        return view
    }
    
    func updateUIView(_ uiView: MTMathUILabel, context: Context) {
        uiView.latex = equation
        uiView.fontSize = fontSize
        uiView.font = MTFontManager().termesFont(withSize: fontSize)
        uiView.textAlignment = .right
        uiView.labelMode = .text
    }
}
```

### Included Features
This is a list of formula types that the library currently supports:

* Simple algebraic equations
* Fractions and continued fractions
* Exponents and subscripts
* Trigonometric formulae
* Square roots and n-th roots
* Calculus symbos - limits, derivatives, integrals
* Big operators (e.g. product, sum)
* Big delimiters (using \\left and \\right)
* Greek alphabet
* Combinatorics (\\binom, \\choose etc.)
* Geometry symbols (e.g. angle, congruence etc.)
* Ratios, proportions, percents
* Math spacing
* Overline and underline
* Math accents
* Matrices
* Equation alignment
* Change bold, roman, caligraphic and other font styles (\\bf, \\text, etc.)
* Most commonly used math symbols
* Colors

### Example

The [MathRenderDemo](https://github.com/mgriebling/MathRenderDemo) is a Swift version
of the Objective-C demo included in `iosMath` that uses `MathRender` as a Swift package dependency.

### Advanced configuration

`MTMathUILabel` supports some advanced configuration options:

##### Math mode

You can change the mode of the `MTMathUILabel` between Display Mode
(equivalent to `$$` or `\[` in LaTeX) and Text Mode (equivalent to `$`
or `\(` in LaTeX). The default style is Display. To switch to Text
simply:

```swift
label.labelMode = .label
```

##### Text Alignment
The default alignment of the equations is left. This can be changed to
center or right as follows:

```swift
label.textAlignment = .center
```

##### Font size
The default font-size is 25pt. You can change it as follows:

```swift
label.fontSize = 30
```
##### Font
The default font is *Latin Modern Math*. This can be changed as:

```swift
label.font = MTFontManager().termesFont(withSize:20)
```

This project has 3 fonts bundled with it, but you can use any OTF math
font.  Note: I couldn't get the `iosMath` Python script to work.

##### Color
The default color of the rendered equation is black. You can change
it to any other color as follows:

```swift
label.textColor = .red
```

It is also possible to set different colors for different parts of the
equation. Just access the `displayList` field and set the `textColor`
on the underlying displays that you want to change the color of. 

##### Custom Commands
You can define your own commands that are not already predefined. This is
similar to macros is LaTeX. To define your own command use:

```swift
MTMathAtomFactory.addLatexSymbol("lcm", value: MTMathAtomFactory.operator(withName: "lcm", limits: false))
```

This creates an `\lcm` command that can be used in the LaTeX.

##### Content Insets
The `MTMathUILabel` has `contentInsets` for finer control of placement of the
equation in relation to the view.

If you need to set it you can do as follows:

```swift
label.contentInsets = UIEdgeInsets(top: 0, left: 10, bottom: 0, right: 20)
```

##### Error handling

If the LaTeX text given to `MTMathUILabel` is
invalid or if it contains commands that aren't currently supported then
an error message will be displayed instead of the label.

This error can be programmatically retrieved as `label.error`. If you
prefer not to display anything then set:

```swift
label.displayErrorInline = true
```

## Future Enhancements

Note this is not a complete implementation of LaTeX math mode. There are
some important pieces that are missing and will be included in future
updates. This includes:

* Support for explicit big delimiters (bigl, bigr etc.)
* Addition of missing plain TeX commands 

## License

`MathRender` is available under the MIT license. See the [LICENSE](./LICENSE)
file for more info.

### Fonts
This distribution contains the following fonts. These fonts are
licensed as follows:
* Latin Modern Math: 
    [GUST Font License](GUST-FONT-LICENSE.txt)
* Tex Gyre Termes:
    [GUST Font License](GUST-FONT-LICENSE.txt)
* [XITS Math](https://github.com/khaledhosny/xits-math):
    [Open Font License](OFL.txt)
