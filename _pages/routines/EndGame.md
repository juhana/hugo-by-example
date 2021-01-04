---
title: EndGame
permalink: /routines/endgame/
categories: 
  - Routines
---

`EndGame(end_type)` provides the **RESTART, RESTORE, (UNDO), or QUIT**
dialogue at the end of a play session.

Also see: [PrintEndGame](/routines/printendgame/)

### The code

Here is the `EndGame` routine. You may be particularly interested in how
different switches affect its functionality. For instance, if your game
has the NO_UNDO switch set, "undo" will not be listed as an option
(this can also be accomplished by setting the `UNDO_OFF` 
[global variable](/basics/global/) to true).

    !----------------------------------------------------------------------------
    ! EndGame(end_type)
    ! called by the engine via EndGame(end_type) when endflag is not false
    ! (endflag is cleared previous to calling); return false to terminate
    !
    ! Default responses (in PrintEndGame):  1 = win, 2 = die, 0 = no response

    routine EndGame(end_type)
    {
        PrintStatusLine                 ! update one last time
        PrintEndGame(end_type)          ! print appropriate ending message

    #ifclear NO_VERBS
        local r

    :AskAgain

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

        if r = -1:  jump AskAgain

        return r

    #else   ! i.e., #elseif set NO_VERBS

        return 0;
    #endif
    }
