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

everything except the [routine](routine) DoXyzzy and the
[code](code) that follows it, are all declarations. They
simply inform the compiler about the data used by the program or define
things. They do not actually perform any actions. The following language
commands in Hugo are declarations:

-   The [asterisk](asterisk) symbol (**\***) when used to
    define parameters to the [verb](verb) command
-   The [comment](comment) symbol, exclamation point **!**
-   The [block comment](block_comment), a group of lines
    beginning with **!\\** and ending with **\\!**
-   [attribute](attribute)
-   [constant](constant)
-   [enumerate](enumerate)
-   [global](global)
-   The [globals](globals) parameter to the
    [enumerate](enumerate) command
-   [local](local)
-   [property](property)
-   [verb](verb)

See Also: [code](code), [keywords](keywords)
