---
title: Vault of Hugo II
permalink: /example-games/vault-of-hugo-2/
categories: 
  - Example Games
---

This game was written for the [PAX East 2011
Speed-IF](http://www.ifwiki.org/index.php/PAX_East_2011_Speed-IF)
"competition." It took four or five hours to write, as the first several
hours of the competition were used just to come up with a game idea.

### Notes About the Design From The Author

I did not use every topic. Originally, I was going to put Marius Müller
in there and use my altered version of Christopher Tate's converse.h
library contribution to talk to him, but when I realized how little time
I had to implement what I wanted, I dropped that idea and did not
replace it with an easier idea. I wanted to include "Alewife" by
mentioning Community's Dan Harmon, who used to be a member of a comedy
troupe called the Dead Alewives and maybe say something about how
"Braintree" always makes me think about headcrabs. "Chicken fingers" was
omitted when the topic list was first relayed to me (I missed the start
of the Speed-IF) so in my mind, it was not canon. So yeah, due to time
constraints and what not, I did not do all of those things.

I ended up using Kent Tessman's SuperContainer contribution since I had
a desk that I wanted people to put stuff both on and in, although my
final game ended up having so few items to hold that it was most-likely
unnecessary (especially since I don't think I gave the desk a capacity
property so people couldn't actually put things into it). I also made
the floor in one of the rooms a SuperContainer since there was a
compartment in it that people could put stuff in. All poorly coded.

I used my replacement PrintStatusLine routine since I like having the
SCORE / MOVES look nice, but then I ended up turning SCORE / MOVES off
since I didn't want to come up with ranks. Oops!

The title, of course, is a nod to Hugo's sample game, The Vault of Hugo.

### In Retrospect

First off, I should have done a better job describing the typewriter.
Having written the game just before (and during) the IF Demo Fair, I
took for granted that all players would be familiar with [the
Automatypewriter](http://upnotnorth.net/projects/typewriter/), an
electronic typewriter that was programmed to play Zork (the
automatypewriter at PAX East 2011 was actually even more impressive; it
was a 100 year old typewriter rigged up to do the same thing with a
newly written IF game). I didn't make it clear in the game that this
typewriter plays IF games.

As glad as I am to have figured out how to use
[parse$](Parse$) to capture words between quotes (and then
using [StringDictCompare](StringDictCompare)), despite trying
to direct players to `TYPE "GAME COMMAND" ON TYPEWRITER`, many would
ignore the quotes and break my code. I should have also entered the
exact commands into the verb grammar to allow for not-quoted commands,
especially since my in-game typewriter accepts such a limited number of
commands.

Yeah, spell-checking.

I also forgot to give the desk the quiet property so it lists its
contents twice.

Lastly, while I included some ways to intentionally detonate the
landmine, I missed many, including hitting. Oh well.

All in all, it was my first reasonably short Speed-IF so I was glad to
have finished a game!

### The Code Itself

    !::
    ! New Game (Shell)
    !
    !:: Flags
    !#set HUGOFIX             ! Compile with HugoFix Debugging Library commands available (type $? in game)
    !#set HDX                 ! Compile as Hugo Debuggable Executable (see below for details)
    !#set PRECOMPILED_LIBRARY ! Use a precompiled header library (see manual)
    !#set VERBSTUBS           ! Include the grammar and routines from verbstubs.g and verbstubs.h, respectively
    !#set USE_ATTACHABLES     ! Use attachable items
    !#set USE_PLURAL_OBJECTS  ! Use plural objects
    !#set USE_VEHICLES        ! Use vehicle objects
    !#set NO_AUX_MATH         ! No advanced math needed
    !#set NO_FONTS            ! Don't use font effects
    !#set NO_FUSES            ! Don't use fuses
    !#set NO_MENUS            ! Don't use menus
    !#set NO_RECORDING        ! Don't allow transcripts
    !#set NO_SCRIPTS          ! Don't use character scripts
    !#set NO_STRING_ARRAYS    ! Don't use string arrays
    !#set NO_VERBS            ! Don't use any standard verbs
    !#set NO_XVERBS           ! Don't use any standard "out-of-world" verbs


    !:: switches              ! example how one can add compiler switches to source
    !#switches -ls            ! print compilation stats to .LST file

    #ifset HUGOFIX
    #set DEBUG
    #endif

    #ifset HDX
    #switches -d              ! if the -d switch is not set in the compiler itself, #set HDX will produce
                              ! a Hugo Debuggable Executable (.HDX) with extension .HEX
    #endif                    ! Sneaky!

    !:: Constants and globals  (some constants must be set before hugolib is included)
    !constant AFTER_PERIOD " "     ! include one space after full stops (as opposed to two)
    !constant INDENT_SIZE 0        ! no indentation in room descriptions and room content listings
    constant IFID "put-IFID here"

    !:: Includes (grammar must come first)
    ! put your new grammar here
    verb "push","pull"
        * object            DoMove
    verb "clean","vacuum"
        * object            DoVacuum
    verb "load"
        * typewriter            DoPaper
        * typewriter "with" "paper"     DoPaper
        * paper "in"/"into" "typewriter" DoPaper
    verb "type"
        * string            DoType
        * string "on"/"into"/"in" typewriter DoType
    verb "step","stand"
        * "on" landmine         DoStepOn
    verb "depress"
        * object            DoMove
    verb "scrape"
        * "parrot"          DoScrape
    ! new grammar needs to be defined before the including verblib
    #include "verblib.g"    ! Verb Library

    #ifset PRECOMPILED_LIBRARY
    #link "hugolib.hlb"     ! Your Precompiled Library
    #else
    #include "hugolib.h"    ! Standard Hugo Library
    #endif
    #include "contain.h"

    !:: Game Initialization routine
    routine init
    {
            STATUSTYPE = 0  ! 0 = none :: 1 = score/turns :: 2 = time
            counter = -1    ! 1 step before first turn
    !       If STATUSTYPE = 2 (time), counter is minutes since midnight, so a game that starts at 3 pm
    !       should have:
    !       counter = 899
    !       (900 minutes minus the one minute the main routine will add on the first turn)
            TEXTCOLOR = DEF_FOREGROUND
            BGCOLOR = DEF_BACKGROUND
            SL_TEXTCOLOR = DEF_SL_FOREGROUND
            SL_BGCOLOR = DEF_SL_BACKGROUND
            color TEXTCOLOR, BGCOLOR

            verbosity = 2   ! 1 = normal (rooms described only if not previously
                            !     described)
                            ! 2 = full (rooms described every time they are entered)

            display.title_caption = "Vault of Hugo II: Electric Boogaloo"  ! used for GUI clients for title bar text.
            prompt = ">"

            window 0 ! resets the windows in case the player is restarting a game
            cls

            DEFAULT_FONT = PROP_ON
            Font(DEFAULT_FONT)

            !:: Opening Text
            "The future's not what it's cracked up to be! Jetpacks and joybooths are cool and all,
         but you've always had a special place in your heart for history and its artefacts- so
         much that it was long ago that you decided you wanted to be a roguish space pirate
         (way before it was considered cool, in fact).\n"
         "Among the many who had heard the tale of a fabled lost museum devoted to interactive
         fiction, you alone thought the myth was rooted in truth. Perseverence paid off, though,
         and by golly, you found it. Tragicly, you lost your cohorts
        Jim and Kevin to an ill-considered mining
          expedition to Pluto, so you are embarking on this adventure alone.
          You have already ransacked the other wings of the museum. The one thing left
          to do is to crack the..."
            print ""    ! For a blank line between the intro and the game title

            Font(BOLD_ON)
            "Vault of Hugo II: Electric Boogaloo"
            Font(BOLD_OFF)
            "An Interactive Scavenging by Roody Yogurt"
            print BANNER;
            #ifset HUGOFIX
            print " (Now with HugoFix Technology TM!)"
            #else
            print ""
            #endif
     !       print IFID

            player = you
            location = STARTLOCATION

            move player to location
        MoveOnto(desk,typewriter)
        MoveOnto(desk,output)
        MoveInto(desk,paper)
        move landmine to player
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
            PrintStatusLine
            run location.each_turn
            runevents
            RunScripts
            if speaking not in location
                    speaking = 0
    }

    player_character you "you"
    {
        long_desc
            "You are rugged and roguish and space-pirate-tastic."
        before
        {
            actor
            {
                if parent(object).type = SuperContainer
                {
                    if Inlist(parent(object), contents_in, object) and
                        parent(object) is not open
                    {
                        print capital player.pronoun #1;
                        MatchPlural(player, "doesn't", "don't")
                        " see that."
                        return true
                    }
                }
                return false
            }
        }
    }

    room STARTLOCATION "The Hugo Wing"
    {
        long_desc
            {
            if desk not in STARTLOCATION
                {
                "Oh, the humanity! The desk and awesomatic-typewriter have been
                 blown to a better place. Luckily, though, the Hugo Vault door
                 is left hanging on its hinges, leaving the exit north unblocked."
                }
            else
            "This place is pretty amazing. Of course, your attention is mainly
             drawn to the north, where the big Hugo Vault Door keep you from
             its treasures. Also somewhat neat is the desk near it. You came from
             the east, but there was a cave-in just moments ago, trapping you.
             Luckily, there seems to be a room past a tight squeeze to the
             southwest."
             }
        n_to    {
            if desk in STARTLOCATION
                {
                "The massive Hugo Vault door blocks your progress."
                }
            else
                {
                "Whistling a happy tune, you walk though the smoking debris,
                 onward to happiness and success and more effective roguishness!"
                 endflag = 1
                 }
            }
        sw_to   {
            if child(player) ~= 0
                "You'd never make that squeeze while carrying anything!"
            else
                {
                "It's a tight fit, but you make it, finding yourself in..."
                return tomb
                }
            }
        e_to    {
            "The way back to the ALAN Wing has been blocked by a cave-in.
            Those plaques written in Comic Sans are inaccessible to you for now."
            }
    }

    replace PrintStatusline
    {
        if display.linelength < 80
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
    ! The part we're changing
    !           print to 65;
    ! Ok, let's begin writing to array "_temp_string"
    ! _temp_string is an array declared by the library if NO_STRING_ARRAYS is not set
                            {
                            text to _temp_string
                    if STATUSTYPE = 1
                        print number score; " / "; number counter;
                    elseif STATUSTYPE = 2
                        print HoursMinutes(counter);
                text to 0
    ! Ok, we've closed off the string array
    ! Now, let's move to the end of the screen MINUS the length of the _temp_string array
    ! plus two extra spaces for good measure (so there's a little space to the right on the status bar)
                print to (display.screenwidth - (StringLength(_temp_string) + 2));
                            }
            else
            {
                locate 1, 2
                if FORMAT & DESCFORM_F:  print "_";
            }

            if STATUSTYPE = 1
                print number score; " / "; number counter;
            elseif STATUSTYPE = 2
                print HoursMinutes(counter);
        }
        color TEXTCOLOR, BGCOLOR
        Font(DEFAULT_FONT)
    }

    object vault "vault door"
    {
        article "the"
        in STARTLOCATION
        adjective "vault","giant","huge"
        noun "vault","door"
        long_desc
            {
            if desk in STARTLOCATION
                "This thing is the real deal. There's no way you're getting this bad boy open
                 without some serious firepower."
            else
                "Oh, it is a Hugo shell of its former self, but it was for the greater good."
            }
        before
            {
            object DoEnter
                {
                Perform(&DoGo,n_obj)
                }
            }
        is static, hidden, enterable
    }

    SuperContainer desk "desk"
    {
        article "the"
        noun "desk"
        in STARTLOCATION
        long_desc
            "This is quite a sturdy work desk. On top of it is a typewriter, and behind
            the typewriter is an output tray for sheets of paper to fall into."
        is static, openable, hidden
    }

    object drawers "drawers"
    {
        article "some"
        noun "drawers"
        part_of desk
        before
            {
            object DoOpen
                {
                Perform(&DoOpen,desk)
                }
            object DoClose
                {
                Perform(&DoClose,desk)
                }
            }
        is openable, hidden
    }

    object typewriter "100 year old awesomatic-typewriter"
    {
        article "the"
        adjective "100","year","old","awesomatic"
        noun "automatypewriter","typewriter","awesomatic-typewriter","typewriter"
        long_desc
            "Unbelievable! Everybody remembers the \"automatypewriter\" that
             predates this one, but not many remember the Awesomatic-Typewriter that
             came much later, playing only Hugo games. This one seems to be in the
             middle of a game of \"Quest For Museum\" and is currently waiting for a
             command. If you feel up to the challenge, TYPE \"COMMAND\" ON TYPEWRITER."
        before
            {
            object DoGet,DoMove
                {
                "Either it's really heavy or bolted to the desk. You can't
                move it and are too lazy to investigate exactly why."
                }
            xobject DoPutIn
                {
                if object = landmine
                    {
                    "The landmine is much too thick to put in the typewriter."
                    return true
                    }
                else
                return false
                }
            }
    }

    object sheet "sheet of paper"
    {
        article "a"
        adjective "sheet","of"
        noun "sheet","paper"
        long_desc
            "The paper in the awesomatic-typewriter has some printed text but not much."
        before
            {
            object DoGet
                {
                "Nah, then you'd just have to replace it with another piece of paper!."
                }
            }
        in typewriter
        is readable
    }

    object output "output tray"
    {
        long_desc
            "The output tray seems more than capable of catching any 8 by 10 inch piece of paper
             that falls into it."
        article "an"
        adjective "output"
        noun "output","tray","bin"
        is static, container
        capacity 10
    }


    object paper "sheaf of paper"
    {
        long_desc
            "Lots of sheets of Feather Light Brand Paper."
        article "a"
        adjective "sheaf","of"
        noun "sheaf","paper","sheets"
        before
            {
            object DoGet
                {
                if sheet in typewriter
                    {
                    "There is no need to grab more paper while the typewriter still has paper in it."
                    return true
                    }
                if infodump.tick
                    {
                    "The typewriter is still printing!"
                    return true
                    }
                "You grab a blank sheet of paper and load it up into the typewriter. It automatically
                 prints a line of text and waits with a new prompt."
                 move sheet to typewriter
                 return true
                 }
            object DoPutIn
                {
                if xobject = typewriter
                    {
                    if sheet in typewriter
                        {
                        "There is no need to grab more paper while the typewriter still has paper in it."
                        return true
                        }
                    if infodump.tick
                    {
                    "The typewriter is still printing!"
                    return true
                    }
                    "You grab a blank sheet of paper and load it up into the typewriter. It automatically
                     prints a line of text and waits with a new prompt."
                    move sheet to typewriter
                     return true
                     }
                 else
                    return false
                }
            }
    }

    object landmine "landmine"
    {
        article "a"
        adjective "land"
        noun "landmine","mine"
        long_desc
            "The only thing you have left- after using all of your good ordnance raiding this museum-
             is your trusty landmine.
             With its hair-trigger mechanism, it'll explode at a moment's notice. It may not
             be the safest kind of landmine to carry around on one's person, but hey, they are
             among the cheapest! It is roughly 8 by 10 inches in length and fires powerful
             shrapnel in all directions."
        size 9
        before
            {
            object DoStepOn
                {
                if parent(landmine)= STARTLOCATION
                    {
                    "Like a genius, you chortle to yourself and
                     hop onto the landmine."
                     endflag = 4
                     }
                else
                    "The landmind ought to be on the floor."
                    return true
                }
            object DoMove
                {
                if word[1] = "press","push"
                    {
                    "\"Gee, I wonder what this button does...\""
                    endflag = 4
                    }
                }
            }

    }

    object floor2 "floor"
    {
        article "the"
        noun "floor"
        is static, hidden
        in STARTLOCATION
    }

    room tomb "The Tomb of the Unknown Tool"
    {
        long_desc
            "What a weird place. Some graffiti lines the concrete walls, but the real
             star of the room is the little creepy coffin at its center. Also, did I
             mention that the floor is dusty?"
        after
            {
            location DoGo
                {
                if sheet in output
                    {
                    "/nNoticing a full sheet of game transcript in the output tray,
                     you roll it into a ball and throw it away- NEVER TO BE SEEN
                     AGAIN."
                     remove sheet
                     }
                }
            }
        ne_to   {
            if child(player) ~= 0
                "You'd never make that squeeze while carrying anything!"
            else
                {
                "It's a tight fit, but you make it, finding yourself in..."
                return STARTLOCATION
                }
            }
    }

    object coffin "coffin"
    {
        article "the"
        adjective "little","creepy"
        noun "coffin","lid"
        long_desc
            {
            "Creepy! Little! Coffin! It is ";
            if self is open : "open." :  else : "closed."
            }
        in tomb
        before
            {
            object DoOpen
                {
                if self is not special
                    {
                    "Scary stuff! With great trepidation, you slowly
                    open up the coffin's lid. Shockingly enough,
                    the contents are revealed to be a hand vacuum
                    (a dustbuster, ya know?). Somebody here had a sense of
                    humor."
                    self is special
                    tomb.name = "The Tomb of the Known Tool"
                    coffin is open
                    dustbuster is known
                    return true
                    }
                else
                return false
                }
            }
        is static, container, openable, hidden
    }

    object dustbuster "dustbuster"
    {
        article "a"
        adjective "hand"
        noun "dustbuster", "vacuum"
        long_desc
            "Whoa! It's a dustbuster just like in the Inform 6 classic, \"Death To My
             Enemies!\" You're pretty sure this particular model is hugely famous in
             Austria."
        in coffin
    }

    SuperContainer floor "floor"
    {
        long_desc
            "What a horribly dirty floor! Where's the abandoned museum cleaning staff?"
        article "the"
        adjective "dusty"
        noun "floor","dust"
        before {
            object DoVacuum
                {
                if self is not special
                    {
                    if dustbuster is not known
                        {
                        "You have nothing to vacuum with!"
                        return true
                        }
                    elseif FindObject(dustbuster,tomb) and parent(dustbuster) ~= player
                        {
                        "(Picking up the dustbuster first)"
                        move dustbuster to you
                        }
                    "In a fit of dustbusting fever, you attack the dusty floor
                     with the dustbuster. Your efforts are rewarded by revealing
                     a trapdoor. Huzzah!"
                     move trapdoor to tomb
                     self is special
                     return true
                     }
                return false
                }
            }
        is static, hidden,open
        in tomb
    }

    object trapdoor "trapdoor"
    {
        short_desc
            {
            "In the center of the floor is ";
            if self is open : "an open "; :  else : "a closed ";
            "trapdoor."
            }
        long_desc
            {
            "Wonder of wonders, a trapdoor! It is ";
            if self is open : "open.": else : "closed."
            }
        article "the"
        adjective "trap"
        noun "trapdoor","door"
        is static, openable, container
    }

    object cheat "game walkthrough"
    {
        article "a"
        adjective "game"
        noun "walkthrough"
        long_desc
            "Somebody hid away this walkthrough for the game \"Quest
             For Museum.\" There are lots of little comments making snide
             remarks about the game itself. Interestingly, there's a note
             that the command >SCRAPE PARROT at any point results in the
             biggest infodump in the game."
        is readable
        in trapdoor
    }

    object graffiti "graffiti"
    {
        noun "graffiti"
        in tomb
        long_desc
            "It reads, \"Don't you hate spelling 'graffiti' right in
            IF games???\""
        is static, hidden
    }

    routine DoVacuum
    {
    !  When I wrote this game, I did not understand what CheckReach is good for.
    !  This is bad code and should be ignored.
        !if parent(dustbuster) = you
        !"The "; object.name;" is dust-busted!"
        if not CheckReach(dustbuster)
            {
            "You have nothing to vacuum with!"
            return true
            }
        elseif CheckReach(dustbuster) and parent(dustbuster) ~= player
            {
            "(Picking up the dustbuster first)"
            move dustbuster to you
            }
        if object = you
            "You are dust busted enough."
        elseif object = dustbuster
            "Wise guy, eh?"
        else
            print "The "; object.name; " is slightly more dust-busted."
        return true
    }

    routine DoPaper
    {
        if CheckReach(paper)
            {
                        if sheet in typewriter
                        {
                        "There is no need to grab more paper while the typewriter still has paper in it."
                        return true
                        }
                    if infodump.tick
                    {
                    "The typewriter is still printing!"
                    return true
                    }
                    "You grab a blank sheet of paper and load it up into the typewriter. It automatically
                     prints a line of text and waits with a new prompt."
                    move sheet to typewriter
                     return true
            }
        elseif sheet in typewriter
            {
            "The typewriter is already loaded."
            return true
            }
        "You see no paper here."
        return true
    }

    array command[20]

    routine DoType
    {
        if player in tomb
            {
            "There is nothing to type on here!"
            return true
            }
                    elseif infodump.tick
                    {
                    "The typewriter is still printing!"
                    return true
                    }
        elseif sheet not in typewriter
            {
            "You'll have to load the typewriter up with some paper first."
            return true
            }
        string(command, parse$, 20)
        if StringDictCompare(command, "scrape parrot") = 0
            {
            Typewrite()
            return true
            }
        else
        "The awesomatic-typewriter prints a pithy response, leaving lots
         of blank sheet yet."
    }

    fuse infodump
    {}

    event infodump
    {

            if not self.tick
                {
                event_flag= true
                if landmine in output and you in STARTLOCATION
                    {
                    "\nLike an idiot, you watch while the page
                     falls lightly onto the landmine."
                     endflag = 3
                     }
                elseif landmine in output and you in tomb
                    {
                    "\nBOOM! You hear a deafening explosion from the other room!"
                    remove desk
                    }
                elseif you in STARTLOCATION
                    {
                    "\nThe page finishes printing and falls into the output
                     tray without much fanfare. Uninterested with the result,
                     you instantly throw the paper away- NEVER TO BE SEEN AGAIN."
                     remove sheet
                     }
                else
                    {
                    move sheet to output
                    }
                }
    }

    routine Typewrite
    {

            "The awesomatic-typewriter springs to life, printing a giant screed
            filled with the author's views on politics, religion, and his complicated
            relationship with his mother. In fact, it still is printing!"
            Activate (infodump, 2)
    }

    replace PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        select end_type
            case 1:  print "\n*** HUGO GLORY IS YOURS! ***"
            case 2
            {
                if player_person = 2
                    print "\n*** YOU HAVE DIED ***"
                else
                    print "\n*** "; CThe(player); \
                        MatchPlural(player, "has", "have"); \
                        " died! ***"
            }
            case 3: print "\n*** SHRAPNEL IS NOT JUST AN IF GAME ***"
            case 4: print "\n*** KABOOM IS NOT JUST AN ATARI GAME ***"
        Font(BOLD_OFF)
        PrintScore(true)
    }

    routine DoStepOn
    {}

    routine DoScrape
    {
        "This is life, man, not a game!"
        return true
    }
