---
title: The Underoos That Ate New York
permalink: /example-games/underoos-that-ate-new-york/
categories: 
  - Example Games
---

    !::
    ! The Underoos That Ate New York
    !
    !:: Flags
    #set DEBUG
    #set VERBSTUBS           ! Include the grammar and routines from verbstubs.g and verbstubs.h, respectively
    !#set USE_ATTACHABLES     ! Use attachable items
    !#set USE_PLURAL_OBJECTS  ! Use plural objects
    !#set USE_VEHICLES        ! Use vehicle objects
    !#set NO_AUX_MATH         ! No advanced math needed
    !#set NO_MENUS            ! Don't use menus
    !#set NO_RECORDING        ! Don't allow transcripts
    !#set NO_SCRIPTS          ! Don't use character scripts
    !#set NO_STRING_ARRAYS    ! Don't use string arrays


    !:: switches              ! example how one can add compiler switches to source
    !#switches -ls            ! print compilation stats to .LST file

    #ifset DEBUG
    #switches -d
    #endif

    !:: Constants and globals  (some constants must be set before hugolib is included)
    !constant AFTER_PERIOD " "     ! include one space after full stops (as opposed to two)
    !constant INDENT_SIZE 0        ! no indentation in room descriptions and room content listings
    !constant IFID "put-IFID here"

    !:: Includes (grammar must come first)
    ! put your new grammar here

    ! new grammar needs to be defined before the including verblib
    #include "verblib.g"    ! Verb Library

    #include "hugolib.h"    ! Standard Hugo Library

    !:: Game Initialization routine
    routine init
    {
        STATUSTYPE = 1  ! 0 = none :: 1 = score/turns :: 2 = time
        counter = -1    ! 1 step before first turn
        TEXTCOLOR = DEF_FOREGROUND
        BGCOLOR = DEF_BACKGROUND
        SL_TEXTCOLOR = DEF_SL_FOREGROUND
        SL_BGCOLOR = DEF_SL_BACKGROUND
        color TEXTCOLOR, BGCOLOR, INPUTCOLOR

        verbosity = 2   ! 1 = normal (rooms described only if not previously
                        !     described)
                        ! 2 = full (rooms described every time they are entered)

        #ifset DEBUG
        display.title_caption = "Underoos (HugoFix On)"  ! used for GUI clients for title bar text.
        #else
        display.title_caption = "Underoos"
        #endif
        prompt = ">"

        window 0 ! resets the windows in case the player is restarting a game
        cls

        DEFAULT_FONT = PROP_ON
        Font(DEFAULT_FONT)

        !:: Opening Text
        "Yesterday, as you were walking through Central Park, a meteorite crashed
        nearby, bathing you in cosmic radiation. It only made the twelth page of
        the paper, under Dear Abby. Of course, if anyone could have foreseen the
        awful effects of that accident, it surely would have been a front page story.
        But there was no way for you, or anyone else, to predict that the result of
        that accident would be...."
        print ""

        Font(BOLD_ON)
        "The Underoos That Ate New York!"
        Font(BOLD_OFF)
        "An Interactive Quickie by G. Kevin Wilson"
        "(c) 1994. All Rights Reserved."
        "Type 'xyzzy' for help and information."
        print BANNER

        player = you
        location = bedroom

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

    player_character you "you"
    {}

    room bedroom "Your Bedroom"
    {
        long_desc {
            "Home sweet home for a '60s throwback bachelor like yourself. Assorted,
            but unimportant decorations litter the walls and ceiling. To the west
            is a door that, as you fuzzily recall, leads into your walk-in closet.
            To the east is a hallway, that, as you even more fuzzily recall, leads
            to the kitchen."
        }
        e_to {
            if (underoos is hidden) {
                "You don't like the chill wind blowing in off the kitchen tiles.
                Maybe you could at least have a look round for your underoos first?"
            } else {
                return kitchen
            }
        }
        w_to closetdoor
    }


    scenery shazam "bed"
    {
      noun "bed"
      adjective "my"
      article "your"
      long_desc
        "This is your bed."
      in bedroom
      is enterable, platform
      before
      {
        object DoLookUnder
        {
          if player in shazam
            "You lean over the edge and try to peer under the bed, but
            the blood rushes to your head and your eyes refuse to focus."
          elseif (self is not special)
          {
            "You find your Ruby Poo underoos."
            underoos is not hidden
            self is special
          }
          else
          {
            "You don't find anything else."
          }
        }
      }
      w_to closet_door
    }

    object underoos "Ruby Poo underoos"
    {
      noun "underoos", "underwear"
      adjective "ruby", "poo"
      article "your"
      initial_desc {print "You see "; The(self); " here."}
      in bedroom
      is clothing, hidden
      long_desc
      "Ah. Your good ole Ruby Poo underoos. The luckiest of lucky underwear.
      You've worn them every time you've ever gotten lucky. But then, maybe
      that has something to do with never changing them. Naaah."
      before
      {
        object DoGet
        {
          "As you pick your underwear up, something utterly unbelievable
          happens. The underwear begins struggling in your grasp! Finally,
          it bites you on the hand, causing you to drop it. It huddles in
          the corner, growling."
          move liveundies to bedroom
          remove self
        }
      }
    }

    door closet_door "closet door"
    {
      noun "door"
      adjective "closet"
      article "the"
      between closet, bedroom
      before
      {
        object DoOpen
        {
          closet is light
          return false
        }
        object DoClose
        {
          closet is not light
          return false
        }
      }
    }

    scenery decorations "decorations"
    {
      noun "decorations"
      article "the"
      is plural
      in bedroom
      long_desc: "Assorted, but useless."
    }

    room closet "Your Closet"
    {
      long_desc
      "Ah, the cathedral of clothes. Only, um. I wonder why it's empty? The
      exit lies back to the east."
      e_to closet_door
      is not light
    }

    room kitchen "Your Kitchen"
    {
      long_desc
      "Kitchen (ki' chun) n. - A place in which food is prepared. This
      particular ki' chun has a toaster, a fridge, a hallway leading west, a
      dark passageway leading into the cellar, and a hallway leading north to
      the entryway."
      before
      {
        location DoDrop
        {
          if (object is clatters)
          {
            if parent(sock) = toaster
            {
              print "When you drop "; The(object); " it clatters on
              the floor, waking up the socks! They leap from the
              toaster, latching on to you with their terrible elastic
              mouths. Gradually, the venom in their bite overcomes
              you, and you pass out..."
              endflag = 2
            }
            else
            {
              print CThe(object); " clatters noisily on the kitchen
              floor tiles."
              move object to self
            }
          }
        }
      }
      w_to bedroom
      d_to
      {
        if (self is not special and shoes is not worn)
        {
          "As you recall, there's an awful lot of broken glass, rusting
          staples, and the like down there. It would probably be good to
          make sure you're wearing shoes before you go down these stairs.
          But, if you want to chance it anyways, then on your head lies
          the blame."
          self is special
        }
        elseif (deadundies is not worn)
        {
          "You want to walk down into that freezing cellar without even
          the barest of protection?  No way, go put some underwear on."
        }
        else
          return cellar
      }
      n_to entryway
    }

    object broom "broom"
    {
      noun "broom"
      article "a"
      initial_desc: "There is a broom leaning against the counter."
      long_desc
      "Your broom. There is a rubbermade sticker on the end
      of it, near the bristles."
      in kitchen
      is clatters
    }

    component sticker "sticker"
    {
      part_of broom
      noun "sticker", "rubbermade"
      article "a"
      long_desc: "It reads \"Rubbermade\"."
      before {
        object DoGet
        {
          if self.part_of = broom
            "It's stuck to the broom."
          else
          {
            "Respectfully, you pick up the sticker,
            then, on a sudden impulse, you tie it
            around your head, like a bandana. Your
            broom will not go unavenged!"
            move bandana to player
            Activate(bandaemon)
            remove self
          }
        }
      }
    }

    daemon bandaemon
    {}

    event in bandaemon
    {
      local rand
      rand = random(100)
      if bandana is worn and rand <11> 0: ""
    for (i = 0; i < 6; i++) {
      if tasks[i] ~= 0 {
        print "_   1 point for ";
        select i
        case 0: "dodging tetanus";
        case 1: "practicing your karate";
        case 2: "freshening your shoes up";
        case 3: "collecting insects";
        case 4: "defeating the lurking socks";
        case 5: "paying your respects (easter egg)";
        ""
      }
    }
    }

    routine DoSpray
    {
      if object ~= nothing or lysol and xobject = nothing and
        parent(lysol) = player
      {
        print "(with "; The(lysol); ")"
        xobject = lysol
      }

      if xobject = lysol
      {
        xobject = object
        object = lysol
      }

      if object = lysol
      {

        if location = closet and closet_door is not open
        {
          "Probably not a good idea. These aerosols can be lethal in
          small, enclosed areas."
        }
        elseif location = kitchen and sock in toaster
        {
          "The socks are awakened by the hissing of the aerosol can. They
          leap from the toaster in a flash, fastening themselves onto your
          body with their terrible elastic mouths. You struggle mightily
          in their grip, but to no avail. Gradually, the venom from their
          bite drags you down into oblivion."
          endflag = 2
        }
        elseif xobject = liveshoes
          run liveshoes.flee
        else
          "Mmm. Lemon scent!"
      }
      else: print CThe(actor); " can't spray that!"
    }

    routine DoXyzzy
    {
      "A hollow voice says, \"This is a short sample 'game' designed to test
      out some programming ideas I had. It pays homage to the bad old sci-fi B
      movies. The material here is, I suppose, vaguely mystifying to small
      children, so parents be warned, play it through first yourself, and make
      your own decision about it.\""
    }

    ! New non-verb routines

    routine Achieved(task)
    {
      if tasks[task] = 0
        tasks[task] = 1
      score++
    }

    routine NumSP(num, sing, plur)
    {
      print number num; " ";
      if num = 1
        print sing;
      else
        print plur;
    }

    routine Pardon
    {
      print "What?"
    }

    routine PrintRank
    {
    print ". This gives you a rank of: ";
    if monster
    {
      select score
      case 0: "Dirty Mutant";
      case 1: "Shoeless Kong";
      case 2: "Gamera Wearing Matching Socks";
      case 3: "Well Groomed Werewolf";
      case 4: "Fashion Hound of the Baskervilles";
      case 5: "Sharp Dressed Mothra";
      case 6: "Easter Egg Godzilla";
    }
    else
    {
      select score
      case 0: "Dirty Underwear";
      case 1: "Shoeless Joe";
      case 2: "Color Coordinated";
      case 3: "Well Groomed";
      case 4: "Fashion Hound";
      case 5: "Sharp Dressed Man";
      case 6: "Easter Egg Guru";
    }
    print ". "
    }

    ! Replaced routines

    replace PrintEndGame(end_type)
    {
      Font(BOLD_ON)
      select end_type
      case 1
      {
        print "\n* * * Congratulations";
        if secret: ", you've found the secret ending!";
        elseif monster: "... you've won, I guess...";
        else: ", you've won!";
        " * * *"
      }
      case 2
      {
        if player_person = 2
          print "\n* * * You have died! * * *"
        else
          print "\n* * * "; CThe(player); \
            MatchPlural(player, "has", "have"); \
            " died! * * *"
      }

      Font(BOLD_OFF)
      PrintScore(true)
    }

    replace PrintScore(end_of_game)
    {
      print "In a total of ";
      NumSP(counter, "turn", "turns")
      print ", you ";
      if not end_of_game
        print "have ";
      print "solved ";
      NumSP(score, "puzzle", "puzzles")
    if not secret
      PrintRank
    else
      ". As for your score, you found the secret ending.
      That's all that really matters, isn't it?"
    !  ". Plus, you found the secret ending!"
    }

    global dark_warning = 0

    replace DarkWarning
    {
      if not dark_warning
      {
        "It's pitch black! You are likely to be eaten by a sock."
        dark_warning = 1
      } else {
        if random(3) = 1 {
          "Oh no! You walked into the slavering fangs of a lurking sock!"
          endflag = 2
        } else
          "It's pitch black! You are likely to be eaten by a sock."
      }
    }

    replace NewParseError(errornumber, obj)
    {
      local retval = false

      select errornumber

      case 0 {
        Perform(&Pardon, 0, 0, 0, 1)

        retval = true
      }

      return retval
    }
