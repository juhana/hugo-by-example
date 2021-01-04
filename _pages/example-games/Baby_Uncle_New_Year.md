---
title: Baby Uncle New Year
permalink: /example-games/baby-uncle-new-year/
categories: 
  - Example Games
---

Baby Uncle New Year is a short game written by Roody Yogurt for the
[Even Newer New Year's Speed IF](http://ifwiki.org/index.php/Even_Newer_New_Year%27s_Speed_IF).
Being Herr Yogurt, he submitted it late.

-   This is a somewhat modified version, updated to make use of library
    contributions. Currently, it requires
    glk.h, [opportune.h](contributions/opportune.h/), and
    *boxdrawglk.h*.
-   It totally steals object-naming code from Vault of Hugo.

## The code

    !::
    ! BABY UNCLE NEW YEAR
    !    by Roody Yogurt
    !
    !:: Flags
    #set GLK
    #set DEBUG
    #set NO_MENUS            ! Don't use menus
    #set NO_SCRIPTS          ! Don't use character scripts

    ! The following limit setting reserves 512 extra bytes of dictionary space
    ! so that the play can name the unnamed object.  A maximum 512 bytes are
    ! required because the game needs to write the name, adjective, and misc
    ! properties of the object.

    $MAXDICTEXTEND = 512


    constant AFTER_PERIOD " "     ! include one space after full stops (as opposed
                                  !  to two)
    constant INDENT_SIZE 2


    !:: Includes (grammar must come first)
    ! put your new grammar here
    verb "screen"
       *              DoScreen
    verb "exits"
       *              DoExits
    verb "sigh"
       *              DoSigh
    verb "hug","kiss"
       * object          DoHug
    verb "throw"
       * object          DoThrow
    verb "recline"
       * object          DoRecline
    verb "push","pull","press"
       * object "north"/ "n"/ "south"/ "s"/ "east"/ "e"/ "west"/ "w"/ \
       "southeast"/ "se"/ "southwest"/ "sw"/ "northwest"/ "nw"/ \
       "northeast"/ "ne"/ "up"/ "u"/ "down"/ "d"/ "in"/ "out"/ \
       "inside"/ "outside"     DoPushDir
       * object "to" anything        DoPushDir
       * object          DoMove
    verb "call","dial"
       *              DoVague
       * anything           DoCall
       * "home"          DoCall
    verb "hit"
       * "alarm"            DoAlarm
    verb "read"
       * object          DoLook
    verb "wake"
       * object          DoWake
    verb "rummage","search"
       * object          DoSearch
    verb "time"
       *              DoTime
    verb "hooray"
       *              DoHooray
    verb "help","hint","hints"
       *              DoHelp
    verb "version","info"
       *              DoInfo
    verb "xyzzy"
       *              DoXyzzy
    verb "use"
       *   (payphone)          DoCall
       * (alarm)            DoSwitchOn
    verb "yes","y"
       *              DoYes
    verb "no"
       *              DoNo
    ! new grammar needs defined before the #include verblib
    #include "verblib.g"    ! Verb Library
    #include "hugolib.h"    ! standard Hugo Library
    #include "system.h"
    #include "glk.h"
    #include "boxdrawglk.h"
    #include "opportune.h"

    !:: Game Initialization routine
    routine init
    {
       window 0
            counter = -1    ! 1 step before first turn
    ! counter = 0           ! number of minutes since midnight if STATUSTYPE = 2 (time)
            STATUSTYPE = 0  ! 0 = none :: 1 = score/turns :: 2 = time
            TEXTCOLOR = DEF_FOREGROUND
            BGCOLOR = DEF_BACKGROUND
            SL_TEXTCOLOR = DEF_SL_FOREGROUND
            SL_BGCOLOR = DEF_SL_BACKGROUND

            color TEXTCOLOR, BGCOLOR

            glkcheck
            FillBox
            verbosity = 2   ! 1 = normal (rooms described only if not previously
                            !     described)
                            ! 2 = full (rooms described every time they are entered)

            display.title_caption = "Baby Uncle New Year"  ! used for GUI clients
                                                           !  for title bar text.

            prompt = ">"
            print " "
            lines_from_top = display.screenheight/5
            DEFAULT_FONT = PROP_ON
            Font(DEFAULT_FONT)
            if not glk
                cls
            Epigram(true,"_ Press a key to continue...")
       cls
       if not glk
          locate 1,3

            "_  It must be said- 2010 gone done you wrong. You lost employment, friends, love. Without so much as a silver lining,
       the year was more like
       an endless golden shower. It was a half-empty cup containing spoiled milk.
       It has been a swirling turd for which there has been no positive spin. To describe the year with a phrase that came
       out of it, 2010
       has eaten \"a hot bowl of Dicks.\"\n\n
       _  In late December, though, things changed when you became an uncle.
       That single, humble birth hatched a glorious idea- a dash of
       right time with a sprinkle of right place and voil\`a! A freshly-appointed Baby New Year nephew could be
       your meal ticket, and 2011 would be your oyster. Nepotism, bitches!!\n"

            "\BBaby Uncle New Year\b"
            "An Interactive New Year's Revolution"
       "Written for the Even Newer New Year's Speed IF by Roody Yogurt"
       print BANNER

            player = you
            location = STARTLOCATION

            move player to location
       move baby to player
            old_location = location
            FindLight(location)
            DescribePlace(location)
            location is visited
    }


    routine main
    {
            counter = counter + 1
            PrintStatusLine
            run location.each_turn
            runevents
            RunScripts
            if speaking not in location
                    speaking = 0
            if epigram_on
             Box(true,1)
    }

    player_character you "you"
    {
       long_desc {
          "You look as good as you ever do most days."
          }
       before {
          actor PreParse
             {
             local a
             a = words
             if (word[1] = "hell", "hell?")
                {
                "I know, right?"
                ParseError(100)
                return true
                }
             elseif (word[1] = "aw") and (word[2] = "yeah","yeah!")
                {
                "Right on!"
                ParseError(100)
                return true
                }
             else
             return false
             }
          }
       after {
          actor DoInventory
             {
             if self is not special
                {
                "\nDang! You just realized you left your cell phone in the charger at home. THAT ALWAYS HAPPENS."
                self is special
                }
             else
             return false
             }
          }
       capacity 1000
    }

    room STARTLOCATION "Main Lobby"
    {
       initial_desc {
       "It took some doing, but you finally found New Year's Pole, the place
       Where It All Starts (and ends). You would have given this small island off
       the coast of New Zealand a pass if it weren't for its sizeable building
       fully-equipped with television satellite. You'd bet your unshakable faith in worn-out
       stereotypes that Old Man New Year loves himself some \"Matlock.\"\n\n

       _  Anyhow, now you're in the main lobby of that building. A directory tells
       you that there is a \"Baby Room\" to the northeast, a
       \"TV Lounge\" to the northwest, and a \"Sash Ceremony Stage Area\"
       to the north. Furthermore, a large banner has been erected over the exit to the south.";
       "\n\n
       _  You are carrying a baby."
       }
       long_desc {
       "Santa and his peeps may have the North Pole; John Carpenter's The Thing may have the South Pole.
       Awesomely and nonsensically, it turns out there's a New Year's Pole, too, and
       you're in the main lobby of its headquarters. A directory tells
       you that there is a \"Baby Room\" to the northeast, a
       \"TV Lounge\" to the northwest, and a \"Sash Ceremony Stage Area\"
       to the north. Furthermore, a large banner has been erected over the exit to the south."
       }
       before   {
       location DoListen  {
          "It's mostly pretty quiet."
          }
             }
       ne_to {
          if StorkRoom is not visited
             {
             MovePlayer(StorkRoom,1)
             DescribePlace(location)
          !\ "\BBaby Room\b\n
          _  A crib is here. A little sign on it denotes the occupant as \"Future Baby New Year.\"\n\n
          _  The crib currently is empty.\n" \!
          "_ The crib is currently empty. You hear a bell chime.\n\n>the hell?\n\n
          Suddenly, a delivery man- guess that chime was from an unseen delivery door- barges
          into the room, carrying a baby (presumably the successor to the New Year throne). As he gently places
          the baby in the crib, he glances in your direction. His eyes go wide as he sees the baby in your arms.\n\n
          He straightens up and addresses you, \"Aw, geez fella. If that baby is what I think it is, you guys must have
          received a duplicate shipment. Here, take this.\" He hands you a business card. \"I can't take this
          baby back without the right paperwork. Call
          corporate and tell them about the duplicate shipment, and they'll send me to take
          this guy back, no questions asked.\"\n\n
          And with that, he departs."
          move card to player
          move baby2 to crib
          PutInScope(company,player)
          DescribePlace(location)
          StorkRoom is visited
          }
          elseif baby2 is special and baby2 in crib
             {
             MovePlayer(StorkRoom,1)
             DescribePlace(location)
             "\n_ You hear a bell chime. You know what this means, right?\n\n>aw yeah!\n\n
             The delivery man enters the room. He spots you quickly and says,\"Just got the call.
             I'm glad we could straighten this out.\"\n\n
             Without missing a beat, he scoops up the baby from the crib and leaves. Swell guy!"
             move baby2 to void
             move babies to void
             DescribePlace(location)
             }
          else
          return StorkRoom
          }
       nw_to tvlounge
       n_to {
          "An elf pokes his head out of a big door. ";
          if oldman in recliner and child(crib) = 0
          "He says, \"We're not yet ready to start the Sash Ceremony. Old Man New Year hasn't
          begun his preparations and Baby New Year is not yet in his crib!\" and disappears
          again."
          elseif oldman in recliner and child(crib) ~= 0
          "He says, \"We're not yet ready to start the Sash Ceremony. It looks like Baby New Year
          is all ready in his crib, but Old Man New Year hasn't begun his preparations!\"
          and disappears again."
          elseif oldman in void and child(crib) = 0
          "He says, \"We're not yet ready to start the Sash Ceremony. Old Man New Year is ready
          to go, but Baby New Year is not yet in his crib!\" and disappears
          again."
          elseif oldman in void and child(crib) ~= 0
          DoEnding()
          return true
          }
       s_to {
          if current_opp = mystery
             {
              "You hop on a plan and head home. As you doze off into
               both metaphorical and spiritual oblivion, you struggle
               to hear the announcement of the in-flight meal. Did she
               really say that?"
               endflag = 3
              }
          if current_opp = mammal
             NewQuestion(mystery)
          if current_opp = egress
             NewQuestion(mammal)
          if not current_opp
             NewQuestion(egress)
            }
        extra_scenery "door","shadow","corner","shadows"
    }


    question egress
    {
       long_desc
          "Are you sure you're mentally and otherwise prepared to meet up with an egress?"
    }

    question mammal
    {
       long_desc
          "Then you're fully aware of the ferociousness of this rare mammalian species, right?"
    }

    question mystery
    {
       long_desc
          "Alright, so you know all about egresses.
           But do you really want to leave the New Year's Pole in all of its mystery
           and all of its pageantry behind?"
    }

    replace PreParse
    {
       if current_opp and word[1] = "n"
          word[1] = "no"
    }


    routine DoYes
    {
       if not current_opp
          {
          "Yes?"
          return false
          }
       else
       select current_opp
          case egress: NewQuestion(mammal)
          case mammal: "Then you'd be helpless against this dangerous beast."
          case mystery {
                "You hop on a plan and head home. As you doze off into
                 both metaphorical and spiritual oblivion, you struggle
                 to hear the announcement of the in-flight meal. Did she
                 really say that?"
                 endflag = 3
              }
       return true
    }

    routine DoNo
    {
       if not current_opp
          {
          "You sound rather negative."
          return false
          }
       else
       select current_opp
          case egress: "Then you'd be helpless against this dangerous beast."
          case mammal: NewQuestion(mystery)
          case mystery: "That's the spirit."
       return true
    }

    scenery banner2 "banner"
    {
       article "the"
       noun "banner"
       long_desc {
          "\"THIS WAY TO THE EGRESS\""
          }
       in STARTLOCATION
    }
    scenery directory "directory"
    {
       article "the"
       noun "directory"
       long_desc {
          "The directory tells
       you that there is a \"Baby Room\" to the northeast, a
       \"TV Lounge\" to the northwest, and a \"Sash Ceremony Stage Area\"
       to the north."
          }
       in STARTLOCATION
    }

    object baby "nephew"
    {
       article "your"
       adjective "baby","old"
       noun "baby", "nephew" !, "william"
       long_desc { if self is not special
             {
             !self.name = "Baby William"
             self.article = 0
             "His parents were ecstatic when you volunteered to babysit him. Of course, you didn't really explain
          you'd be taking him out of the country. Beggy parents can't be choosy parents.
          Anyhow, you've already forgotten his original name. You like to call him ";
             GetInput("\"NAME\">")
             DoName()
             self is special
             }
             else
             {
             print "Your nephew, "; self.name; ", looks up at you lovingly. Well, with as much love as a baby
          can muster. Like anything, babies aren't really good at adoration yet."
             }
          }
       misc 0
       size 200
       before {
          object DoEat
             {
             "You want your baby back, baby back, baby back, etc... In all seriousness, though, no."
             }
          object DoDrop
             {
             "You can't just drop ";
             if self is special
             print self.name;
             else
             print "a baby";
             " anywhere. You're not a monster!"
             }
          object DoHello
             {
             "Why hello right back at you, Big Man!"
             }
          object DoTalk
             {
             "You make obnoxiously cute babytalk noises. He coos his enjoyment in reply."
             }
          object DoGet
             {
             if self in crib
             "He should remain in the crib until after the sash ceremony."
             else
             return false
             }
          }
       after {
          xobject DoAskQuestion
          {
          "Try again later. Much later."
          }
          object DoAsk
          {
          "Try again later. Much later."
          }
          }
          order_response {
          "Try again later. Much later."
             }
       is living
    }

    room storkroom "Baby Room"
    {
       long_desc
          {
          "This room seems to be where Baby New Year hangs out before the big ceremony. An exit
          to the southwest leads to the Main Lobby.\n"
          }
       sw_to {
             if payphone not in STARTLOCATION
                {
                move payphone to STARTLOCATION
                return STARTLOCATION
                }
             else
                return STARTLOCATION
             }

    }

    object crib "crib"
    {
       noun "crib"
       article "the"
       short_desc {
                   "A crib is here. A little sign on it denotes the occupant as
                   \"Future Baby New Year.\"\n"
                   if child(self) = 0 and baby2 in void
                      "_ The crib is currently empty. ";
                   }
       list_contents
                {
                if child(self)= 0
                   "_ The crib is currently empty."
                else
                   return false
                }
       before
                {
                xobject DoPutIn
                   {
                   if object ~= baby
                      {
                      "Only babies go in the crib!"
                      return true
                      }
                   elseif baby2 in crib
                      {
                      "The crib is already occupied."
                      return true
                      }
                   elseif baby is special
                      {
                      "You do your best choir-of-angels sound as you slowly lower ";
                      print baby.name; " down into the crib. He smiles back up at
                      you (although it's probably just gas). Everything is coming
                      up \BUncle\b! Hooray!"
                      move baby to crib
                      return true
                      }
                   else
                      {
                      "You do your best choir-of-angels sound as you slowly lower
                      your nephew down into the crib. He smiles back up at you
                      (although it's probably just gas). Everything is coming up
                      \BUncle\b! Hooray!"
                      move baby to crib
                      return true
                      }
                   }
             object DoEnter
                {
                "You are too big for the crib!"
                }
             }
       is static, container, open
       in storkroom
       holding 0
       capacity 300
    }

    property times alias misc

    object baby2 "new baby"
    {
       noun "baby","year"
       article "the"
       adjective "new"
       long_desc {
          "Just ";
          NumberWord(self.times)
          if self.times = 1
           print " look ";: else: print " looks ";
           "tells you that this baby would give you a lousy year.
          He has to go."
          self.times++
          }
       times 1
       before {
          object DoTalk,DoHello,DoAsk,DoTell
             {
             "\"Why do you and your brothers hate me?\" you ask the baby, sobbingly."
             return true
             }
          object DoHit
             {
             "No, you don't hit babies. Plus, if your plan fails, in three months, this guy
             might be bigger than you."
             return true
             }
          object DoLook
             {
             return false
             }
          object
          {
             "As a bachelor, you feel it is your privilege to not have to deal with anybody's
             baby that you aren't related to. Even under the circumstances, you're not
             going to touch this baby while other options remain available."
             return true
          }
          }
       is living, static
          order_response {
          "Try again later. Much later."
             }
       parse_rank 2
    }

    scenery babies "babies"
    {
       article "the"
       noun "babies"
       before
          {
          object
             {
             "Please refer to the babies specifically."
             }
          xobject
             {
             "Please refer to the babies specifically."
             }
          }
        nearby crib
       is hidden
    }

    scenery lilsign "little sign"
    {
       part_of crib
       article "the"
       adjective "little"
       noun "sign"
       long_desc {
          "It reads, \"Future Baby New Year.\""
          }
    }

    object card "business card"
    {
       article "a"
       adjective "business"
       noun "card"
       long_desc {
          "Printed on the card is the baby delivery service's phone number. The hell?
          It's not even a toll free number! Still, luckily, it looks like a local number."
          }
       size 1
    }

    object company "phone number"
    {
       article "the"
       noun "number","company","service"
       adjective "delivery", "phone"
       before {
          object DoCall
             {
             return false
             }
          object DoLook
             {
             "It's right there on the card. To use it, try >CALL NUMBER or >CALL COMPANY."
             }
          object {
             "I don't see the point of that, really."
             }
          }
       in_scope 0
       is hidden
    }

    scenery delivery "unseen delivery door"
    {
       adjective "unseen","delivery"
       noun "door"
       article "the"
       before
          {
          object
          {
          ! The first rule of Unseen Delivery Door Club is you can't see Unseen Delivery Door Club.
          "The first rule of Unseen Delivery Door Club is \"Don't refer to Unseen Delivery Door Club!\""
          }
          }
       in storkroom
    }

    room tvlounge "TV Lounge"
    {
       long_desc {
          "Well, well, well. Even fancy pants Old Man New Year likes a good man cave.
          Nothing too ostentatious, really, but it has a nice tv and seems generally
          comfy.
          Over on the side of the room is a shelf on which you can see an alarm clock
          and some kind of daily planner. Heading southeast takes you back to the Main
          Lobby. To the north is some kind of living quarters.\n"
          }
       se_to {
          if alarm is special
             {
             "Leaving now might draw undue attention to yourself."
             return true
             }
          return StartLocation
          }
       n_to {
          "Nah, you are not interested in exploring Old Man New Year's living quarters."
          }
       extra_scenery "controls","base","shelf","beard","sash","crocosharks"
    }

    object planner "daily planner"
    {
       noun "planner", "schedule"
       adjective "daily"
       article "the"
       long_desc {
          "Glancing at the planner, you see that Old Man New Year wrote down
          his schedule for the entire day. It doesn't look like his alarm is supposed
          to go off for a fair amount of time yet."
          }
       before  {
          object DoLook
             {
             return false
             }
          object  {
             "Better just let it be."
             return true
             }
          }
       in tvlounge
       is hidden, openable
    }
    object recliner "recliner"
    {
       article "the"
       adjective "seat"
       noun "recliner","chair","cushion","cushions"
       short_desc {
          "A comfortable distance away from the tv is a recliner. ";
          }
       long_desc {
          "This chair looks very comfortable. You can only guess that Old Man New Year
          spends a lot of time on it. ";
          if oldman in recliner
             {
             "He is currently doing just that, sleeping blissfully unaware of the world
             around him. ";
             }
          "For whatever reason, a big chunk of the base is missing. ";
          if wood in tvlounge
             {
             "Luckily, there is a block of wood propped under the chair keeping it level."
             }
          }
       in tvlounge
       is static, platform, enterable
       list_contents {
             if oldman in self
             "Sleeping peacefully on the recliner is Old Man New Year."
             else
             return false
             }
       before
          {
          object DoEnter
             {
             if oldman in recliner
                "The recliner is already occupied."
             elseif oldman in tvlounge
                "Old Man New Year might sit back down any second!"
             else
                "You have no inclination for reclination at the moment."
             }
          object DoMove
             {
             if wood in tvlounge
             "You give it a nice shove, but the block of wood underneath the recliner
             keeps the chair pretty stable. It
             barely moves at all."
             else
             "The recliner wobbles greatly."
             return true
             }
          object DoSearch
             {
             if oldman in recliner
                {
                "You find an Old Man New Year in the recliner. Just kidding- you can't
                properly search it with him sitting in it."
                return true
                }
             elseif oldman in tvlounge
                {
                "Old Man New Year could sit down at any moment. You don't have enough time
                to give it a good rummaging."
                return true
                }
             elseif self is special
                {
                "You find nothing else in the seat cushions."
                return true
                }
             else
                {
                "Digging among the seat cushions, you come across some change. You're RICH!"
                move change to player
                self is special
                }
             }
          }
    }

    character oldman "Old Man New Year"
    {
       noun "man","year","guy"
       adjective "old","man","new"
       long_desc {
          "You know the deal. He's an old guy with a long beard wearing a sash."
          }
       in recliner
       before
          {
          object DoHit
             {
             "That's not a good idea."
             return true
             }
          object DoLook,DoWake
             {
             return false
             }
          object
             {
             if oldman in recliner
                {
                "Old Man New Year is completely oblivious."
                return true
                }
             if oldman in tvlounge
                {
                "Don't bother him. He's sleepwalking!"
                return true
                }
             }
          xobject
             {
             if oldman in recliner
                {
                "Old Man New Year is completely oblivious."
                return true
                }
             if oldman in tvlounge
                {
                "Don't bother him. He's sleepwalking!"
                return true
                }
             }
          }
       order_response {

             if oldman in recliner
                {
                "Old Man New Year is completely oblivious."
                return true
                }
             if oldman in tvlounge
                {
                "Don't bother him. He's sleepwalking!"
                return true
                }

             }
    }

    object wood "piece of wood"
    {
       article "the"
       adjective "piece","of","block"
       noun "piece","wood","block","chunk"
       in tvlounge
       long_desc {
          "There is a chunk of wood of wood propped under the recliner, keeping it stable."
          }
       before {
          object DoGet,DoThrow,DoMove
             { if oldman in recliner and wood in tvlounge
                {
                "You can't pull the wood free while the old guy is sitting there."
                return true
                }
              else
              "With nobody sitting on the chair, you easily pull the wood out from under it
              and chuck it behind you, never to be seen again!"
              move wood to void
             }
          }
       is hidden
    }

    scenery tv "television"
    {
       article "the"
       noun "tv", "television"
       long_desc {
       "You are in too much of a hurry to pay much attention to the show Old Man New Year
       was watching but you think you see crocosharks." }
       react_before {
          if verbroutine = &DoLook and object = tv
             return false
          elseif object = tv or xobject = tv
             {
             "Never mind the tv."
             return true
             }
          elseif verbroutine = &DoListen
             {
             if alarm is special
             "All sound is dwarfed by the blare of the alarm clock."
             else
             "It's mostly quiet except for some soft blather from the television."
             }
             else
             return false
          }
       before {
          object DoSwitchOff
             {
             "You're not here to fiddle with televisions."
             }
          object DoSwitchOn
             {
             "The tv is already on."
             }
          }
       is switchable
       in tvlounge
    }

    object alarm "alarm clock"
    {
       article "the"
       adjective "alarm"
       noun "clock"
       long_desc {
       "The alarm clock has all of the bells and whistles. Actually, you think it might be part foghorn, too.
       It looks really loud. In any case, the only controls that catch your eye are an alarm button and a snooze button."
          }
       in tvlounge
       is static, hidden, switchable
       parse_rank 2
       before
          {
          object DoMove,DoHit,DoSwitchOn
             {
             Perform(&DoAlarm)
             }
          object DoSwitchOff
             {
             Perform(&DoMove,snooze)
             }
          }
    }
    scenery buttons "buttons"
    {
       article "the"
       noun "buttons"
       is plural
       long_desc {
          "There is an alarm button and a snooze button."
          }
       before
          {
          object DoLook,DoGet
             {
             return false
             }
          object
             {
             "You'll have to specify which button you want to interact with."
             }
          }
       in tvlounge
    }

    component alarmbutton "alarm button"
    {
       article "the"
       adjective "alarm"
       noun "button"
       part_of alarm
       before
          {
          object DoMove,DoHit
             {
             DoAlarm
             return true
             }
          }
    }

    component snooze "snooze button"
    {
       article "the"
       adjective "snooze"
       noun "snooze", "button"
       part_of alarm
       before
          {
          object DoMove,DoHit
             {
             if alarm is not special
                {
                "The alarm is not ringing. Hitting snooze would have no effect."
                return true
                }
             elseif wood in tvlounge
                {
                "You hit the snooze button and the alarm stops ringing. Old Man New Year slowly
                realizes the offending noise is gone and turns back, plopping
                back into the recliner and promptly falling back asleep."
                alarm is not special
                Deactivate(alarmclock)
                move oldman to recliner
                }
             else
                {
                "You hit the snooze button and the alarm stops ringing. Old Man New Year slowly
                realizes the offending noise is gone and turns back, plopping back into the recliner.
                With the piece of wood gone, though, it tilts backwards, throwing Old Man New Year
                to the floor. The shock of it all sends him fully awake. He gives up on the
                possibility of a last minute catnap and goes to the north to prepare for the
                ceremony."
                move oldman to void
                alarm is not special
                Deactivate(alarmclock)
                }
             }
          }
    }


    object payphone "payphone"
    {
    article "the"
    adjective "pay"
    noun "phone","payphone"
    initial_desc {
       "\n_  AHEM- It is at this point that the author of the game would like to apologize for neglecting to mention
       that there's a payphone in the corner of the room. So yeah, payphone in the corner! Wow!"
       self is moved
       }
    long_desc {
       "The sight of this baby brings you a huge sigh of relief. You are much better prepared for a
       find-change-for-payphone puzzle ";
       if change not in player : "(despite not having any change) ";
       "than a find-a-payphone puzzle, which we all know is nearly impossible
       in this day and age."
       }
    short_desc
       {
       "\nA lonely payphone hangs in a shadowy corner."
       }
       is static,container, open
       list_contents
       {
          ! Skip contents-listing if not looking specifically inside
          if verbroutine ~= &DoLookIn
          {
               "You can't see inside the payphone, dumbass."
          }
          else
          {
                return 0
          }
       }
       holding 0
       capacity 20
       before
       {
       xobject DoPutIn
          {
          if object ~= change
             {
             "That doesn't go in there."
             return true
             }
          "Clink! The coins go in the payphone. Looks like you're ready for a phone call!"
          move change to void
          }
       xobject DoGet
          {
          "How are you going to manage that?"
          return true
          }
       }

    }

    object phonecall "people to call"
    {
    noun "home","mum","mother","family"
    is known
    }

    component slot "coin slot"
    {
       article "the"
       adjective "coin"
       noun "slot"
       part_of payphone
       before
          {
          xobject DoPutIn
             {
             if object = change
             Perform(&DoPutIn,change,payphone)
             else
             "That doesn't go in there."
             }
          }
       is container
    }


    object change "change"
    {
    article "some"
    noun "change","coins"
    long_desc {
       "Just enough for a phone call!"
       }
       before
          {
          object DoCount
             {
             "Just enough for a phone call!"
             }
          }
       size 5
    }


    routine DoScreen
    {
    print "The screen width is "; number display.screenwidth; " characters."
    print "The screen height is ";  number display.screenheight; " characters."
    print "The line length is "; number display.linelength; " characters."
    print "The window lines height is "; number display.windowlines; " characters."
    print "The status line height is "; number display.statusline_height; " characters."
    print "This interpreter ";
       if display.hasgraphics
       "supports graphics."
       else
       "does not support graphics."
    print "According to glk.h ";
       if glk
       "this is a glk port."
       else
       "this is not a glk port."
    }

    ! this next routine has some weird support-for-simple-DOS code in it
    !  but in the end, I ended up cutting out the score / turn counter
    !  anyways

    replace PrintStatusline
    {
    !  if display.linelength < 80
    !     display.statusline_height = 2
    !  else
          display.statusline_height = 1

       Font(BOLD_OFF | ITALIC_OFF | UNDERLINE_OFF | PROP_OFF)
       window display.statusline_height
       {
       local a
       a = display.linelength
       if not display.hasgraphics and display.screenheight > display.windowlines and glk
       {
       a = a - 3
       }
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
    !        print to 65;
    ! Ok, let's begin writing to array "status"
                            {
                            text to _temp_string
             print number score; " / "; number counter;
             text to 0
    ! Ok, we've closed off the string array writing
    ! Now, let's move to the end of the screen MINUS the length of "score / counter" plus two extra spaces
    ! for good measure
             print to (a - (StringLength(_temp_string) + 2));
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



    routine DoSigh
    {
    "Ah, relief!"
    return true
    }

    routine DoHug
    {
    print "Yay! "; capital object.article; " "; object.name ; " feels better!"
    if object = oldman
    " He remains asleep however."
    return true
    }

    routine DoThrow
    {
       if object = baby
          {
          "You miss. Just kidding, this baby is too young to throw yet!"
          return true
          }
       else
       "Naw, no throwing."
       return true
    }

    routine DoRecline
    {
       if object = recliner
          {
          "The reclination mechanism seems to be malfunctioning! Abort! Abort!"
          return true
          }
       else
          "That doesn't recline."
          return true
    }

    ! Notice that the DoName routine only allows the player to create one new
    ! entry in order to avoid overrunning MAXDICTEXTEND.

    array name_array[50]
    array name2_array[50]

    routine DoName()
    {
       if baby is special
          {"You already named the baby."}
       else
       {
          local i, len

          len = string(name_array, parse$, 49)    ! maximum 49 char.
          for (i=0; i<len; i=i+1)
          {
             ! Because the parser cannot recognize multiple
             ! words...
             if name_array[i] = ' '          ! a space
                {"Better keep it to one word."
                return}

             ! ...or non-alphanumeric characters (a table of
             ! ASCII values will show why these are the
             ! boundaries)

             if name_array[i] < '0' or name_array[i] > 'z' or
               (name_array[i] > '9' and name_array[i] < 'A') or
               (name_array[i] > 'Z' and name_array[i] < 'a'):
                {"Better to keep the fancy punctuation
                out of it."
                return}
          }

          !"You write \"";
          !StringPrint(name_array)
          !"\" on the object."

          ! The misc property contains the non-case-corrected version
          ! of the name.

          baby.misc = dict(name_array, 49)

          ! The name is converted to '"<string>" object':

          ! initial quote first...
          !name_array[0] = '\"'

          ! then read parse$ into name_array (after the first quote)...
          !len = string(name_array+1, parse$, 49)
    !     len = string(name_array, parse$, 49)
          ! and append the last part to name_array...
          !   string(name_array+len+1, "\" object")

          ! ...before turning name_array into a dictionary entry
          !baby.name = dict(name_array, 49)

          ! Since the adjective will be referred to by the parser,
          ! it must be lowercase--name_array must also be reloaded
          ! with parse$ since it has been modified above.

          len = string(name_array, parse$, 49)
          for (i=0; i<len; i=i+1) ! the actual case-conversion loop
          {
             if name_array[i] >= 'A' and name_array[i] <= 'Z'
                name_array[i] = name_array[i] + ('a'-'A')
          }

          ! then write the word as a dictionary entry
          baby.noun #1 = dict(name_array, 49)

          ! object.article = "the"  ! i.e. 'the "<string>" object'

          baby is special
          baby is moved
          text to name2_array
          if StringDictCompare(name_array, "baby") = 0
           { "Baby"; }
           else
           { "Baby ";
           print capital StringPrint(name_array);
           }
           text to 0
           baby.name = dict(name2_array, 49)
          print "Yeah, "; baby.name;
          "! That's the ticket!"
       }
    }


    replace PrintEndGame(end_type)
    {
       Font(BOLD_ON)
       select end_type
          case 1:  print "\n*** YOU'VE WON THE GAME! ***"
          case 2
          {
             if player_person = 2
                print "\n*** YOU HAVE DIED ***"
             else
                print "\n*** "; CThe(player); \
                   MatchPlural(player, "has", "have"); \
                   " died! ***"
          }
          case 3: print "\n*** YOUR FUTURE IS A HOT BOWL OF DICKS ***"
          case 4: print "\n*** YOU ARE THE UNCLE OF THE YEAR ***"
       Font(BOLD_OFF)
       PrintScore(true)
    }

    routine DoCall
    {
    if location ~= StartLocation and payphone not in StartLocation
       {
       "There is no phone here. Sorry."
       return true
       }
    if object = oldman
       {
       "He's somewhere around here, isn't he?"
       return true
       }
    if object = baby2
       {
       "Very funny. Ha ha."
       return true
       }
    if baby2 is special
       {
       "You already called to have the baby picked up."
       return true
       }
    elseif (object = company or object = payphone) and change in void
       {
       "You dial the number of the delivery service. It rings a couple times before being answered
       by a super friendly agent who informs you they will send out a driver to pick
       up your extra baby ASAP. You thank him for the help and tell him you will recommend the company
       to all of your friends for all of their baby delivery needs. You even stay on the line to verbally
       take a quick survey about the excellent service.\n\n
       Satisfied, you hang up."
       baby2 is special
       return true
       }
    elseif (object = company or object = payphone) and change in player
       {
       "You throw the coins in the coin slot and quickly dial the number
       of the delivery service. It rings a couple times before being answered
       by a super friendly agent who informs you they will send out a driver to pick
       up your extra baby ASAP. You thank him for the help and tell him you will recommend the company
       to all of your friends for all of their baby delivery needs. You even stay on the line to verbally
       take a quick survey about the excellent service.\n\n
       Satisfied, you hang up."
       baby2 is special
       return true
       }
    elseif change not in void and change not in player
       {
       "You need to find some change first."
       return true
       }
    else
       "You don't want to waste your phone call on that."
       return true
    }

    routine DoAlarm
    {
       if player not in tvlounge
       {
       "There is no alarm to hit here."
       return true
       }
       elseif not Contains(tvlounge,oldman)
       {
       "Nah, you already got Old Man New Year to go get ready for the ceremony, and you like peace
       and quiet as much as the next guy."
       return true
       }
       elseif alarm is special
       {
       "The alarm is already ringing!"
       return true
       }
       else
       {
       "With a shout of \"Wake up, bitches!\", you hit the alarm button on the alarm clock!
       Old Man New Year jumps to his feet (albeit groggily) and starts slowly shuffling in the direction of the alarm clock."
       alarm is special
       move oldman to tvlounge
       oldman is not special
       Activate(alarmclock,3)
       return true
       }
    }

    fuse alarmclock
    {}

    room void "void"
    {}

    event in alarmclock
    {
       event_flag = 2
       if oldman is not special
       {
       oldman is special
       return true
       }
       elseif verbroutine = &DoLookAround
       "\n_ Old Man New Year slowly stumbles towards the alarm clock, eyes practically closed."
       else
       "\nOld Man New Year slowly stumbles towards the alarm clock, eyes practically closed."
       if not self.tick
       {
       if wood in tvlounge
          {
          if verbroutine = &DoLookAround
          "\n_ Old Man New Year finally gets to the alarm clock. His eyes open just enough to see that he
          still has yet some time before the sash ceremony, so he hits the snooze button
          and hops back onto the recliner and promptly falls back asleep."
          else
          "\nOld Man New Year finally gets to the alarm clock. His eyes open just enough to see that he
          still has yet some time before the sash ceremony, so he hits the snooze button
          and hops back onto the recliner and promptly falls back asleep."
          alarm is not special
          Deactivate(alarmclock)
          move oldman to recliner
          }
       else
          {
          if verbroutine = &DoLookAround
          "\n_ Old Man New Year gets to the alarm clock. His eyes open just enough to see that he
          still has yet some time before the sash ceremony, so he hits the snooze button
          and hops back onto the recliner.
          With the piece of wood gone, though, it tilts backwards, throwing Old Man New Year
          to the floor. The shock of it all sends him fully awake. He gives up on the
          possibility of a last minute catnap and goes to the north to prepare for the
          ceremony."
          else
          "\nOld Man New Year gets to the alarm clock. His eyes open just enough to see that he
          still has yet some time before the sash ceremony, so he hits the snooze button
          and hops back onto the recliner.
          With the piece of wood gone, though, it tilts backwards, throwing Old Man New Year
          to the floor. The shock of it all sends him fully awake. He gives up on the
          possibility of a last minute catnap and goes to the north to prepare for the
          ceremony."
          move oldman to void
          alarm is not special
          Deactivate(alarmclock)
          }
       }
    }

    routine DoWake
    {
       if object ~= oldman
          {
          "That doesn't need waking."
          return true
          }
       elseif oldman in recliner
          "Try as you might, the old guy just won't wake. He must be really tired."
       elseif alarm is special
          "He may be up and walking, but his eyes are barely open. You're not certain
          he's really awake, and it is dangerous to wake a sleepwalker."
          return true
    }

    routine DoSearch
    {
       "There is nothing to be found there."
    }

    routine DoCount
    {
       "Don't waste your time."
    }

    routine DoEnding()
    {
    if baby2 in crib
       {
       "The elf excitedly ushers you into a large room. Up on the stage is both Old Man New
       Year and that jerk baby the delivery guy dropped off. You watch sadly as Old Man New Year
       hands his sash off to the baby. The baby shimmers magically, and 2011 officially begins.\n\n
       On the long flight home, it's hard to know who cries more, you or your nephew. It only gets
       worse, though, when you hear the announcement of the in-flight meal."
       endflag = 3
       }
    if baby in crib
       {
       if baby is special
          {
          "The elf excitedly ushers you into a large room. Up on the stage is both Old Man New
          Year and ";
          print baby.name; ". You watch with great pride as Old Man New Year hands his sash over
          to the little guy. ";
          print baby.name; " shimmers magically. The new year has just begun,
          but you already know it's going to be a good one!"
          endflag = 4
          }
       else
             "The elf excitedly ushers you into a large room. Up on the stage is both Old Man New
          Year and your nephew. You watch with great pride as Old Man New Year hands his sash over
          to the little guy. Your nephew shimmers magically. The new year has just begun,
          but you already know it's going to be a good one!"
          endflag = 4
       }
    }

    routine DoTime
    {
       "You don't have a watch on you, but it's New Year's Eve."
    }

    routine DoHooray
    {
       "Yes. Hooray!"
    }

    routine DoHelp
    {
       "There is no help. Wah!"
    }

    routine DoInfo
    {
            "\BBaby Uncle New Year\b"
            "An Interactive New Year's Revolution"
       "Written for the Even Newer New Year's Speed IF by Roody Yogurt"
       print BANNER
    }

    routine DoXyzzy
    {
       "Save the baby talk for, um, another game."
    }

    routine DoExits
    {
       "Just re-read the room description already."
    }


    routine DoPushDir
    {

       Perform(&DoMove,object)
       return true
    }

    routine FillBox
    {
      if glk
      {
                     box_array[0] = "When everybody else refrained"
            box_array[1] =        "My Uncle Johnny did cocaine"
            box_array[2] =        "        - The Killers"
      }
      else
       {
                   box_array[0] = "When everybody else refrained"
            box_array[1] =        "My Uncle Johnny did cocaine"
            box_array[2] =        "  "
            box_array[3] =        "                - The Killers"
       }
    }
