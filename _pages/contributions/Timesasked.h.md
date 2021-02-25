---
title: Timesasked.h
permalink: /contributions/timesasked.h/
categories: 
  - Library Contributions
---

`Timesasked.h` provides a system for keeping track of times that a
character has been asked or told about various objects/topics. It also
has some support for notifying the player of currently-available topics.
Get it [here](https://github.com/hugoif/library-contributions/tree/main/timesasked).


## The code

It is probably best explained by reading the commentary:

    !::
    ! TIMESASKED Version 1.4 by Roody Yogurt
    !::

    !\
    This library contribution tries to make keeping track of how many times you ask
    or tell about an object easy, for use with games with elaborate ASK/TELL system.
    It also supports listing currently-available topics.
    \!

    !\
    Besides including this in your game, you'll need to to declare two constants
    BEFORE this is included. The two constants are:

    constant TOTALCHARACTERS # ! should hold total number of characters in the game
    constant MAXTOPICS # ! total number of topics any character can be asked about

    Next, any object that will have multiple responses (so we need to keep track
    of times asked/told) should "inherit"  the topics class. Example:

    player_character you "you"
    {
       inherits topics ! we can ask characters about ourselves
    }

    Now, every character should inherit the "chartopics" class. Example:

    character randomshmoe "Random Schmoe"
    {
       inherits chartopics
    }

    Now, witihn a character's normal DoAsk/DoTell xobject code, you can get the
    current number of times asked/told by calling Asked and Told respectively.
    Add some code to increase the counter. Take a look at the included example
    for assistance.

    If you want to make use of the DoAskTellTopics routine which allows players to
    see what objects can be currently asked and told about, add the following to
    your verb grammar:
    xverb			"topics"
    *										DoAskTellTopics

    If you want the topic listing to *work properly*, you'll want to make your own
    CharRules routine. Filling it out with your characters and objects, you can
    define rules under which circumstances objects are available. You can even set
    it so one topic won't show up unless another object has been asked/told about
    by checking Asked(<other object>) or Told(<other object>)

    \!

    #ifclear _TIMESASKED_H
    #set _TIMESASKED_H

    #ifset VERSIONS
    #message "timesasked.h Version 1.4"
    #endif

    #if undefined TOTALCHARACTERS
    constant TOTALCHARACTERS 10
    #endif

    #if undefined MAXTOPICS
    constant MAXTOPICS 10
    #endif

    array asktopicsleft[MAXTOPICS]
    array telltopicsleft[MAXTOPICS]

    ! some properties to hold these values
    property timesasked
    property timestold

    attribute is_topic

    ! each NPC should get his or her own charnumber, starting at 1, ending at
    ! the TOTALCHARACTERS value
    property charnumber

    class topics
    {
       timesasked #TOTALCHARACTERS
       timestold #TOTALCHARACTERS
       is is_topic
    }

    class chartopics
    {
       charnumber 0
       inherits topics
    }

    ! just a class object for use with non-physical
    ! conversation topics and such
    class topic_object
    {
       found_in
          return location
       before
       {
          object
          {
             "Don't be silly."
          }
          xobject
          {
             if verbroutine = &DoAsk,&DoAskQuestion,&DoTell,&DoTalk
                return false
             "Don't be silly."
          }
       }
       is known
    }

    object timesaskedlib "timesasked"
    {
    #ifset _ROODYLIB_H
       type settings
       in init_instructions
       did_print 0
       execute
       {
          if not CheckWordSetting("restore") and not CheckWordSetting("undo")
             SetCharNumbers
       }
    #endif  ! _ROODYLIB_H
    }

    routine SetCharNumbers
    {
       local i = 1
       local n
       while i <= objects
       {
          if i.#charnumber and i ~= chartopics
          {
             i.charnumber = ++n
          }
          i++
       }
    }

    !\ ChangeValueAsked - utility routine for manually changing the
    'timeasasked' property for a specific character (not actually called
    by anything \!
    routine ChangeValueAsked(obj,char,value)
    {
       obj.timesasked #(char) = obj.timesasked #(char) + value
    }

    routine Asked(obj)  ! only meant to be called by character's DoAsk code
    {                   ! returns the 'times asked' number of the current object
                        ! being asked about
       if not obj
          obj = xobject
       return obj.timesasked #(speaking.charnumber)
    }

    routine Told(obj) ! only mean to be called by character's DoTell code
    {                 ! returns the 'times told' number of the current object
                      ! being asked about
       if not obj
          obj = xobject
       return obj.timestold #(speaking.charnumber)
    }


    ! ArrayCheck checks an object's property elements
    ! and returns true when it finds a value

    routine ArrayCheck(arr)
    {
       if array arr[0]
          return true
       else
          return false
    }

    !\ TopicsList is a modified version of PropertyList. "you" as a topic gets
    changed to "yourself" and the speaker is listed as "himself" or "herself" \!

    routine TopicsList(arr, artic)
    {
       local a, b, n, total

       for (a=0; a< MAXTOPICS; a++)
       {
          if array arr[a]:  total++
       }

       for (a=0; a< MAXTOPICS; a++)
       {
          b = array arr[a]
          if b
          {
             if artic
                The(b)
             else
             {
                if b = speaking or b = player
                   print b.pronoun #4;
                else
                   Art(b)
             }

             if (a+1) < total and total > 2
                print ", ";
             elseif (a+1) = total-1:  print " ";

             if a+1 = total - 1
                print AND_WORD; " ";
             n++
          }
       }
       return n
    }


    routine DoAskTellTopics
    {
       if not speaking
       {
          TimesAskedVMessage(&DoAskTellTopics,1) !	"You are not talking to anyone
                                                 !   at the moment."
          return false
       }

       local i,j

    ! time to clear the character's asktopicsleft and telltopicsleft properties
    !   so we can refill them

       for (i=0; i<MAXTOPICS; i++)
       {
          asktopicsleft[i] = 0
          telltopicsleft[i] = 0
       }

       verbroutine = &DoAsk
       for (i=29; i<=objects; i++)
       {
          if i is is_topic and CharRules(i)
             asktopicsleft[j++] = i
       }

       j = 0

       verbroutine = &DoTell
       for (i=29; i<=objects; i++)
       {
          if i is is_topic and CharRules(i)
             telltopicsleft[j++] = i
       }

       local m,n
       TimesAskedVMessage(&DoAskTellTopics,5) ! "("
       if ArrayCheck(asktopicsleft)
       {
          TimesAskedVMessage(&DoAskTellTopics,2) ! "You can ask <char> about..."
          m = 1
       }
       if ArrayCheck(telltopicsleft)
       {
          if m
             print " ";
          TimesAskedVMessage(&DoAskTellTopics, 3 , m) ! "You can tell <char>
                                                      ! about..."
          n = 1
       }
       if not n and not m
          TimesAskedVMessage(&DoAskTellTopics,4) ! "You have nothing to talk about
                                                 !  at this time."
       TimesAskedVMessage(&DoAskTellTopics,5,1)  ! ")"
    }

    routine TimesAskedVMessage(r, num, a, b)
    {
       if NewTimesAskedVMessages(r, num, a, b):  return

       select r
          case &DoAskTellTopics
          {
             select num
                case 1: "You are not talking to anyone at the moment."
                case 2
                {
                   print "You can ask "; speaking.name ; " about ";
                   TopicsList(asktopicsleft)
                   print ".";
                }
                case 3
                {
                   print "You can tell ";
                   if a
                      print speaking.pronoun #2 ;
                   else
                      print speaking.name ;
                   print " about ";
                   TopicsList(telltopicsleft)
                   print ".";
                }
                case 4
                {
                   print "You have nothing to talk about at this time.";
                }
                case 5
                {
                   if not a
                      print "(";
                   else
                      print ")"
                }
          }
    }

    !\ The NewTimesAskedVMessages routine may be REPLACED and should return
    true if a replacement message exists for routine <r> \!

    routine NewTimesAskedVMessages(r, num, a, b)
    {
       return false
    }

    routine CharRules(obj)
    {
       return true
    }

    #endif


## Some examples

    ! Example of a character
    character fred "Fred"
    {
       noun "fred"
       in STARTLOCATION
       inherits chartopics ! inherits all relevant properties
       after
       {
          object DoAsk
          {
             local notcount ! let's create a variable that if true, the 'timesasked'
                            ! counter does NOT increase
             select xobject
                case you
                {
                   if not Asked
                      "You seem swell."
                   else
                      "I said you seem swell."
                }
                case STARTLOCATION
                {
                   select Asked
                   case 0 : "I like swell places."
                   case 1: "This place seems swell."
                   case 2: "Sure, this place seems really swell."
                   case else: "I'm done talking about how swell this
                   place is."
                }
                case fred: "I'm just this guy."
                case else: "I dunno!"
             if not notcount
                xobject.timesasked #(self.charnumber) =  Asked + 1
          }

          object DoTell
          {
             select xobject
             case you
             {
                if not Told
                   "You seem swell."
                else
                   "I said you seem swell."
             }
             case STARTLOCATION
             {
                select Told
                case 0 : "I like swell places."
                case 1: "This place seems swell."
                case 2: "Sure, this place seems really swell."
                case else: "I'm done talking about how swell this
                place is."
             }
             case self: "I'm just this guy."
             case else: "I dunno!"
             xobject.timestold #(self.charnumber) =  Told + 1
          }
       }
    }

    ! Example of an object
    object tincan "tin can"
    {
       article "the"
       adjective "tin"
       noun "can"
       inherits topics
    }

    ! CharRules example
    replace CharRules(obj)  ! called by DoAskTellTopics
    {
       local a, b
       if verbroutine = &DoAsk
          b = Asked(obj)
       else
          b = Told(obj)
       select speaking
          case fred
          {
             select verbroutine
                case &DoAsk
                {
                   select obj
                      case you: a = b < 1
                      ! "you" will show up as a topic if it hasn't been
                      ! asked about
                      case STARTLOCATION: a = b < 3
                      ! the start room will show up as a topic if it has
                      ! been asked about less than three times
                      case fred: a = 1
                      ! fred will always show up as a topic
                      case else : a = 0
                      ! nothing else will show up as a topic
                }
                case &DoTell
                {
                   select obj
                      case you: a = b < 1
                      case STARTLOCATION: a = b < 3
                      case fred: a = 1
                      case else : a = 0
                }
          }
       return a
    }
