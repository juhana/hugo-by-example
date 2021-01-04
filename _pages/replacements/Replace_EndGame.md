---
title: Replace EndGame
permalink: /replacements/endgame/
categories: 
  - Replacements
---

[EndGame](routines/endgame/) both calls the "Would you like to
\[R\]estart..." message and interprets whatever the player enters,
directing it towards the right command. As important as this is to any
game, the original routine isn't optimized for configurability (for
those cases where an author might want to offer an "\[A\]musing" choice
or change the menu choices altogether for whatever reason). This version
attempts to do that.

`EndGame` also has a bug where, if someone opens up the "\[R\]estore"
dialog but cancels out of it (or `restore` fails in some other way),
instead of staying in the "end game" loop, the game quits out. This'll
fix that, too.

### What it fixes

1.  Adds an "end_type" parameter to
    [Message(&EndGame)](basics/messages/) calls, so that the messages
    can be adapted to the current ending (end_type is set to the
    [endflag](globals/endflag/) value that initiated the endgame
    routines).
2.  Moves the key-response code into another
    [replaceable](guts/replace/) routine, which is hopefully easier
    to adapt. Checking for the value of end_type, one can make options
    only available under certain circumstances. After processing the
    command, set the `r` local value to `-1` if you want to stay within
    the end game menu loop, `1` if you want to return to the game, or
    `0` to quit out of the game.

### The code

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

    routine SpecialKey(end_type)
    {}

    routine SpecialRoutine
    {}

### How to configure

So, part of the point of this replacement is to make it easier to have
special options that only show up under certain circumstances (like an
AMUSING menu when you win a game). This section shows how one might do
that:

    ! in this game, the ending where the message shows up is endflag 3, so our NewMessages cases reflect that.
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

    replace SpecialKey(end_type)
    {
       if (end_type = 3) and (word[1] = "s","special")
          {
          return word[1]
          }
       else
          return false
    }

    replace SpecialRoutine
    {
             "\n\IWhat was the point of the second game? I won on my first try!\i"
             "The middle game was the author's somewhat feeble attempt to try to get the player to \BUNDO\b
             or \BSAVE\b (at a couple parts). If one does that, the game becomes unwinnable (usually).\n"
             "\IHow do I start over?\i"
             "Delete the \"ecto\" file from your interpreter's working directory. In Hugor, this should be
             the same directory as your gamefiles. With the official interpreter, this can be in different places,
             depending on  your OS (In Windows 7, it shows up in \BC:\\Users\\USER_NAME\\AppData\\Local\\VirtualStore\\Program Files (x86)\\Hugo)\b\n"
             "I hope you enjoyed the game!\n"
