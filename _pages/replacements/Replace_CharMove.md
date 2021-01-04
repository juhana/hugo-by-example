---
title: Replace CharMove
permalink: /replacements/charmove/
categories: 
  - Replacements
---

### What it fixes

Exit-checking code works best when directions, in the case of
[doors](/classes/doors/), point to door objects themselves (not
door.door_to properties like the Hugo Book suggests).
[DoGo](/verb-routines/dogo/) still works fine that way, but `CharMove` needs
a little help. This is that help.

### The code


    replace CharMove(char, dir)
    {
    #ifclear NO_OBJLIB

        local newroom, a

        newroom = parent(char).(dir.dir_to)

        if newroom.type = door
            {
            a = newroom
            newroom = a.between #((parent(char) = \
                    a.between #1) + 1)
            if a is not open
                {
                if char in location or newroom = location
                    {
                    self = a
                    ""
                    OMessage(door, 5)
                    }
                }
            elseif newroom = location or char in location
                a = 0
            }

        if char in location and not a
        {
            Message(&CharMove, 1, char, dir)
            event_flag = true
        }

        move char to newroom

    #ifset DEBUG
        if debug_flags & D_SCRIPTS
        {
            print "["; CThe(char); IsorAre(char, true); " now in:  ";
            print capital parent(char).name; ".]"
        }
    #endif

        if char in location and not a
        {
            Message(&CharMove, 2, char, dir)
            event_flag = true
        }
        elseif char in location
            event_flag = true

    #endif  ! ifclear NO_OBJLIB

        run parent(char).after

        return true
    }
