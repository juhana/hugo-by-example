---
title: Font
permalink: /input-output/font/
categories: 
  - Input-Output
---

Hugo allows some font control to enhance your text. Options include:

-   Boldface
-   Italics
-   Underline
-   Proportional Text
-   Mono-spaced Text
-   Colors

## Changing Fonts

There are two ways to change the font in your printed text, either by
using the `Font()` routine or embedding control characters in the text
itself. It is generally recommended to use the `Font()` routine over
embedded codes for readability.

### Font() routine

The `Font()` routine takes [constants](basics/constants/) (defined in
the standard library)

| Constant | Effect |
| --- | --- |
| BOLD_ON | to start **bold** text  |
| BOLD_OFF | to stop **bold** text  |
| ITALIC_ON | to start *italic* text  |
| ITALIC_OFF | to stop *italic* text  |
| UNDERLINE_ON | to start <ins>underlined</ins> text  |
| UNDERLINE_OFF | to stop <ins>underlined</ins> text |
| PROP_ON | Start `proportional` printing |
| PROP_OFF | Stop `proportional` printing |

Example:

```
...INSIDE SOME ROUTINE SOMEWHERE...
Font(BOLD_ON)
"This text will print bold, "
Font(BOLD_OFF)
"but this text will not."

! You can also combine the effects thusly
Font(BOLD_ON | UNDERLINE_ON)
"This text will print Bold AND underlined."
Font(BOLD_OFF)
"And this text will just be underlined."
Font(UNDERLINE_OFF)
"Back to normal text."
...
```

The output of this program will look something like this (for
interpreters that support it):

>**This text will print bold.**  
>But this text will not.  
><ins>**This text will print Bold AND underlined**</ins>  
><ins>And this text will just be underlined.</ins>  
>Back to normal text  
>&gt;_

### Embedded Control Codes

The following control codes are used for embedded text:

| Control Code | Effect                            |
|--------------|-----------------------------------|
| \\B          | Start **bold** text.              |
| \\b          | End **bold** text.                |
| \\I          | Start *italic* text.              |
| \\i          | End *italic* text.               |
| \\U          | Start <ins>underlined</ins> text. |
| \\u          | End <ins>underlined</ins> text.   |

Example (to match the output of the previous example):

``` numberLines
"\BThis text will print bold,\b "
"but this text will not."

! You can also combine the effects thusly
"\B\UThis text will print Bold AND underlined.\b\nAnd this text will just be underlined.\u"
! \n is the newline character
"Back to normal text."
```

## Text Colors

The [color](input-output/color/) command changes the color of the text
and/or the background. Giving only a foreground color will result in
colored text with the same background color. For example:

    color LIGHT_RED
    print "WARNING! WARNING!"
    color TEXTCOLOR ! go back to the regular text color
