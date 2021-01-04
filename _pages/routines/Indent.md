---
title: Indent
permalink: /routines/indent/
categories: 
  - Routines
---

`Indent` is a [hugolib.h](library/hugolib.h/) routine that prints the
number of spaces specified by the `INDENT_SIZE` constant. It is used
for- *wait, for it*- indenting text. It is called by several different
Hugo library routines, but it is likely an author will want to call it,
too.

### Options

`INDENT_SIZE` defaults to 2 spaces unless the author sets it himself (by
defining the constant before `hugolib.h` is \#include'd). Setting
`INDENT_SIZE` to `0` is an easy way to get rid of indentations in your
game, if that is what you are going for.

If you are using the `LIST_F` mask (which makes lists- like inventory-
be shown as itemized lists, not sentences) for the
[FORMAT](globals/format/) global, also setting `NOINDENT_F` will make
it so that those listed items are not indented.

### Why Indent?

You'll notice that the library's default behavior is to not indent
command responses (or location names), but things like room
descriptions, on the other hand, are. This creates a sense of "game
world vs. game parser." It is likely you want to indent text for the for
former but not the latter. Of course, this is up to you (and the issue
is complicated enough that getting rid of indentations is sometimes
appealing).

### The code

    !----------------------------------------------------------------------------
    ! Indent
    ! indents only if the NOINDENT_F bit is not set in the FORMAT mask; returns
    ! the null word "" (0 or false); if <newl> is true, a newline is printed
    ! first (if appropriate)

    routine Indent(newl)
    {
        local i

        if override_indent or display.cursor_column > 1
            print AFTER_PERIOD;
        elseif not (FORMAT & NOINDENT_F) and INDENT_SIZE
        {
            ! See display.cursor_column > 1, above
            !print newline

            if newl
                print ""
            print "_";
            for (i=2; i<=INDENT_SIZE; i++)
                print " ";
        }
        override_indent = false
    }
    