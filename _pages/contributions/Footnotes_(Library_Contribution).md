---
title: Footnotes
permalink: /contributions/footnotes/
categories: 
  - Library Contributions
---

This library contribution, inspired by the footnotes systems used in
games like Guilty Bastards and Stationfall, attempts to make footnotes
easy! Unlike those other games, this system uses a "chronological"
design- footnotes are only accessible after the prompting text has been
seen, and footnotes are numbered by the order they are seen. Compared to
the method used in [Guilty Bastards](Guilty_Bastards_Infocom-Style_Footnotes),
this system uses a footnote object (with its various aliased properties) to
keep track of states instead of arrays and globals.

Download it [here.](http://roody.gerynarsabode.org/hbe/footnotes.zip)
Now let's take a look!

## The Set-Up

To use the footnotes library extension:

1.  [\#include](Include) "footnotes.g" in your grammar and
    "footnotes.h" after "hugolib.h"
2.  Before "footnotes.h" is included, define a constant called
    MAXFOOTNOTES that tells the game how many possible footnotes there
    are:
            constant MAXFOOTNOTES 20
3.  Put the call "FootnoteNotify" in the [main](main) routine
    *after* calls to routines that might possibly print text, like
    [runevents](Events) and [RunScripts](Scripts).
4.  Add a "PrintFootnote" routine to your game, like the following:
        routine PrintFootnote(num)
        {
            select num
            case 1 : "Actually, this game was also submitted to the 2011 Hugo \
                          Comp. That's TWO comps! Crazy, right?"
            case 2 : "[ Ok, so you converse in different ways with different \
                          characters. Get over it. ]"
        }

    (The cases are the actual footnotes your game will respond with.)

## Putting Footnotes in Your Game

-   Calling Footnote(
    <case number>

    ) will automatically print "(Footnote
    <next footnote number in line>)" instantly and add

    <case number>

    from PrintFootnote to your footnote array.

<!-- -->

        Footnote(<case number>)

-   If you want the game to announce the footnote with the
    after-the-turn notification system, just call:

<!-- -->

        AddFootnote(<case number>)

-   If you want to print your own footnote announcement, print it and
    call:

<!-- -->

        AddFootnote(<case number>, 1)

That's it! You're good to go!

## Any questions?

E-mail roody.yogurt at gmail...
