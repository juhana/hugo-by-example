---
title: Halloween Horror Part II
permalink: /example-games/halloween-horror-part-2
categories: 
  - Example Games
---

See the [Halloween Horror Part I](/example-games/halloween-horror-part-1/)
page for explanation.

## the code

    !::
    ! Halloween Horror - The Movie
    !::
    #set GLK
    !#set BETA

    $MAXDICTEXTEND = 512
    #ifset HUGOFIX
    #set DEBUG
    #endif

    #ifset HDX
    #switches -d
    #endif

    !:: Grammar Library Inclusions (grammar must come first)
    ! put your new grammar here
    verb "hit"
    * object "with" (knife)      DoHit

    verb "wake"
        *                               DoWake
        *   living                  DoWake
    verb "flush"
    *           DoFlush

    xverb "about","menu"
        *                   DoAbout

    synonym "cut" for "hit"
    synonym "stab" for "hit"
    synonym "kill" for "hit"

    ! new grammar needs to be defined before the including verblib
    #include "verblib.g"    ! Verb Library

    #include "hugolib.h"

    !:: Other Library Inclusions
    #ifset BETA
    #include "beta.h"
    #endif

    #ifset GLK
    #include "glk.h"
    #endif

    !:: Other constants and global variables
    constant IFID "E361278D-4306-4051-9E47-CC3F95CEE7B6"
    global 1iswon
    global 2iswon
    global havesaved
    global haveundone

    !:: Game Initialization routine
    routine init
    {
        LoadConfig
        if not 1iswon
            {
            "You are not ready for this yet. Go beat Part I first.\n"
            display.title_caption = "NOT READY YET"
                    "PRESS ANY KEY TO QUIT"
                     pause
                     quit
            }
    #ifset BETA
        BetaInit
    #endif
        STATUSTYPE = 0  ! 0 = none :: 1 = score/turns :: 2 = time
        counter = -1    ! 1 step before first turn
        TEXTCOLOR = BRIGHT_WHITE
        BGCOLOR = BLACK
        SL_TEXTCOLOR = RED
        SL_BGCOLOR = WHITE
        color TEXTCOLOR, BGCOLOR

        verbosity = 2
        !\ Verbosity: 1 = normal (rooms described only if not previously described)
            2 = full (rooms described every time they are entered) \!

        display.title_caption = movie.name  ! used for GUI clients for title bar text.
        prompt = ">"

        window 0 ! resets the windows in case the player is restarting a game
        cls

    #ifset GLK
        glkcheck
    #endif

        DEFAULT_FONT = PROP_ON
        Font(DEFAULT_FONT)

        if (not glk)
            {
            locate 1,3
            }
        !:: Opening Text
        if 2iswon
            {
        "\ISometimes it's nice to rewatch a good movie...\i"
            }
        else
        "\IMovies are almost never faithful to the source material, but let's give this one a shot...\i"
        print ""    ! For a blank line between the intro and the game title

        Font(BOLD_ON)
        color RED
        print movie.name
        color TEXTCOLOR
        Font(BOLD_OFF)
        "Written and Directed by Roody Yogurt"
        print "Release 1 / ";
        print BANNER
    #ifset BETA
            string(_temp_string, serial$, 8)
        "BETA BUILD # 20";
        StringPrint(_temp_string, 6, 8)       ! if a BETA flag is set,
        StringPrint(_temp_string, 0, 2)       ! a build # in YEARMODY
        StringPrint(_temp_string, 3, 5)       ! format is printed.
        ".0"
    #endif
        print "IFID: "; IFID

        player = you
        location = STARTLOCATION
        WAIT_TURN_COUNT = 1
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
    PrintStatusLine
    run location.each_turn
    runevents
    RunScripts
    if speaking not in location
        speaking = 0
    }

    !:: Standard Library replacements
    replace PreParse
    {
            if display.needs_repaint
            {
            ""
            "[Detected screen size change. Press a key to redraw.]"
            pause
            cls
            if not glk
                {
                locate 1,3
                }
            display.needs_repaint = false
            }
    }

    replace room
    {
        type room
        is static, light, open
        after
            {
            location DoListen
                {
                "You hear nothing special."
                }
            }
    }

    replace PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        color GREEN
        select end_type
            case 1:  {
                print "\n*** THAT'S NOT HOW THE MOVIE'S SUPPOSED TO END! ***"
                }
            case 2:  {
                PRINT "\n*** THE END CREDITS ARE AWESOME ***\n"
                "(Now go play Part I again)"
                }
                    case 3:  print "\n*** YOU ARE AREN'T A DUCK! ***"
        color TEXTCOLOR
        Font(BOLD_OFF)
    !   PrintScore(true)
    }

    replace DoListen
    {
        if not object
            {
                if not location.after
                    {
                    VMessage(&DoListen, 1)  ! "Be a little more specific..."
                    return false
                    }
                verbroutine = ""
                return true
            }
        elseif not object.after
            VMessage(&DoListen, 2)   ! "Not making any sound..."
        ! we have to clear verbroutine or else location.after.DoListen will run again
        verbroutine = ""
        return true
    }

    replace DoUndo
    {
        if not UNDO_OFF
        {
            if undo
            {
                PrintStatusline
                DescribePlace(location)
                haveundone = true
            }
            else
                VMessage(&DoUndo)
        }
        else
            VMessage(&DoUndo)
    }

    replace DoSave
    {
        if save
        {
            VMessage(&DoSave, 1)             ! "Saved."
            havesaved = true
            return true
        }
        else:  VMessage(&DoSave, 2)              ! "Unable to save."
    }

    replace PrintStatusline
    {
        if display.linelength < 40
            display.statusline_height = 2
        else
            display.statusline_height = 1

        Font(BOLD_OFF | ITALIC_OFF | UNDERLINE_OFF | PROP_OFF)
        window display.statusline_height
        {
            color SL_TEXTCOLOR, SL_BGCOLOR
            cls
            locate 1, 1
            if not location
                print "_";
            elseif not light_source
                print "In the dark";
            else
            {
                if FORMAT & DESCFORM_F:  print "_";
                print capital location.name;
            }

            if display.statusline_height = 1
                            {
                            text to _temp_string
                    if STATUSTYPE = 1
                        print number score; " / "; number counter;
                    elseif STATUSTYPE = 2
                        print HoursMinutes(counter);
                if player is special
                print "[DYING OF POISON]";
                text to 0
                print to (display.screenwidth - (StringLength(_temp_string) + 2));
                            }
            else
            {
                locate 1, 2
                if FORMAT & DESCFORM_F:  print "_";
            }

    !       if STATUSTYPE = 1,2
            if player is special
                         StringPrint(_temp_string)
        }
        color TEXTCOLOR, BGCOLOR
        Font(DEFAULT_FONT)
    }


    !----------------------------------------------------------------------------
    ! EndGame(end_type)
    ! called by the engine via EndGame(end_type) when endflag is not false
    ! (endflag is cleared previous to calling); return false to terminate
    !
    ! Default responses (in PrintEndGame):  1 = win, 2 = die, 0 = no response

    replace EndGame(end_type)
    {
        UNDO_OFF = true
        PrintStatusLine                 ! update one last time
        PrintEndGame(end_type)          ! print appropriate ending message

    #ifclear NO_VERBS
        local r

    :AskAgain2

        Message(&EndGame, 1)    ! ask to RESTART, RESTORE, (UNDO), or QUIT

        r = -1

        while true
        {
            GetInput
            select word[1]
                case "restart", "r"
                {
                    if restart
                    {
                        r = true
                        PrintStatusline
                    }
    #ifclear NO_XVERBS
                    else
                        Message(&DoRestart, 2)   ! failed
    #endif
                    break
                }
                case "restore", "e"
                {
    #ifclear NO_XVERBS
                    r = Perform(&DoRestore)
    #else
                    if restore
                    {
                        r = true
                        PrintStatusline
                        DescribePlace(location)
                    }
    #endif
                    break
                }
    #ifclear NO_UNDO
                case "undo", "u"
                {
                    if not UNDO_OFF
                    {
                        if undo
                        {
                            r = true
                            PrintStatusLine
                            DescribePlace(location)
                        }
    #ifclear NO_XVERBS
                        else
                            Message(&DoUndo, 1)  ! failed
                    }
                    else
                        Message(&DoUndo, 1)
    #else
                    }
    #endif
                    break
                }
    #endif
                case "quit", "q"
                {
                    r = 0
                    break
                }

            Message(&EndGame, 2)    ! ask again (more succinctly)
        }

        if r = -1:  jump AskAgain2

        return r

    #else   ! i.e., #elseif set NO_VERBS

        return 0;
    #endif
    }

    !:: Game objects
    player_character you "you"
    {
        long_desc
            "You look just like the protagonist to a horror movie."
        misc 0
        before
            {
            actor DoGo
                {
                if self is special
                    {
                    if object.type = direction
                        {
                            local k
                            k = location.(object.dir_to)
                            if k > 1                ! since a message always returns 1
                                "Not while you are dying of poison, you don't!"
                            else
                                return false
                        }
                    }
                else
                    return false
                }
            }
    }

    event in you
    {
        if you is special
            {
            you.misc++
            if you.misc = 3
                {
                "\nEventually, you decide that the spider was probably not poisonous
                after all. Whew!"
                you is not special
                PrintStatusLine
                }
            else
                "\nYou writhe around in pain, waiting to die."
            }
    }

    room STARTLOCATION "Stranded"
    {
        long_desc
            "Who would have thought that your car would break down on such a bleary
            night? To the south lies the country road on which your car has given up
            the ghost. Across the frozen lake to the north, you can see lights that
            contain the promise of help."
        n_to frozenlake
        s_to
            "You didn't leave anything of importance in your car."
    }

    scenery road "country road"
    {
        article "the"
        adjective "country"
        noun "road"
        in STARTLOCATION
        before
            {
            object DoGo
                {
                return STARTLOCATION.s_to
                }
            object
                {
                "The road is to the south, not here."
                }
            xobject
                {
                "The road is to the south, not here."
                }
            }
        is enterable platform
        extra_scenery "lake" "frozen" "ice"
    }

    scenery lights "lights"
    {
    noun "light" "lights"
    article "the"
    nearby
    long_desc
        {
        "Maybe someone there could help you?"
        }
    }

    scenery car "car"
    {
        nearby
        article "your"
        noun "car"
        is enterable container open known
        before
        {
        object DoGo
            {
            return STARTLOCATION.s_to
            }
        object
            {
            "Your car is to the south, not here."
            }
        xobject
            {
            "Your car is to the south, not here."
            }
        }
    }

    room frozenlake "Frozen Lake"
    {
        long_desc
            "Maybe taking this shortcut across a frozen lake wasn't the smartest of
            ideas. The lake stretches in all directions."
        cant_go
            {
            if object = u_obj,d_obj,in_obj,out_obj
                return false
            else
                LakeRoutine
            }
        after
            {
            location DoListen
                {
                "You hear the worrisome sound of ice cracking with increasing
                frequency."
                }
            }
        misc 0
        extra_scenery "ice" "cracks" "crack" "frozen" "lake"
    }

    object movie
    {
    misc 0
    }


    room bank "Other Side"
    {
        long_desc
            "Hopefully, the worst of your night is over. The defeated frozen lake
            lies to the south. A farmhouse lies to the north."
        s_to
            "You don't want to go back to the lake."
        n_to farmhouse
        extra_scenery "farmhouse" "frozen" "lake"
    }

    room farmhouse "Farmhouse"
    {
        long_desc
            "Strangely enough, this farmhouse seems abandoned. An exit north leads to
            a yard."
        s_to bank
        n_to yard
    }

    object knife "butcher knife"
    {
        article "the"
        adjective "butcher"
        noun "knife"
        in farmhouse
        before
            {
            object DoDrop
                {
                "Nah, you might need it."
                }
            }
        after
            {
            object DoGet
                {
                if havesaved or haveundone
                    return false
                else
                    {
                    "A hidden spider previously unnoticed ";
                    color MAGENTA
                    "RANDOMLY ";
                    color TEXTCOLOR
                    "jumps out and bites you! You are
                    now poisoned! It scurries off, never to be seen again. You grab the knife."
                    }
                player is special
                }
            }
    }

    room yard "Yard"
    {
        long_desc
            "This is a yard. To the northwest lies a SCARY BARN."
        nw_to barn
        s_to farmhouse
        extra_scenery "scary" "barn"
    }

    room barn "Scary Barn"
    {
        long_desc
            "This barn is as many barns are, a big room with lots of hay."
        extra_scenery "hay"
        se_to yard
        after
            {
            location DoListen
                {
                "You hear the gentle intake and exhalations of the killer's quiet
                breaths."
                }
            }
    }

    character killer "sleeping killer"
    {
        article "the"
        is unfriendly
        noun "killer"
        adjective "sleeping" "evil"
        ignore_response
            "The killer is asleep!"
        short_desc
            "Taking a cat nap next to the remains of his latest victim is an evil killer!"
        before
            {
            object DoHit
                {
                if parent(knife) ~= you
                    "You'd be confident if you had a knife!"
                else
                    {
                    "You sneak up and stab the killer! His reign of terror
                    is over! Maybe you will star in the sequel, too!"
                    2iswon = true
                    SaveConfig
                    endflag = 2
                    }
                }
            }
        after
            {
            object DoListen
                {
                "You hear the gentle intake and exhalations of the killer's quiet
                breaths."
                }
            }
        in barn
    }

    scenery remains "victim's remains"
    {
        article "the"
        noun "remains" "victim"
        adjective "victim's"
        nearby
        before
            {
            object
                {
                "Ew, gross!"
                }
            }
    }

    event in killer
    {
        if haveundone or havesaved
            {
            "Without warning, the killer pops up from his nap and disembowels you! Maybe if you weren't such
            a scaredy-cat, you would have expected that!"
            endflag = 1
            }
    }

    !:: Configuration file routines
    array name_array[50]
    array name2_array[50]

    routine LoadConfig
    {
            ClearArray(name2_array)
            local test2
          readfile "gamedata"
               {
          local a
          for (a=0;a<=49;a++)
          {
          name_array[a] = readval
          }
          text to name2_array
          StringPrint(name_array)
          " - THE MOVIE";
          text to 0
          movie.name = dict(name2_array, 49)
           1iswon = readval
          2iswon = readval
           test2 = readval
               }
          if test2 ~= FILE_CHECK
              {
      !        print "Error reading file."
              }
            ClearArray(name2_array)
    }

    ! The name of the movie kept on adding extra "- THE MOVIE"s
    ! to titles so I started clearing the name2_array array
    ! all over the place
    routine ClearArray(array_to_clear)
    {
        local f
        for (f = 0;f< array array_to_clear[] ; f++ )
            {
            array array_to_clear[f] = 0
            }
    }

    routine SaveConfig
    {
         local test2
         writefile "gamedata"
              {
          local a
          for (a=0;a<=49;a++)
          {
          writeval name_array[a]
          }
          writeval 1iswon
          writeval 2iswon
              test2 = FILE_CHECK
              writeval test2
              }
         if test2 ~= FILE_CHECK  ! if the program didn't get this far, we know something is wrong
              {
              print "An error as occurred."
              }
    }

    !:: Verb routines
    routine DoFlush
    {
        "The \B>FLUSH\b command is only supported in Part I."
    }

    routine DoAbout
    {
        "No need to play with menus for this movie. Don't worry- subtitles
        are already turned on!"
    }

    routine DoWake
    {
        if not object or object = you
            {
            "But this is not a dream!"
            }
            else
                "That'd be rude."
    }

    !: Misc. routines

    routine LakeRoutine
    {
        if location.misc = 4
            {
            if haveundone or havesaved
                {
                "Without warning, the ice breaks beneath you, giving you an untimely
                frozen death."
                endflag = 1
                }
            else
                {
                "You have made it to the other side!"
                MovePlayer(bank)
                return
                }
            }
        local a
        if haveundone or havesaved
            {
            a = random(3)
            select a
                case 1, 2: "You walk in that direction with no audible consequences."
                case 3: "Soft cracks underfoot follow your footsteps."
            DescribePlace(location)
            location.misc = ++location.misc
            }
        else
            {
            select location.misc
                case 0: "The ice makes soft audible cracks underfoot."
                case 1: "Now the cracks are louder and becoming quite visible. Another
                misstep could kill you!"
                case 2: "Water seeps up from the large cracks spiderwebbing beneath
                you. This can't be safe!"
                case 3: "Oh dear, is the ice giving way beneath you?"
            location.misc = ++location.misc
            DescribePlace(location)
            }
    }
