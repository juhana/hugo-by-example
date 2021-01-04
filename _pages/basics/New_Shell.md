---
title: The "new shell"
permalink: /basics/new-shell/
categories: 
  - Basics
---

This is a updated version of the `shell.hug` that is available at the
main Hugo webpage (and also available at the ifarchive). It is based
both on the original shell.hug and a bit on the ScavHunt tutorial. You
can download a version of it
[here](http://roody.gerynarsabode.org/hbe/newshell.hug).

This file includes several commonly used flags and switches, making it
harder to forget to include them in your own game. It also includes a
global called [IFID](http://ifwiki.org/index.php/IFID), a unique
identifier for Interactive Fiction games. There is an easy to use IFID
generator at
[www.tads.org/ifidgen/ifidgen](http://www.tads.org/ifidgen/ifidgen).
There is also a program that's available on many linux distros that can
be used to create an IFID called *uuidgen*.

    !::^!
    ! New Game (Shell)
    !::

    !:: Flags
    !#set BETA                ! Compile with the comments-in-transcripts library
                              !   addition (requires "beta.h")
    !#set CHEAPGLK            ! Compile with cheapglk checks (requires "cheapglk.h")
    !#set GLK                 ! Compile with glk checks (requires "glk.h")
    !#set HUGOFIX             ! Compile with HugoFix Debugging Library commands
                              !   available (type $? in game)
    !#set HDX                 ! Compile as Hugo Debuggable Executable (see below for
                              !   details)
    !#set VERBSTUBS           ! Include the grammar and routines from verbstubs.g
                              !   and verbstubs.h, respectively
    !#set USE_ATTACHABLES     ! Use attachable items
    !#set USE_PLURAL_OBJECTS  ! Use plural objects
    !#set USE_VEHICLES        ! Use vehicle objects
    !$set VERSIONS            ! Print library versions at compile time
    !#set NO_AUX_MATH         ! No advanced math needed
    !#set NO_FONTS            ! Don't use font effects
    !#set NO_FUSES            ! Don't use fuses
    !#set NO_MENUS            ! Don't use menus
    !#set NO_RECORDING        ! Don't allow transcripts
    !#set NO_SCRIPTS          ! Don't use character scripts
    !#set NO_STRING_ARRAYS    ! Don't use string arrays
    !#set NO_VERBS            ! Don't use any standard verbs
    !#set NO_XVERBS           ! Don't use any standard "out-of-world" verbs


    #ifset HUGOFIX
    #set DEBUG
    #endif

    #ifset HDX
    #switches -d              ! if the -d switch is not set in the compiler itself,
                              ! #set HDX will produce a Hugo Debuggable Executable
                              ! (.HDX) with extension .HEX
    #endif                    ! Sneaky!

    #ifset GLK
    #include "glk.h"
    #endif

    !:: Pre-hugolib.h Constants (some constants must be set before hugolib is
    !   included)

    !constant AFTER_PERIOD " " !include one space after full stops (as opposed to 2)
    !constant INDENT_SIZE 0    !no indentation in room descriptions and room
                               ! content listings

    !:: Grammar Library Inclusions (grammar must come first)
    ! put or include your new grammar here


    ! (some grammar needs to be defined before the including verblib)
    #include "verblib.g"    ! Verb Library
    ! put any post-verblib.g grammar here, if any


    #ifset PRECOMPILED_LIBRARY
    #link "hugolib.hlb"     ! Your Precompiled Library
    #else
    #include "hugolib.h"    ! Standard Hugo Library
    #endif

    !:: Other Library Inclusions
    #ifset BETA
    #include "beta.h"
    #endif

    #ifset GLK
    #include "glk.h"
    #endif

    #ifset CHEAPGLK
    #include "cheapglk.h"
    #endif

    !:: Other constants and global variables
    constant IFID "put-IFID here"

    !:: Game Initialization routine
    routine init
    {

    #ifset BETA
        if word[1] = "script"
            transcript_is_on = true
    #endif
        word[1] = ""    ! clear word[1] in case of game restart
        MAX_SCORE = 0   ! ready to change for a scored game
        STATUSTYPE = 0  ! 0 = none :: 1 = score/turns :: 2 = time
        counter = -1    ! 1 step before first turn
    !\ STATUSTYPE clock overview:
    If STATUSTYPE = 2 (time), counter is minutes since midnight, so a game
    that starts at 3 pm should have:
    counter = 899
    (900 minutes minus the one minute the main routine will add on the first
    turn)
    \!
        TEXTCOLOR = DEF_FOREGROUND
        BGCOLOR = DEF_BACKGROUND
        SL_TEXTCOLOR = DEF_SL_FOREGROUND
        SL_BGCOLOR = DEF_SL_BACKGROUND
        color TEXTCOLOR, BGCOLOR

        verbosity = 2
    !\ VERBOSITY -
    ! 1 = normal (rooms described only if not previously described)
    ! 2 = full (rooms described every time they are entered)
    \!
        display.title_caption = "<game title>"
    ! display.title_caption - used for GUI clients for title bar text.
        prompt = ">"
        window 0 ! resets the windows in case the player is restarting a game
        cls      ! clear the screen, too

    #ifset GLK
        glkcheck
    #endif

        DEFAULT_FONT = PROP_ON
        Font(DEFAULT_FONT)

    !:: Opening Text
        "Intro to game"
        print ""    ! For a blank line between the intro and the game title

        Font(BOLD_ON)
        "Game Title"
        Font(BOLD_OFF)
        "Game Blurb"
    #ifset BETA  ! this section gives build numbers to beta releases
        string(_temp_string, serial$, 8)
        "beta build: \B20";
        StringPrint(_temp_string, 6, 8)
        StringPrint(_temp_string, 0, 2)
        StringPrint(_temp_string, 3, 5)
        "\b"
    #endif
        print BANNER;
    #ifset HUGOFIX
        print " (Now with HugoFix Technology TM!)"
    #else
        print ""
    #endif
    #if defined IFID  ! print the IFID, if there is one
        print IFID
    #endif

    #ifset BETA
        "\n(\INOTE:  This beta release is intended for testing only, not for
         distribution to the general public.  Please report any errors,
         bugs, etc. to the author. To make a comment, type \"\B* COMMENT TEXT\b\" at
         the prompt.\i)"
    #endif
        player = you
        location = STARTLOCATION

        move player to location
        old_location = location
        FindLight(location)
        DescribePlace(location)
        location is visited
        CalculateHolding(player)

    #ifset USE_PLURAL_OBJECTS
        InitPluralObjects
    #endif
    }

    !:: Main game loop
    #ifset PRECOMPILED_LIBRARY
    replace main
    {
    #else
    routine main
    {
    #endif
        counter = counter + 1
        run location.each_turn
        runevents
        RunScripts
        if speaking not in location
            speaking = 0
        PrintStatusLine
    }

    player_character you "you"
    {
    }

    room STARTLOCATION "Start Location"
    {
    }

## A bare-bones shell

By popular demand, the following is a only-what-you-need version of a
Hugo shell. Things it *doesn't* do:

1.  No optional switches for things like debugging (or plural, identical
    objects)
2.  No colors declared so default interpreter colors are automatically
    used
3.  `verbosity` global is not set as 2 so game doesn't start out in
    VERBOSE mode
4.  `display.title_caption` doesn't have a placeholder line for the
    game's title
5.  No code for precompiled headers in there anymore

<!-- -->

    ! put your new verb grammar here

    ! new grammar needs to be defined before the including verblib
    #include "verblib.g"    ! Verb Library

    #include "hugolib.h"    ! Standard Hugo Library

    !:: Game Initialization routine
    routine init
    {
        STATUSTYPE = 1  ! 0 = none :: 1 = score/turns :: 2 = time
        counter = -1    ! 1 step before first turn
        prompt = ">"    ! the prompt character
        window 0        ! resets the windows in case the player is restarting
        cls

        DEFAULT_FONT = PROP_ON
        Font(DEFAULT_FONT)

    !:: Opening Text
        "Intro to game"
        print ""    ! For a blank line between the intro and the game title

        Font(BOLD_ON)
        "Game Title"
        Font(BOLD_OFF)
        "Game Blurb"

        player = you
        location = STARTLOCATION

        move player to location
        old_location = location
        FindLight(location)
        DescribePlace(location)
        location is visited
        CalculateHolding(player)
    }

    !:: Main game loop
    routine main
    {
        counter = counter + 1
        run location.each_turn
        runevents
        RunScripts
        if speaking not in location
            speaking = 0
        PrintStatusLine
    }

    player_character you "you"
    {
    }

    room STARTLOCATION "Start Location"
    {
    }
