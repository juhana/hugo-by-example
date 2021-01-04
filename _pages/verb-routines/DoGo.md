---
title: DoGo
permalink: /verb-routines/dogo/
categories: 
  - Verb Routines
---

`DoGo` is the verb routine used almost every time the player goes
anywhere (surprise, surprise). As authors, we often want to interject
messages or otherwise modify the normal behavior, so a good
understanding of `DoGo` is beneficial. In the section below, the `DoGo`
routine is presented. Support for games that don't include
*objlib.h* has been omitted in an effort to make it
slightly more readable (it's a multifaceted routine).

## The DoGo "walkthrough"

Reading it from top to bottom, we can see it do the following things:

1.  If the player is in another object (a vehicle or, say, on a couch):
    1.  directions other than "up" and "out" will give a "You'll have to
        get out." message. Keep this in mind when you have objects that
        a player should be able to leave by typing "down" (like a
        horse).
    2.  The player's parent object is checked for a `before` routine.
        Uunfortunately, this code is only reached if the direction is
        "up" or "out" and if there *is* a `before` routine, a turn will
        pass (which is suboptimal for certain messages).
2.  If the [obstacle](/globals/obstacle/) variable has been set to an
    object, it prints the response "<object> stops you from going."
3.  If the direction object is valid, jump ahead to the "valid
    direction" section.
4.  If there isn't an object (or if there *is* an object but it isn't a
    direction object):
    1.  If no object, say "Which way?"
    2.  If the object doesn't have a [door_to](/properties/door_to/)
        property, check if it's [enterable](/attributes/). If
        so, enter the object.
    3.  Set the `moveto` local variable to the object's
        [door_to](/properties/door_to/) property.
        1.  If `moveto` = 0 (there was no [door_to](/properties/door_to/)
            property), say "You can't enter that."
        2.  If `moveto` = 1, the [door_to](/properties/door_to/) property
            was just a printed string. DoGo will just leave it at that.
        3.  (at the bottom of the routine) Perform
            [MovePlayer](/routines/moveplayer/)(`moveto`)
5.  If the object is a valid direction (or if the above
    [door_to](/properties/door_to/) code had returned a direction object
    instead of a room object):
    1.  If the player is in an object:
        1.  If the player is on a platform, any direction other than
            "up" will give a "you'll have to go out" message (and "up"
            will successfully exit).
        2.  If the player is in a container, any direction other than
            "out" will give a "you'll have to go out" message (and "out"
            will successfully exit).
    2.  Reset `moveto` to whatever the current direction leads to.
        1.  If it returns an object with a
            [door_to](/properties/door_to/) property or a door, change
            `moveto` to the [door_to](/properties/door_to/) property.
    3.  If `moveto` is false (there's no exit in that direction):
        1.  Check if the current location has a
            [cant_go](/properties/cant_go/) property and print it. If
            not, do the default "You can't go that way." message.
        2.  If `moveto` = 1, the direction only printed something.
    4.  Again, if the player is in something, there is a "You'll have to
        get up." message
    5.  Lastly- and we should only get to this code if `moveto` is set
        to a viable room location- [MovePlayer](/routines/moveplayer/)
        the player to that location.

## The code

    routine DoGo
    {
        local moveto

        if player not in location               ! sitting on or in an obj.
        {
            if object ~= u_obj and object ~= out_obj
                {
                VMessage(&DoGo, 3)      ! "You'll have to get up..."
                return false
                }
            if parent(player).before    ! i.e., a vehicle, etc.
                return true
        }
        elseif obstacle
        {
            VMessage(&DoGo, 1)      ! "X stops you from going..."
            return true
        }

        ! See if the object is one of the current direction set
        if object.type = direction and object in direction
            {
            moveto = object
            jump FoundDirection
            }

        if not moveto
            {
            if not object
                {
                ! ParseError(6)  ! doesn't make any sense
                VMessage(&DoGo, 4)  ! "Which way...?"
                return
                }
            if not &object.door_to
                {
                if not object.door_to and object is enterable
                    return Perform(&DoEnter, object)
                }
            moveto = object.door_to
            if not moveto
                {
                VMessage(&DoEnter, 2)  ! "You can't enter..."
                return
                }
            if moveto = 1
                return true
            }

    :FoundDirection
        if moveto.type = direction and moveto in direction
            {
            if player not in location and object = out_obj
                {
                if parent(player) is platform
                    {
                    VMessage(&DoGo, 3)
                    return false
                    }
                else
                    return Perform(&DoExit)
                }
            elseif player not in location and object = u_obj
                {
                if parent(player) is container
                    {
                    VMessage(&DoGo, 3)
                    return false
                    }
                else
                    return Perform(&DoExit, parent(player))
                }

            moveto = location.(moveto.dir_to)
            if &moveto.door_to or moveto.type = door
                moveto = moveto.door_to
            }

        if moveto = false
            {
            if not location.cant_go
                VMessage(&DoGo, 2)      ! "You can't go that way."
            return false
            }

        elseif moveto = true                    ! already printed message
            return true                     ! (moveto is never 1)

        elseif player not in location           ! sitting on or in an obj.
            {
            VMessage(&DoGo, 3)              ! "You'll have to get up..."
            }
        else
            {
            MovePlayer(moveto)
            return true
            }
    }
