---
title: MovePlayer
permalink: /routines/moveplayer/
categories: 
  - Routine
---

`MovePlayer` is a routine specifically written for moving the player to
another location, saving us the trouble of updating the [location
global](Variables#Global_Variables), among other things. For
instance, it also checks to checks that the new location has a light
source and runs `DarkWarning`, if necessary. Let's break it down:
The first argument (`loc` or `dir`) is either the location object we are
moving the player to or a direction object (n_to, e_to, etc.). If it's
the latter, `MovePlayer` only moves the player if it's a valid
direction.
The second argument {`silent`) determines whether
[DescribePlace](DescribePlace) should be executed after we
move the player, giving the name and description of the new location.
The last argument (`ignore`) determines whether we want to run any
`player.before` or `player.after` code. Imagine a game where moving the
player (such as the wand or &gt;XYZZY in Adventure) gives him an odd
feeling:

    player_character you "you"
    {
        before
            {
            actor MovePlayer
                {
                "Your whole body tingles."
                return false ! so the player still is moved by MovePlayer
                }
            }
        after
            {
            actor MovePlayer
                {
                "The odd tingling subsides."
                return true
                }
            }
    }

Having an `ignore` value would skip both of those statements.
Ta-da!

## the code

For the sake of browsing, here is the routine itself:

    !----------------------------------------------------------------------------
    ! MovePlayer(location[, silent])
    ! moves the player to the object <location>, with no description if <silent>
    ! is true
    !
    ! MovePlayer(direction[, silent[, ignore]])
    ! moves player in <direction>, where <direction> is a direction object.
    ! If <ignore> is true, before/after routines relating to the move are
    ! not checked.
    !
    ! MovePlayer calls DarkWarning when there is no light source in the new
    ! location; replace it with a new DarkWarning routine for a more elaborate
    ! response, such as the possible demise of the player

    routine MovePlayer(loc, silent, ignore)
    {
        local v, obj, xobj, act, ret

    #ifclear NO_OBJLIB
        if loc.type = direction
        {
            local l
            l = location.(loc.dir_to)
            if l > 1                ! since a message always returns 1
                loc = l
            else
                return
        }
    #endif

    #ifset USE_ATTACHABLES
        if ObjectisAttached(player, location, loc)
            return
    #endif

        ! Check if there's a before routine for MovePlayer in the new
        ! location.  Note that the (potential) new location and the old
        ! location are stored in object and xobject, respectively.
        !
        v = verbroutine
        obj = object
        xobj = xobject
        act = actor
        verbroutine = &MovePlayer
        object = loc
        xobject = location
        actor = player
        if not ignore
        {
            ret = player.before
            if ret:  jump LeaveMovePlayer
            ret = location.before
            if ret:  jump LeaveMovePlayer
            ret = loc.before
            if ret:  jump LeaveMovePlayer
        }

        move player to loc
        old_location = location
        if parent(loc) = 0              ! if it's likely a room object
            location = loc
        else                            ! if it's an enterable object
            location = parent(loc)  ! (noting that the object must be
                        ! in a room, not inside another
                        ! non-room object)

    #ifset USE_ATTACHABLES
        MoveAllAttachables(player, old_location, location)
    #endif

        PrintStatusline

    :LeaveMovePlayer

        if not ret
        {
            if not FindLight(location)
                DarkWarning
            elseif not silent
            {
                DescribePlace(location)
                event_flag = true
                location is visited
            }

        ! Check if there's an after routine for MovePlayer in the new
        ! location:
        !
            if not ignore
            {
                ret = player.after
                if not ret
                    ret = location.after
            }
        }

        verbroutine = v
        object = obj
        xobject = xobj
        actor = act

        return ret
    }
