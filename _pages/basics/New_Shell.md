---
title: The "new shell"
permalink: /basics/new-shell/
categories: 
  - Basics
---

This is a updated version of the `shell.hug` that is available at the
main Hugo webpage (and also available at the ifarchive). It was originally
based on both on that original and a bit on the ScavHunt tutorial. You
can download a version of it
[here](https://drive.google.com/file/d/19fU-aDpwjD3HaxdH5sX6OSDSMkbooOht/view?usp=sharing).

This file includes several commonly used flags and switches that one
can often forget are available. It also includes a
global called [IFID](http://ifwiki.org/index.php/IFID), a unique
identifier for Interactive Fiction games. There is an easy to use IFID
generator at
[www.tads.org/ifidgen/ifidgen](http://www.tads.org/ifidgen/ifidgen).
There is also a program that's available on many linux distros that can
be used to create an IFID called *uuidgen*.

    !::
		! New Game (Shell)
		!::

		!:: Raise limits, if necessary (here are some of the limits you're likely to
		!   run into first).
		!$MAXROUTINES = 320
		!$MAXDICT = 1024
		!$MAXDICTEXTEND = 0 ! (needed for adding more dictionary words mid-game)

		!:: Flags
		!#set BETA                ! Compile with the comments-in-transcripts library
										  !   addition
		!#set HUGOFIX             ! Compile with HugoFix Debugging Library commands
										  !   available (type $? in game)
		!#set VERBSTUBS           ! Include the grammar and routines from verbstubs.g
										  !   and verbstubs.h, respectively
		!#set USE_ATTACHABLES     ! Use attachable items
		!#set USE_PLURAL_OBJECTS  ! Use plural objects
		!#set USE_ROLLABLES       ! Allow the pushing of mobile objects (needs Roodylib)
		!#set USE_ROODYLIB
		!#set USE_VEHICLES        ! Use vehicle objects
		#set VERSIONS            ! Print library versions at compile time

		!:: switches              ! example how one can add compiler switches to source
		#switches -s              ! print compilation statistics

		#ifset HUGOFIX
		#set DEBUG
		#endif

		!:: Constants and global variables (some constants must be set before hugolib
		!   is included):

		constant GAME_TITLE "GAME TITLE"
		constant AUTHOR "YOUR NAME"
		constant RELEASE "1.0"
		!constant FIRST_PUBLICATION "(year)"  ! for previously released games
		!constant BLURB "An Interactive Blah"
		!constant IFID "put-IFID here"
		!constant AFTER_PERIOD " "     ! include one space after full stops (as opposed
												 !   to two)
		!constant INDENT_SIZE 0        ! no indentation in room descriptions and room
												 !   content listings

		!:: Grammar Library Inclusions (grammar must come first)
		#ifset USE_ROODYLIB
		#include "roodylib.g"
		#endif

		! new grammar needs to be defined before the including verblib
		#include "verblib.g"        ! Verb Library

		#include "hugolib.h"        ! Standard  Hugo Library
		#ifset USE_ROODYLIB
		#include "roodylib.h"         ! Hugo  Library Updates
		#endif

		!::	Other Library Inclusions

		!::	Game Initialization	routine
		routine init
		{
		!: First Things First
			SetGlobalsAndFillArrays
		!: Screen clear section
		#ifclear _ROODYLIB_H
			CenterTitle("Hugo Interactive Fiction")
			cls
		#ifset USE_PLURAL_OBJECTS
			InitPluralObjects
		#endif
		#else
			SimpleIntro
			InitScreen
		!: Set up any special libraries
			Init_Calls
		#endif
		!: Game opening
			IntroText
			MovePlayer(location)
		}


		routine SetGlobalsAndFillArrays
		{
		!\ Uncomment and modify this section if your game has scoring and ranking.
			MAX_SCORE = 50
			ranking[0] = "Amateur Adventurer"
			ranking[1] = "Competent Door-Unlocker"
			ranking[2] = "Bomb-Meddling Adventurer"
			ranking[3] = "Master Magic Wand Finder"
			ranking[4] = "The Genuine Article Sample Game Solver"
			MAX_RANK = 4  \!
		! if using Roodylib, verbosity can be set to BRIEF, SUPERBRIEF, OR VERBOSE
			verbosity = 2
			counter = -1                    ! 1 turn before turn 0
		! statustype options: 0 = no status, 1 = score/turns, 2 = time
		! if using Roodylib, can be set to NO_STATUS, SCORE_MOVES, TIME_STATUS,
		! CUSTOM_STATUS, INFOCOM_STYLE, MILITARY_TIME
			STATUSTYPE = 1
			TEXTCOLOR = DEF_FOREGROUND
			BGCOLOR = DEF_BACKGROUND
			SL_TEXTCOLOR = DEF_SL_FOREGROUND
			SL_BGCOLOR = DEF_SL_BACKGROUND
			INPUTCOLOR = MATCH_FOREGROUND
		#if defined TITLECOLOR
			TITLECOLOR = DEF_FOREGROUND
		#endif
			prompt = ">"
			DEFAULT_FONT = PROP_ON
		#if defined GAME_TITLE
			display.title_caption = GAME_TITLE
		#endif
		#ifset _ROODYLIB_H
			MakePlayer(you,2) ! sets player as you object, second person
		#else
			player = you
		#endif
			location = STARTLOCATION
		}

		routine IntroText
		{
			"Intro text goes here."
		#if defined DoVersion
			""
			DoVersion
		#endif

		}

		!::	Main game loop
		routine main
		{
			counter = counter + 1
			run location.each_turn
			runevents
			runscripts
		#ifset _ROODYLIB_H
			SpeakerCheck
		#else
			if parent(speaking) ~= location
				speaking = 0
		#endif
			PrintStatusLine
		#ifset _ROODYLIB_H
			Main_Calls
		#endif
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
