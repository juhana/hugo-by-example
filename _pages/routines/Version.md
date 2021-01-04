---
title: Version
permalink: /routines/version/
categories: 
  - Routines
  - Tips
---

In most games, when you type **VERSION**, you get the same title,
author, and release info one often gets at the beginning of the game.
These routines are generic adaptions of `version.hug` from the
[Future Boy Selected Source](misc/future-boy-license/)
files for quick inclusion into games. Calling `Version` will result in
this:

>Annoyotron X: Annoyotron Takes Manhatten  
>Copyright (c) 2011 by Some Guy  
>Release 1.0 / Hugo v3.1 / Library 31031  
>Serial Number: 092211

To use, define the following [constants](basics/constants/) in your game:

    constant TITLE "Annoyotron X: Annoyotron Takes Manhatten"
    constant TITLECOLOR LIGHT_RED ! has to be a number value if defined before "hugolib.h" is included
    constant AUTHOR "Some Guy"
    constant RELEASE "1.0"  ! Game release number
    constant EMAIL "email@address.com"
    constant WEBSITE "www.somewebsite.com"

Now copy the routines themselves:

    routine GameTitle
    {
        color TITLECOLOR
        print TITLE;
        color TEXTCOLOR
    }

    routine DoVersion
    {
        Font(BOLD_ON | ITALIC_OFF)
        print GameTitle
        Font(BOLD_OFF | ITALIC_OFF)
        string(_temp_string, serial$, 8)
        print "Copyright (c) 20";
        StringPrint(_temp_string, 6, 8)
        " by ";
        print AUTHOR
        print "Release "; RELEASE; " / ";
        print BANNER
    #ifclear BETA                                 ! This routine makes serial numbers
        print "Serial Number: ";              ! without slashes,
        StringPrint(_temp_string, 0, 2)       ! in MODYYR format.
        StringPrint(_temp_string, 3, 5)
        StringPrint(_temp_string, 6, 8)
        print ""
    #endif
    #ifset BETA
        " \BBETA BUILD # 20";
        StringPrint(_temp_string, 6, 8)       ! if a BETA flag is set,
        StringPrint(_temp_string, 0, 2)       ! a build # in YEARMODY
        StringPrint(_temp_string, 3, 5)       ! format is printed.
        "\b"
    #endif
    #ifset DEMO_VERSION
        " \B(demo version)\b";
    #endif
        print " ";  ! newline

    #ifset BETA
        color TITLECOLOR
        "\n\BDO NOT DISTRIBUTE\b";
        color TEXTCOLOR
        "  This beta release is intended for testing only, not for
        distribution to the general public.  Please report any errors,
        bugs, etc. to \I<";
        print EMAIL;">\i."
        "\nHI, TESTERS:  Please type \B>SCRIPT ON\b and send in your transcripts."
    #endif
    #ifset DEMO_VERSION
        "\n(Like this demo?  Visit \B";
        print WEBSITE; "\b for the full version.)"
    #endif
    #ifset HUGOFIX
        "\n\I(Compiled with the HugoFix Debugging Suite)\i"
    #endif
    }

## Other VERSION versions

There isn't any way set in stone on how to display your title and
release information. Of course, it is expected that you mention Hugo and
the library version prominently somewhere in appreciation to the
language that Kent Tessman has written for us, but you could conceivably
move that information away from the game title, maintaining one of these
"older" styles.

In each case, we'll share some example version code and list some Hugo
code for emulating it, incorporating the constants from above.

### Infocom

>THE LURKING HORROR  
>An Interactive Horror  
>Copyright (c) 1987 by Infocom, Inc. All rights reserved.  
>THE LURKING HORROR is a trademark of Infocom, Inc.  
>Release 221 / Serial number 870918

    string(_temp_string, serial$, 10) ! write the serial to a string, to change to Infocom format
    print TITLE
    "An Interactive ..."
    "Copyright (c) 20";
    StringPrint(_temp_string, 6, 8) ! the year
    print " by "; AUTHOR ; ". All rights reserved."
    ! Since no one will actually get trademarks, we will skip this line.
    print "Release "; VERSION ; " / Serial number ";
    StringPrint(_temp_string, 6, 8)
    StringPrint(_temp_string, 0, 2)
    StringPrint(_temp_string, 3, 5)
    print newline

### Magnetic Scrolls

>&gt;version  
>Jinxter - Copyright (c) 1987 Magnetic Scrolls Ltd.  
>Version 1.05  
>&gt;
>
>&gt;version  
>Fish! Version 1.07, Copyright (c) Magnetic Scrolls Ltd 1988.

    string(_temp_string, serial$, 10)

    ! Jinxter version
    print TITLE ; " - Copyright (c) 20";
    StringPrint(_temp_string, 6, 8) ! the year
    print " "; AUTHOR ; "."
    print "Version "; RELEASE

    ! Fish! version
    print TITLE ; " Version "; RELEASE; ", Copyright (c) "; AUTHOR ; " 20";
    StringPrint(_temp_string, 6, 8) ! the year
    "."

### Other games

>Pantomime  
>Interactive Fiction  
>Copyright (c) 2006. Written and programmed by Robb Sherwin  
>Release 1.02 / Serial number 060426 / Hugo 3.1

    string(_temp_string, serial$, 10)
    print TITLE
    "Interactive Fiction"
    "Copyright (c) 20";
    StringPrint(_temp_string, 6, 8) ! the year
    print ". Written and programmed by "; AUTHOR
    print "Release "; RELEASE ; " / Serial number "; serial$ ; " / ";
    print BANNER ! it's not exactly the banner, but close enough
