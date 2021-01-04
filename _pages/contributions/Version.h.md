---
title: version.h
permalink: /contributions/version.h/
categories: 
  - Library Contributions
---

`Version.h` is just a library-contribution version of the routines found
on the [Version](Version) page, which in turn is an adaption
of the "version.hug" file from the Future Boy! selected source. Download
it (the library contribution, that is)
[here](http://roody.gerynarsabode.org/hbe/version.h). 

## The set-up

To use `version.h`:

1.  Add the following to your [verb grammar](Grammar):
        verb "version"
        *                          DoVersion
2.  After "hugolib.h" is included, define the following constants:
        constant GAME_TITLE "Annoyotron X: Annoyotron Takes Manhatten"
        constant TITLECOLOR LIGHT_RED ! has to be a number value if defined before "hugolib.h" is included
        constant AUTHOR "Some Guy"
        constant RELEASE "1.0"  ! Game release number
        constant EMAIL "email@address.com"
        constant WEBSITE "www.somewebsite.com"

    (The only one *really* necessary is `GAME_TITLE`.)
3.  After that, [\#include](Include) "version.h".
4.  Season to taste, and serve!

## The code

    !\-----------------------------------------------------------------
    Version.h release 1.1, based on version.hug from the Future Boy!
    source code by Kent Tessman, adapted by Jon Blask

    In your game source, you'll want to define the following constants:

    constant GAME_TITLE "Annoyotron X: Annoyotron Takes Manhatten"
    constant TITLECOLOR LIGHT_RED ! has to be a number value if defined before "hugolib.h" is included
    constant AUTHOR "Some Guy"
    constant RELEASE "1.0"  ! Game release number
    constant EMAIL "email@address.com"
    constant WEBSITE "www.somewebsite.com"

    Of course, if you want the player to be able to pull up version
    info, you'll have to define a "version" verb like this:

    verb "version"
    *                          DoVersion

    -------------------------------------------------------------------\!
    #ifclear _VERSION_H
    #set _VERSION_H

    #ifset VERSIONS
    #message "Version.h Version 1.1"
    #endif

    routine GameTitle
    {
    #if defined TITLECOLOR
        color TITLECOLOR
    #endif

    #if undefined GAME_TITLE
    #message error "You need to define the TITLE constant before version.hug is
    included!"
    #endif
    #if defined GAME_TITLE
        print GAME_TITLE;
    #endif
        color TEXTCOLOR
    }

    routine DoVersion
    {
        Font(BOLD_ON | ITALIC_OFF)
        print GameTitle;
        Font(BOLD_OFF | ITALIC_OFF)
    #ifset DEMO_VERSION
        "\B (demo version)\b"
    #endif
        string(_temp_string, serial$, 8)
        print "Copyright (c) 20";
        StringPrint(_temp_string, 6, 8)
    #if defined AUTHOR
        " by ";
        print AUTHOR;
    #endif
        ""
    #if defined RELEASE
        print "Release "; RELEASE; " / ";
    #endif
    #if clear BETA
        print "Serial Number ";
        StringPrint(_temp_string, 0, 2)
        StringPrint(_temp_string, 3, 5)
        StringPrint(_temp_string, 6, 8)
    #else
        " \BBETA BUILD # 20";
        StringPrint(_temp_string, 6, 8)
        StringPrint(_temp_string, 0, 2)
        StringPrint(_temp_string, 3, 5)
        Font(BOLD_OFF)
    #endif
    ""
    print "Written in ";
    print BANNER
    #ifset BETA
    #if defined TITLECOLOR
        color TITLECOLOR
    #endif
        "\n\BDO NOT DISTRIBUTE!\b";
        color TEXTCOLOR
        " This beta release is intended for testing only, not for
        distribution to the general public.";
    #if defined EMAIL
       " Please report any errors,
        bugs, etc. to \I<";
        print EMAIL;">\i."
    #endif
        "\nHI, TESTERS:  Please type \B>SCRIPT ON\b and send in your transcripts."
    #endif
    #ifset DEMO_VERSION
    #if defined WEBSITE
        "\n(Like this demo?  Visit \B";
        print WEBSITE; "\b for the full version.)"
    #endif
    #endif
    #ifset HUGOFIX
        "\n\I(Compiled with the HugoFix Debugging Suite)\i"
    #endif
    }

    #endif  ! #ifclear _VERSION_H
