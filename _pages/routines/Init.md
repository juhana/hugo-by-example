---
title: Init
permalink: /routines/init/
categories: 
  - Routines
---

`init` (short for "initialization") is the [routine](/routines/)
that "sets the game up" when the game starts (or is restarted). Let's
look at a commented `init` routine to get an idea of the kinds of things
it can do:

    routine init
    {
       STATUSTYPE = 1  ! 0 = none :: 1 = score/turns :: 2 = time
       counter = -1    ! 1 step before first turn
       prompt = ">"  ! the prompt character
       window 0 ! resets the windows in case the player is restarting a game
       cls  ! clears the screen

       TEXTCOLOR = WHITE           ! set colors
       BGCOLOR = BLACK             ! when we want
       SL_TEXTCOLOR = BLACK        ! the game to use
       SL_BGCOLOR = RED            ! particular
       color TEXTCOLOR, BGCOLOR    ! colors

       verbosity = 2  ! set the verbosity global ("2" is VERBOSE)

       DEFAULT_FONT = PROP_ON ! the interpreter's proportional font is
       Font(DEFAULT_FONT)     !  the default font

       !:: Opening Text
       "Intro to game"
       print ""    ! For a blank line between the intro and the game title

       Font(BOLD_ON)
       "Game Title"
       Font(BOLD_OFF)
       "Game Blurb"

       player = you              ! set player object
       location = STARTLOCATION  !  set starting location
       old_location = location   !  and old_location global variables

       move player to location  ! move player to starting location
       FindLight(location)      ! sets light_source variable, if any
       DescribePlace(location)  ! print the starting room's name and description
       location is visited
       CalculateHolding(player) ! calculate the bulk of the things the player is
                                ! already holding

    #ifset USE_PLURAL_OBJECTS
       InitPluralObjects        ! run only if we have set the USE_PLURAL_OBJECTS flag
    #endif
    }
