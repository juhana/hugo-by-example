---
title: RandMove
permalink: /contributions/randmove/
categories: 
  - Library Contributions
---

`RandMove` is Cardinal Teulbach's library contribution for random NPC
movement. It replaces the [character script](characters/scripts/) routine
`CharMove` and uses a new property to keep track of where characters can
go. You can see it
[here](http://ifarchive.smallwhitehouse.org/if-archive/programming/hugo/library/contributions/randmove.txt).

### Required Modifications

As this code was written for Hugo in the *2.1* days, it works
surprisingly well. The one problem that someone might run into only
comes up if you are compiling your game with
HugoFix. To fix it, change the following code:

    #ifset DEBUG
        if _sc_flag
        {
            print "["; CThe(char); IsorAre(char, true); " now in:  ";
            print capital parent(char).name; ".]"
        }
    #endif

To:

    #ifset DEBUG
        if (debug_flags & D_SCRIPTS)
        {
            print "["; CThe(char); IsorAre(char, true); " now in:  ";
            print capital parent(char).name; ".]"
        }
    #endif

(Only one line is different; the others were just included to help
identify the section.)

# Alternatively...

`RandMove` works fine (with the above modification), but it may have
some unnecessary code, as Hugo has come a ways since then. The following
code inherits `RandMove`'s `npc_move` property but throws the
randomization code into the character's `before` routines.

    ! somewhere in the game, you'd start the character script that gets the character moving
    ! in this example, we'll do it in the init routine
    routine init
    {
       ! ... all of your other init code
       setscript[Script (fred, 3)] = &CharMove, 0, &CharMove, 0, &LoopScript, 0
    }

    ! now we define the npc_move property before any object that uses it
    property npc_move

    player_character you "you"
    {
    }

    room STARTLOCATION "Start Location"
    {
        e_to room1
        s_to room2
        w_to room3
        npc_move e_obj s_obj w_obj
    }

    character fred "Fred"
    {
        noun "fred"
        in STARTLOCATION
        before
            {
            actor CharMove
                {
                if not object ! check if we want the character to move randomly or a specific direction
                    {
                                    ! check to see if there are exits defined for this room
                    if not parent(self).#npc_move
                        return true  ! if no exits, do nothing
                    local a
                    a = random((parent(self).#npc_move)) ! pick a random number from the number of exits
                    CharMove(self, parent(self).npc_move #a) ! have the character move in that direction
                    return true
                    }
                return false
                }
            }
    }

    ! just a bunch of rooms for Fred to move around in

    room room1 "east room"
    {
        w_to {return reddoor.door_to}
        s_to {return bluedoor.door_to}
        npc_move w_obj s_obj
    }

    door reddoor "red door"
    {
        adjective "red"
        noun "door"
        article "the"
        between STARTLOCATION room1
    }

    door bluedoor "blue door"
    {
        adjective "blue"
        noun "door"
        article "the"
        between room1 room4
    }
    room room4 "southeast room"
    {
            npc_move n_obj w_obj
        n_to {return bluedoor.door_to}
        w_to room2
    }

    room room2 "south room"
    {
        npc_move n_obj e_obj w_obj
        n_to STARTLOCATION
        e_to room4
        w_to room5
    }

    room room5 "southwest room"
    {
        npc_move n_obj e_obj
        n_to room3
        e_to room2
    }

    room room3 "west room"
    {
        npc_move e_obj s_obj
        e_to STARTLOCATION
        s_to room5
    }
