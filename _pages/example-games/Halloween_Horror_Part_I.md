---
title: Halloween Horror Part I
permalink: /example-games/halloween-horror-part-1
categories: 
  - Example Games
---

This is Roody Yogurt's update to a game originally released as "The Ecto
Horror." It requires the [glk.h](glk.h) and
[newmenu.h](newmenu.h) library extensions (and possibly
[beta.h](beta.h)).

## the code

    !::
    ! The Halloween Horror by Roody Yogurt
    !::
    #set GLK
    !#set BETA

    !$MAXDICTEXTEND = 512
    #ifset HUGOFIX
    #set DEBUG
    #endif

    #ifset HDX
    #switches -d
    #endif

    !:: Pre-Hugolib.h Constants

    !:: Grammar Library Inclusions (grammar must come first)
    ! put your new grammar here

    verb "answer"
    * (phone)           DoAnswer

    verb "call"
    *               DoCall
    * anything          DoCall

    verb "flush"
    *           DoFlush

    verb "smell"
        *                   DoSmell
        * object            DoSmell

    xverb "about","menu"
        *                   DoAbout

    xverb "version"
        *               DoVersion

    verb "hooray"
        *              DoHooray
    synonym "sprawl" for "sit"

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

    #include "window.h"
    #include "system.h"
    #include "newmenu.h"

    !:: Other constants and global variables
    constant IFID "E361278D-4306-4051-9E47-CC3F95CEE7B6"
    global 1iswon
    global 2iswon

    !:: Game Initialization routine
    routine init
    {
        LoadConfig
        SaveConfig(1)
    #ifset BETA
        BetaInit
    #endif
            STATUSTYPE = 0  ! 0 = none :: 1 = score/turns :: 2 = time
            counter = -1
            TEXTCOLOR = BRIGHT_WHITE
            BGCOLOR = BLACK
            SL_TEXTCOLOR = RED
            SL_BGCOLOR = WHITE
            color TEXTCOLOR, BGCOLOR

            verbosity = 2   ! 1 = normal (rooms described only if not previously
                            !     described)
                            ! 2 = full (rooms described every time they are entered)
        if not 2iswon
            display.title_caption = "Halloween Horror"
        else
            display.title_caption = "Halloween Horror Part 2"
        prompt = ">"

            window 0 ! resets the windows in case the player is restarting a game
            cls

    #ifset GLK
           glkcheck
    #endif

        if (not glk)
            {
            locate 1,3
            }
            DEFAULT_FONT = PROP_ON
            Font(DEFAULT_FONT)

            !:: Opening Text
        if not 2iswon
            "This is your favorite part of the week, the only night where you can
        settle down with a big bowl of popcorn and zone out to a horror movie."
        else
            "Wow, that was a pretty rocking movie. Those reviewers on Quikster had
        no idea what they were talking about! You stand up and turn off the TV."

        print ""    ! For a blank line between the intro and the game title
        color LIGHT_RED
        Font(BOLD_ON)
        if not 2iswon
            "The Halloween Horror"
        else
            "The Halloween Horror Part II"
        Font(BOLD_OFF)
        color TEXTCOLOR
        "by Roody Yogurt"
        print "Release 1 / ";
        print BANNER
    #ifset BETA
            string(_temp_string, serial$, 8)
        "BETA BUILD # 20";
        StringPrint(_temp_string, 6, 8)       ! if a BETA flag is set,
        StringPrint(_temp_string, 0, 2)       ! a build # in YEARMODY
        StringPrint(_temp_string, 3, 5)       ! format is printed.
        ".1"
    #endif
        print "IFID: "; IFID
        "Type \BABOUT\b for more info"
    #ifset BETA
        "\n(\INOTE:  This beta release is intended for testing only, not for
        distribution to the general public.  Please report any errors,
        bugs, etc. to the author. To make a comment, type \"\B* COMMENT TEXT\b\" at the prompt.\i)"
    #endif
        player = you
        if not 2iswon
            location = STARTLOCATION
        else
            location = livingroom
        move player to location
        old_location = location
        FindLight(location)
        DescribePlace(location)
        location is visited
        CalculateHolding(player)
        if 2iswon
            {
            move bowl to you
            phone is special
            }
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

    !: Standard Library replacements

    replace PreParse
    {
            if display.needs_repaint
            {
            "[Detected screen size change. Press a key to redraw.]"
            pause
            cls
            if not glk
                {
                locate 1,3
                }
            PrintStatusLine
            display.needs_repaint = false
            }
    }

    ! the room class - so each room can have a default DoListen response
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

    ! DoListen - to support both object and room listening
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

    ! SpeakTo - this version doesn't change the speaking global if you
    ! just type the name of a nearby non-living thing. plus, no jumps.
    replace SpeakTo(char)
    {
        local TryOrder, IgnoreResponse
    #ifset USE_CHECKHELD
        if verbroutine = &DoDrop_CheckHeld
            verbroutine = &DoDrop
        elseif verbroutine = &DoPutIn_CheckHeld
            verbroutine = &DoPutIn
    #endif

    #ifset VERBSTUBS
        if verbroutine = &DoHelpChar and object = player
        {
            verbroutine = &DoHelp
            object = nothing
        }
    #endif

    #ifset USE_CHECKHELD
        ResetCheckHeld
    #endif

    #ifset DEBUG
        if debug_flags & D_PARSE
        {
            print "\B[Speakto("; char.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number char; "]";
            print ") verbroutine="; number verbroutine;
            print ", object="; object.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number object; "]";
            print ", xobject="; xobject.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number xobject; "]";
            print "]\b"
        }
    #endif

    !   old speaking = 0 position

        if char is not living
        {
            ParseError(6)
            return
        }

        ! new speaking = 0 position
        speaking = 0 ! so typing an object won't clear the speaking global

        AssignPronoun(char)

        ! Handle player/typist-related ParseError messages:
        if not FindObject(char, location)
        {
            actor = player
            ParseError(11, char)
            return
        }
        elseif char = player
        {
            actor = player
            Message(&Speakto, 1)    ! "Stop talking to yourself..."
            return
        }
        elseif not ObjectisKnown(object) and not FindObject(object, location)
        {
            actor = player
            ParseError(10, object)
            return
        }

        if char is unfriendly
            IgnoreResponse = true
        else
            {
            speaking = char

            ! In the event of:  >CHARACTER, GO NORTH.  GET THE THING.  GO WEST., etc.
            if not FindObject(char, location)
            {
                run char.order_response
                return true
            }

            select verbroutine
                case 0                  ! Just the character name is given,
                            ! so just "X is listening."
                {
                    if not char.order_response
                        Message(&Speakto, 2, char)
                }

        #ifclear NO_VERBS
                case &DoHello           ! Note the ampersands ('&')--or else
                {                       ! the routines themselves would run
                    if not char.order_response
                    {
                        if char is not unfriendly
                            ! "X nods hello."
                            Message(&Speakto, 3, char)
                        else
                        {
                            IgnoreResponse = true
                        }
                    }
                }

                case &DoAskQuestion
                    return Perform(&DoAsk, char, object)

                case &DoTalk
                {
                    if xobject
                        ParseError(6)
                    else
                        return Perform(&DoAsk, char, object)
                }

                case &DoTell
                {
                    if object = player
                        return Perform(&DoAsk, char, xobject)
                    else
                        TryOrder = true
                }
        #endif  ! ifclear NO_VERBS

                case else
                {

        ! If the character can respond to a request, this should be dealt with by
        ! an order_response property routine; order_response--if it exists--should
        ! return false if there is no response for the given verbroutine

                TryOrder = true
                }
            }

        if TryOrder
                {
                if (not char.order_response)
                    IgnoreResponse = true
                else
                    return true
                }
        if IgnoreResponse
                {
                if not char.ignore_response
                    Message(&Speakto, 4, char)      ! "X ignores you."
                }
        return false
    }

    ! PrintStatusLine
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

    ! (The part we're changing)
    !           print to 65; ! is 65 characters good for every window size? No!

    ! Instead, let's begin by writing the entire 'SCORE / MOVES' to array _temp_string
    ! (_temp_string is an array declared by the library)

                    text to _temp_string
          if STATUSTYPE = 1
             print number score; " / "; number counter;
          elseif STATUSTYPE = 2
             print HoursMinutes(counter);
               text to 0
    ! Ok, we've closed off the string array

    ! Now, if the screen is wide enough, let's move to the end of the screen MINUS the length of the _temp_string array
    ! plus two extra spaces for good measure (so there's a little space to the right on the status bar)
          if display.statusline_height = 1
             print to (display.screenwidth - (StringLength(_temp_string) + 2));
          else
          {
             locate 1, 2
             if FORMAT & DESCFORM_F:  print "_";
          }

     ! Now let's print it!
          if STATUSTYPE = 1,2
                         StringPrint(_temp_string)
       }
       color TEXTCOLOR, BGCOLOR
       Font(DEFAULT_FONT)
    }

    ! PrintEndGame - ending game text
    replace PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        color GREEN
        select end_type
            case 1
                {
                print "\n*** LET'S WATCH A MOVIE! ***\n"
                "(Now go play Part II)"
                }
            case 2:  PRINT "\n*** YOU HAVE REACHED THE NADIR OF GREATNESS ***"
          case 3:  print "\n*** A WINNER IS YOU! ***"
        color TEXTCOLOR
        Font(BOLD_OFF)
    !   PrintScore(true)
    }

    ! DoRestart - added a settings-clearing choice
    replace DoRestart
    {
        VMessage(&DoRestart, 1)                  ! "Are you sure?"
        GetInput
        if YesorNo = true
        {
        word[1] = ""
        "Would you also like to flush the current settings? ";
        if (YesorNo)
            {
            FlushSettings
                ""
            "Settings flushed."
            }
        else
            "\nSettings not flushed.\n"
        "PUSH A KEY TO CONTINUE"
        PAUSE
            if not restart
                VMessage(&DoRestart, 2)  ! "Unable to restart."
        }
    }

    !: EndGame menu routines
    ! EndGame - Allow for a different keypress after game is over
    replace EndGame(end_type)
    {
       PrintStatusLine                 ! update one last time
       PrintEndGame(end_type)          ! print appropriate ending message

    #ifclear NO_VERBS
       local r

       Message(&EndGame, 1,end_type)    ! ask to RESTART, RESTORE, (UNDO), or QUIT

       r = -1
       while r = -1
       {
       GetInput
       r = ProcessKey(word[1], end_type)
       if r = -1
             Message(&EndGame, 2,end_type)    ! ask again (more succinctly)
       }

       return r

    #else   ! i.e., #elseif set NO_VERBS

       return 0;
    #endif
    }

    ! ProcessKey - helper routine for the above EndGame replacement
    routine ProcessKey(entry,end_type)
    {
       local r
       r = -1
       select entry
                case "restart", "r"
                {
                   if restart
                   {
                      r = 1
                      PrintStatusline
                   }
       #ifclear NO_XVERBS
                   else
                      Message(&DoRestart, 2)   ! failed
       #endif

                }
                case "restore", "e"
                {
       #ifclear NO_XVERBS
                   if Perform(&DoRestore)
                      r = 1
       #else
                   if restore
                   {
                      r = 1
                      PrintStatusline
                      DescribePlace(location)
                   }
       #endif
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
                }
       #endif
                    case SpecialKey(end_type)
                        {
                        if entry
                            SpecialRoutine
                        }
                case "quit", "q"
                {
                   r = 0
                }

       return r
    }

    ! SpecialKey - routine for handling extra available keypresses or inputs
    !   for EndGame
    routine SpecialKey(end_type)
    {
        if end_type = 3 and (word[1] = "s","special")
            {
            return word[1]
            }
        else
            return false
    }

    ! SpecialRoutine - another routine for EndGame
    routine SpecialRoutine
    {
        if display.linelength > 62
            {
            MakeMenu(special_menu)
            ""
            cls
            if not glk
                {
                locate 1,3
                }
            print "The game has ended. ";
            }
        else
            {
                color CYAN
                "\n\IWhat was the point of the mid-game (the movie)? I won on my first
                try!\i"
                color TEXTCOLOR
                "The middle game was the author's somewhat feeble attempt to try to get the player to \BUNDO\b
                or \BSAVE\b (at a couple parts). If one does that, the game becomes unwinnable (usually).\n"
                "I hope you enjoyed the game!\n"
            }
    }

    ! NewMessages - some new EndGame messages
    replace NewMessages(r, num, a, b)
    {
           select r
             case &EndGame
                {
                select num
                    case 1
                        {
                        select a
                            case 3
                                {
                                print "\nThe game has ended.  Do you want to (R)ESTART,
                                R(E)STORE a saved game, (S)pecial notes, or (Q)UIT? ";
                                return true
                                }
                            case else: return false
                        }
                    case 2
                        {
                        select a
                            case 3
                                {
                                print "Do you want to (R)ESTART,
                                R(E)STORE a saved game, (S)pecial notes, or (Q)UIT? ";
                                return true
                                }
                            case else: return false
                        }
                }
            case else : return false
    }

    !:: Game objects
    player_character you "you"
    {
        long_desc
            {
            if not 2iswon
                "You are just happy to have made it through the week and are intent on
                enjoying a night to yourself."
            else
                "Sated by popcorn and a good movie, you contentedly wonder what else
                the night holds for you."
            }
    }

    object phone "cellphone"
    {
        article "your"
        noun "phone" "cellphone"
        adjective "cell"
        long_desc
            "You are a protagonist of modern times, one who almost always has a
            cellphone handy."
        before
            {
            object DoSwitchOn
                {
                "It's already on."
                }
            object DoSwitchOff
                {
                "Nah, you like to keep it on. It has plenty of battery power left."
                }
            object DoDrop
                {
                "Nah, you'd rather hold on to it."
                }
            }
        in you
        misc 0
    }

    room STARTLOCATION "Kitchen"
    {
        long_desc
            "Your kitchen is pretty sparse. The living room is to the east."
        extra_scenery  "table" "shelf"
        e_to {
            if microwave is switchedon
                "Better wait for the popcorn to finish."
            else
                return livingroom
            }
        each_turn   {
                if microwave is switchedon
                    {
                    ""
                    select micropop.misc
                        case 1 : "\"Pop.\" Some kernals are beginning to pop."
                        case 2 : "\"Pop. Pop.\""
                        case 3
                                {
                                "\"Pop. Pop. Pop.\""
                                PhoneCall
                                microwave is not switchedon
                                remove micropop
                                move popped to microwave
                                }
                    }
                }
        after
            {
            location DoListen
                {
                if microwave is switchedon
                    {
                    if micropop.misc < 2
                        {
                        "You can hear the quiet hum of the microwave."
                        }
                    else
                        "You can hear the hum of the microwave and the occasional
                        popping of corn."
                    }
                else
                    return false
                }
            location DoSmell
                {
                if micropop.misc < 2
                    {
                    return false
                    }
                elseif micropop.misc < 3
                    "The air begins to smell of popcorn."
                else
                    "The smell of fresh popcorn permeates the air."
                }
            }

    }

    object microwave "microwave"
    {
        article "the"
        noun "microwave" "oven"
        adjective "microwave"
        long_desc
            {
            "Ah, time-saving applications. How you love them! This is one of those
            fancy models where all you have to do is put food into it and turn it on.
            It is currently ";
            if self is open
                {
                "open ";
                }
            else
               "closed ";
            "and ";
            if self is switchedon
                {
                "on";
                }
            else
                "off";
            "."
            }
        short_desc
             "All that is worth noting is the microwave that sits on an
            unimplemented shelf."
        before
            {
            object DoOpen
                {
                    if self is switchedon
                        "You better wait for it to finish popping first."
                    else
                        return false
                }
            object DoSwitchOn
                {
                    if parent(micropop) ~= self
                        "Nothing in the microwave needs zapping!"
                    else
                        {
                        if self is open
                            {
                            "(closing the microwave first)"
                            self is not open
                            }
                        "You turn on the microwave."
                        self is switchedon
                        }
                }
            object DoSwitchOff
                {
                if self is switchedon
                    "Nah, it'll turn off by itself."
                else
                    return false
                }
            }
        after
            {
            object DoListen
                {
                if switchedon
                    "Hum."
                else
                    return false
                }

            xobject DoGet
                {
                if object = popped
                    {
                    "You pull the popcorn out of the microwave and pour it into a bowl
                    you had lying around. You are no longer lacking in popcorn!\n"
                    "You remember your mysterious caller for a moment, but whatevs- out of sight, out of mind."
                    Acquire(you, popped)
                    }
                else
                    return false
                }
            }
        in startlocation
        capacity 100
        is container transparent switchable static openable
    }

    object popped "popped popcorn"
    {
        article "some"
        noun "popcorn" "bowl"
        adjective "of" "popped" "freshly-popped"
        long_desc
            "Perfectly-popped popcorn. Hooray!"
        before
            {
            object DoDrop
                {
                "Not after all of that \Iwork\i, you don't."
                }
            object DoEat
                {
                "Better wait until you're on the couch."
                }
            object DoSmell
                {
                "Smells num-num-derful!"
                }
            }
    }

    object micropop "uncooked microwave popcorn"
    {
        article "some"
        adjective "uncooked" "microwave"
        noun "packet" "popcorn"
        long_desc
            "This is one of those packets of microwave popcorn, all ready to be
            microwaved."
        in startlocation
        size 5
        misc 0
        before
            {
            object DoEat
                {
                "It'd be best to microwave it first."
                }
            object DoOpen
                {
                "The packet is already unwrapped. It's all ready to be
                microwaved!"
                }
            }
        short_desc
            "A packet of microwave popcorn lies here unawares."
        is openable
    }

    event in microwave
    {

        if microwave is switchedon
            {
            event_flag = 2
            "The microwave hums away."
            micropop.misc = ++micropop.misc
            }
    }

    room livingroom "Living Room"
    {
        long_desc
            {
            "This room has two things that you love dearly, locked in an eternal
            cage match for your affection. In one corner, there's the TV that holds
            all of the movies and shows you love. In another corner (well, actually,
            the middle of the room), there's the couch upon which you like to
            sprawl.\n"
            Indent
            "The kitchen is to the west. The patio is to the east."
            if patiolight is special
                {
                ""
                }
            }
        w_to
            {
            if not 2iswon
                return startlocation
            else
                "You aren't hungry for anything else, and dishes can wait until
                tomorrow."
            }
        e_to
            {
            "Nah, this is your night \Iin\i."
            }
        d_to
            {
            "(sitting down on the couch)"
    !       if parent(player) = couch
    !           {
    !           "You are already sitting down."
    !           }
    !       else
                Perform(&DoEnter, couch)
            }
        each_turn
            {
            if player in couch and tv is switchedon and popped in player
                {
                1iswon = true
                SaveConfig
                "\nArmed with popcorn with the TV on, sitting on your favorite seat in
                the house, you are ready for a relaxing night in!"
                endflag = 1
                }
            }
        before
            {
            location DoEnter
                {
                if (not object) or object = d_obj
                    {
                    object = couch
                    return false
                    }
                else
                    return false
                }
            }
    }

    event in livingroom
    {
        if not 2iswon
            return false
        if phone is special
            {
            phone.misc++
            select phone.misc
                case 1: "\nYour phone starts ringing."
                case else : "\nYour phone is ringing. Maybe you should answer it?"
            }
    }

    object bowl "empty bowl"
    {
        article "an"
        adjective "empty"
        noun "bowl"
        long_desc
            "Man, that popcorn was \IYUM\i."
        before
            {
            object DoEat
                {
                "The popcorn is long gone."
                }
            object DoSmell
                {
                "There's the faint reminder of popcorn."
                }
            }
    }

    scenery patiolight "patio lights switch"
    {
        article "the"
        adjective "patio" "light" "lights"
        noun "light" "switch"
        is switchable
        in livingroom
        before
            {
            object DoSwitchOn
                {
                if self is not special
                    "You have no reason to turn on the patio lights."
                else
                    {
                    "With great trepidation, your shaky finger reaches for the patio
                    light switch. Your curiosity eventually overcomes your fear, and the
                    intensity of the situation is punctuated by the switch's
                    \"CLICK.\"\n"
                    "The patio is flooded with light, and with horror, you see that
                    somebody has set up your garden chairs in several rows holding giant
                    letter signs that, altogether, read, \"HAPPY HALLOWEEN!\" What kind
                    of madman would do that?\n"
                    "Oh, well, the important thing is-"
                    self is switchedon
                    endflag = 3
                    }
                }
            }
    }

    scenery patio "patio"
    {
        article "the"
        noun "patio"
        is enterable
        before
            {
            object DoEnter
                {
                return livingroom.e_to
                }
            }
        in livingroom
    }

    scenery tv "television"
    {
        article "the"
        noun "tv" "television"
        is switchable
        long_desc
            "Your trusty TV."
        in livingroom
        before
            {
            object DoSwitchOn
                {
                if 2iswon
                    "You have already watched enough TV for tonight."
                else
                    return false
                }
            }
        after {
            object DoSwitchOn
                {
                "You turn the TV on, ready for a night of watching scary movies."
                }
            object DoSwitchOff
                {
                "You turn the TV off."
                }
            }
    }

    scenery couch "couch"
    {
        article "the"
        noun "couch"
        is platform enterable
        long_desc
            "Your trusty couch."
        in livingroom
        before
            {
            object DoEnter
                {
                if 2iswon
                    "You have already watched enough TV tonight."
                elseif tv is not switchedon
                    {
                    "The TV isn't on yet!"
                    }
                elseif parent(popped) ~= you
                    {
                    "You don't have any popped popcorn!"
                    }
                else
                    return false
                }
            }
        after
            {
            object DoEnter
                {
                "You plop down on the couch. Ahhhhhh!"
                }
            }
    }

    object movie
    {
    misc 0
    }

    !:: Misc. routines
    routine PhoneCall
    {
        "Suddenly, your phone rings. You answer it.\n"
        Indent
        "\"Hello?\" you say.\n"

        "A voice full of gravel and malice answers you with a question, \"WHAT'S YOUR FAVORITE SCARY IF GAME??\"\n"

        "Huh, good question.\n"
        if (glk)
            GlkName()  ! do the glk-interpreter method of getting IF title
        else
            {
            Font(PROP_OFF)
            ScaryCoolPrompt
            Font(DEFAULT_FONT)
            }
    !   WriteNameToDict
        Indent
        "\"";
    !   print movie.name ;
        StringPrint(name_array)
        ",\" you say.\n"
        "Ding! The microwave beeps.\n"
        Indent
        "\"Popcorn's done! Gotta go!\" you say, hanging up on your probably-perplexed caller.\n"
        microwave is open
        "You open the microwave, revealing some freshly-popped popcorn."
        AssignPronoun(popped)
    }

    !:: The non-glk method of entering the 'scary IF' text
    routine ScaryCoolPrompt
    {
    word[1] = ""
    while (word[1] ~= "yes", "y")
        {
        ClearArray(name_array)
        DrawWindows
        Font(DEFAULT_FONT)
        if (name_array[0] ~= 0)
            {
            print "\"";
            StringPrint(name_array)
            "\#148? Is that correct? ";
            word[1] = ""
            if (not YesOrNo)
                {
                ""
                ClearArray(name_array)
                }
            }
        }

        ""
        "(Okay, good.)"
        ""
    }

    routine DrawWindows
    {
        run border_window.win_init
        window
        {
        run border_window.win_clear
        }
        run border_window.win_end
        run text_window.win_init
        window
        {
        run text_window.win_clear
        Font(PROP_OFF)
        locate 2,1

        "ENTER FAVORITE SCARY IF GAME TITLE:"
        locate 3,3
        FakePrompt(name_array)
        Font(DEFAULT_FONT)
        run text_window.win_clear
        }

        run text_window.win_end
        run cover_window.win_init
        window
        {
        run cover_window.win_clear
        }
        run cover_window.win_end
        window 0
        PrintStatusLine
    }

    window_class cover_window!  window to cover everything when we are done
    {
        win_left
            return (display.screenwidth / 2 - 22) ! leftmost column
        win_top
            return (display.screenheight /2 - 3)! topmost row
        win_right
            return (display.screenwidth / 2 + 22) !rightmost column
        win_bottom
            return (display.screenheight /2 + 2) ! bottommost row

        win_textcolor
            return BGCOLOR    ! text color for any output
        win_backcolor
            return BGCOLOR    ! background color

    }

    window_class border_window! window providing the border
    {
        win_left
            return (display.screenwidth / 2 - 22) ! leftmost column
        win_top
            return (display.screenheight /2 - 3)! topmost row
        win_right
            return (display.screenwidth / 2 + 22) !rightmost column
        win_bottom
            return (display.screenheight /2 + 2) ! bottommost row

        win_textcolor
            return BGCOLOR    ! text color for any output
      win_backcolor
            return SL_TEXTCOLOR    ! background color

    }

    window_class text_window ! window where text will go
    {
        win_left
            return (display.screenwidth / 2 - 21) ! leftmost column
        win_top
            return (display.screenheight /2 - 2)! topmost row
        win_right
            return (display.screenwidth / 2 + 21) !rightmost column
        win_bottom
            return (display.screenheight /2 + 1) ! bottommost row

        win_textcolor
            return TEXTCOLOR   ! text color for any output
        win_backcolor
            return BGCOLOR    ! background color
    }

    routine FakePrompt(array_to_fill)
    {

        local a, key, letters,c,r,f
        c = display.cursor_column
        r = display.cursor_row
        array array_to_fill[0] = 0
        for (f = 0;f< array array_to_fill[] ; f++ )
            {
            array array_to_fill[f] = 0
            }

        while not key
            {
                locate c, r
                a++
                key = system(READ_KEY)
                if key = ENTER_KEY
                    {
                    Asteriskcheck(a,c,r)
                    break
                    }
                elseif key = 8 or key = 516 ! should be backspace
                    {
                    if (letters and display.cursor_column = 1)
                        {
                        Asteriskcheck(a,c,r)
                        c = display.linelength !- 1
                        locate c, --r
                        print " ";
                        array array_to_fill[--letters] = 0
                        locate --c
                        }
                    elseif (letters)
                        {
                        print " ";
                        array array_to_fill[--letters] = 0
                        locate (c - 1)
                        print " ";
                        locate --c
                        }
                    }
                elseif key > 31 and key < 127
                    {
                    if ((display.cursor_column + 1) < display.linelength)
                        {
                        array array_to_fill[letters++] = key
                        printchar key
                        c++
                        if (a>50)
                            print "*";
                        locate c
                        }
                    elseif ((display.cursor_row ) < display.windowlines)
                        {
                        Asteriskcheck(a,c,r)
                        c = 2
                        r++
                        locate c,r
                        array array_to_fill[letters++] = key
                        printchar key
                        c++
                        if (a>50)
                            print "*";
                        locate c,r
                        }
                    }
                    if a=50
                        {
                        print "*";
                        }
                    elseif a = 100
                        {
                        Asteriskcheck(a,c,r)
                        a = 0
                        }
                    system_status = 0
                    key = 0
                    system(PAUSE_100TH_SECOND)
            }
    }
        routine Asteriskcheck(a_position,cursor,row)
        {
            if (a_position>50)
                {
                print " ";
                locate (cursor)
                return true
                }
        }

    !:: The glk method of entering the 'scary movie' text
    routine GlkName()
    {
        ClearArray(name_array)
        GetInput("ENTER FAVORITE SCARY IF GAME IN QUOTES>")
        while true
            {
            local len

            len = string(name_array, parse$, 270)    ! maximum 49 char.
            if (word[1])
                {
                len = string(name_array, word[1], 270)
                }

             if not len
                {
                "No, really, what's your favorite scary IF game?"
                GetInput("FAVORITE SCARY IF GAME IN QUOTATION MARKS>")
                }
            else
                {
                Lowercase(name_array)
                CapitalizeFirstLetter(name_array)
                "\"";
                StringPrint(name_array)
                "\"? Is that correct (did you remember the quotation
                marks?)?"
                word[1] = ""
                if (YesOrNo)
                    {
                    "(Okay, good.)"
                    ""
                    break
                    }
                else
                    {
                    ClearArray(name_array)
                    GetInput("FAVORITE SCARY IF GAME IN QUOTATION MARKS>")
                    }
                }
            }
    }

    routine Lowercase(stringarray)
    {
        local len, i
        len = StringLength(array stringarray)
        for (i=0; i<len; i=i+1) ! the actual case-conversion loop
            {
            if array stringarray[i] >= 'A' and array stringarray[i] <= 'Z'
                array stringarray[i] = array stringarray[i] + ('a'-'A')
            }
    }

    routine CapitalizeFirstLetter(stringarray)
    {
        local len, i, new
        len = StringLength(array stringarray)
        for (i=0; i<len; i=i+1) ! the actual case-conversion loop
            {
            if new or i=0
                {
                if array stringarray[i] >= 'a' and array stringarray[i] <= 'z'
                    array stringarray[i] = array stringarray[i] - ('a'-'A')
                new = 0
                }
            elseif array stringarray[i] >= 'A' and array stringarray[i] <= 'Z'
                array stringarray[i] = array stringarray[i] + ('a'-'A')

            if array stringarray[i] = ' '          ! a space
                new = 1
            }
    }

    !:: routines used by both methods
    routine ClearArray(array_to_clear)
    {
        local f
        for (f = 0;f< array array_to_clear[] ; f++ )
            {
            array array_to_clear[f] = 0
            }
    }

    !routine WriteNameToDict
    !{
    !        movie.name = dict(name_array, 270)
    !}

    !:: Configuration routines
    array name_array[270]

    routine LoadConfig
    {
        local test2
        readfile "gamedata"
            {
            local a
            for (a=0;a<=49;a++)
                {
                name_array[a] = readval
                }
        !   movie.name = dict(name_array, 49)
            1iswon = readval
            2iswon = readval
            test2 = readval
          }
       if test2 ~= FILE_CHECK
            {
      !        print "Error reading file."
          }
    }

    routine SaveConfig(intro)
    {
        local test2
        writefile "gamedata"
            {
            local a
    !       text to name_array
    !       print movie.name;
    !       text to 0
            for (a=0;a<=49;a++)
                {
                writeval name_array[a]
                }
            writeval 1iswon
            writeval 2iswon

            test2 = FILE_CHECK
            writeval test2
            }
         if test2 ~= FILE_CHECK  ! if the program didn't get this far, we know
              {          ! something is wrong
                 if (intro)
                    {
                    !\
                    "The game detects that you are playing this Hugo file in a glk
                    environment. \IThe Halloween Horror\i will \Bnot\b play correctly in
                    Gargoyle. Push \"Q\" to quit if you are using Gargoyle. Otherwise,
                    push any other key to continue." \!
                    "A cursory test indicates that this interpreter does not support the
                    saving of configuration files, a required feature for
                    \IThe Halloween Horror\i. Maybe now would be a good time to try Hugor (http://ifwiki.org/index.php/Hugor)!\n"

                    "PRESS ANY KEY TO QUIT"
                     pause
                     quit
                    }
                else  ! this other case will probably never be called
                    {
                     ""
                     print "\B[ SETTINGS COULD NOT SAVE. YOU ARE NOT USING AN
                                 INTERPRETER CAPABLE OF THIS GAME. ]\b"
                    }
              }
    }

    routine FlushSettings
    {
        writefile "gamedata"
        {
        local a,test2
        for (a=0;a<=49;a++)
            {
            writeval 0
            }
        writeval 0
        writeval 0

        test2 = FILE_CHECK
        writeval test2
        }
    }

    !:: Verb routines
    routine DoAnswer
    {
        if phone is not special
            "Your phone is not ringing."
        else
            {
            phone is not special
            "You answer the phone. You are greeted by the same ominous voice.\n"

            "\"You know, it is rude to hang up on people like that! Just the same,
            I've got a surprise for you. Turn on your patio lights!\" the voice
            commands.\n"

            "The line goes dead."
            patiolight is not hidden
            patiolight is special
            }
    }

    routine DoCall
    {
        "You have no one to call."
    }

    routine DoSmell
    {
        if not object
            {
                if not location.after
                    {
    !               VMessage(&DoListen, 1)  ! "Be a little more specific..."
                    "You don't smell anything of note."
                    return true
                    }
                verbroutine = ""
                return true
            }
        elseif not object.after
            "You can't discern any smell."
    !       VMessage(&DoListen, 2)   ! "Not making any sound..."
        ! we have to clear verbroutine or else location.after.DoListen will run again
        verbroutine = ""
        return true
    }

    routine DoHooray
    {
        "Yes, hooray!"
        return false
    }

    routine DoAbout
    {
        MakeMenu
    }

    routine DoVersion
    {
        color LIGHT_RED
        Font(BOLD_ON)
        if not 2iswon
            "The Halloween Horror"
        else
            "The Halloween Horror Part II"
        Font(BOLD_OFF)
        color TEXTCOLOR
        "by Roody Yogurt"
        print "Release 1 / ";
        print BANNER
        print "IFID: "; IFID
        "Type \BABOUT\b for more info"
    }

    routine DoFlush
    {
        "Restart the game and flush all of the settings? ";
        if (YesorNo)
            {
            FlushSettings
            if not restart
                VMessage(&DoRestart, 2)  ! "Unable to restart."
            }
        else
            "Ok, then."
    }

    !:: Menu stuff
    object main_menu "The Halloween Horror"
    {
        title_gap 1
        options_gap 1
    }

    option history_choice "History"
    {
        in main_menu    ! which menu it is
        menu_text   {
                ""
                "_ This game was originally released as \"The Ecto Horror\" on the sly
                in 2011. It was written for Duncan Bowsman's EctoComp, but
                as it was written the day \Iafter\i games were due, it was not an
                official submission.\n"
                "_ A couple of the ideas for the game were first intended for a
                submission to the Saugus Comp (http:/www.saugus.net), an annual
                Halloween game contest, but the Saugus Comp only accepts games compiled
                to z-code so the ideas were shelved.\n"
                "_ Anyhow, I am glad to clean up some of the problems with the
                original release, which was written in 5 hours, breaking \Ianother\i
                one of
                the EctoComp's rules (although I like to think that this game
                counts as more than one game, teehee). Hopefully, it'll bring
                some entertainment to more people now that it is more likely to work
                correctly.\n"
                CoolPause(1)
                }
    }

    option commands_choice "Special Commands"
    {
        in main_menu    ! which menu it is

        menu_text   {
                ""
                "_ This game saves a configuration file. To clear this file and
                begin the game with a clean slate, type >FLUSH.\n"
                CoolPause(1)
                }
    }

    option credits_choice "Credits"
    {
        in main_menu    ! which menu it is

        menu_text   {
                ""
                "First, I'd like to thank Kent Tessman for providing the Hugo
                system and its library!\n"
                "Thanks to Mike Snyder for laying down the groundwork for such
                things like optimising games for glk interpreters and other little
                tips and tricks.\n"
                "Thanks to Royce Odle for hosting and setting up Hugo by Example,
                the best Hugo code repository on the net!\n"
                "Thanks to Robb Sherwin for setting a great example for all other
                Hugo authors!\n"
                "Thanks to the people at ClubFloyd ( http://www.ifwiki.org/index.php/ClubFloyd ) and Paul Lee for giving me
                transcripts, resulting in the slightly-more-polished game you have
                before you!\n"
                "Lastly, thanks to \Byou\b for playing this!\n"
                CoolPause(1)
                }
    }

    option contact_choice "Contact"
    {
        in main_menu    ! which menu it is

        menu_text   {
                ""
                "_ Feel free to send me your thoughts and suggestions at
             roody.yogurt@gmail.com! What an amazing discourse we will
             have!\n"
                CoolPause(1)
                }
    }

    object special_menu "Special Notes"
    {
        title_gap 1
        options_gap 1
    }

    option movie_choice "\IWhat was the deal with the movie? I beat it on my first try!\i"
    {
        in special_menu    ! which menu it is

        menu_text   {
                ""
                "The concept behind the mid-game is that if the player uses \BUNDO\b
                or \BSAVE\b, the game becomes unwinnable (usually).\n"
                "So, not exactly fair, but I just wanted to do something that'd make
                people scratch their heads for a while.\n"
                CoolPause(1)
                }
    }

    option killer_choice "\IWhat was the deal with the sleeping killer guy?\i"
    {
        in special_menu    ! which menu it is

        menu_text   {
                ""
                "That part is a silly homage to the horror game \"House of the
                Stalker\" by Jason Clayton White. ";
                "In that game, you also dispense of the bad guy in somewhat odd
                circumstances.\n"
                CoolPause(1)
                }
    }

    option files_choice "\IWhy break the game into two files?\i"
    {
        in special_menu    ! which menu it is

        menu_text   {
                ""
                "It is true that the game could easily have been coded all
                in one file. The two-file design
                was mostly a proof-of-concept thing (although I \Ido\i think
                that without the gimmick, the resulting movie name in the
                midgame would be that much less cool).\n"
                "I hope people don't mind too much.\n"

                CoolPause(1)
                }
    }

    option code_choice "\IIs the code for this game available somewhere?\i"
    {
        in special_menu    ! which menu it is

        menu_text   {
                ""
                "Why, yes, it is! Go check out the \"Example Games\" section
                at Hugo by Example ( http://hugo.gerynarsabode.org ).\n"

                CoolPause(1)
                }
    }
