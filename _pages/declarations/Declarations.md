---
title: Declarations
permalink: /declarations/
categories: 
  - Declarations
---

**Declarations** are parts of the program that tell the compiler things,
but don't actually *do* anything. In the following code snippet

    verb "xyzzy"
       *                            DoXyzzy

    attribute painted
    property color
    object table "wooden table"
    {
       is painted
       color "viridian"
    }

    routine DoXyzzy
    {
       "Nothing happens."
    }

everything except the [routine](/routines/) DoXyzzy and the
[code](/definitions/code/) that follows it, are all declarations. They
simply inform the compiler about the data used by the program or define
things. They do not actually perform any actions. The following language
commands in Hugo are declarations:

-   The [asterisk](/operators/asterisk/) symbol (**\***) when used to
    define parameters to the [verb](/declarations/verb/) command
-   The [line comment](/basics/line-comment/) symbol, exclamation point **!**
-   The [block comment](/basics/block-comment/), a group of lines
    beginning with **!\\** and ending with **\\!**
-   [attribute](/attributes/)
-   [constant](/basics/constants/)
-   [enumerate](/guts/enumerate/)
-   [global](/basics/global/)
-   The [globals](/basics/global/) parameter to the
    [enumerate](/guts/enumerate/) command
-   [local](/basics/locals/)
-   [property](/properties/)
-   [verb](/declarations/verb/)

See Also: [code](/definitions/code/), [keywords](/guts/keywords/)
