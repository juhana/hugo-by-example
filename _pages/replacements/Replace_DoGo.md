---
title: Replace DoGo
permalink: /replacements/dogo/
categories: 
  - Replacements
---

### What it fixes

1.  Makes the "You'll have to get up..." message more
    [platform](attributes/platform/) and
    [container](attributes/container/) specific.
2.  Has new [vehicle](classes/vehicle/)-specific code to allow
    `parent(player).before` code with greater freedom for different
    directions that will exit. Requires this
    [vehicle replacement](replacements/vehicle/) to work.
3.  Also removes the jump.

### The code

    replace DoGo
    {
        local moveto, JumpToEnd
    #ifset NO_OBJLIB
        local wordnum, m
    #endif

        if player not in location               ! sitting on or in an obj.
        {
    #ifclear NO_OBJLIB
            if (object ~= u_obj and parent(player) is platform) or
                (object ~= out_obj and parent(player) is container)
            {
                VMessage(&DoGo, 3)      ! "You'll have to get up..."
                return false
            }
    #endif
            local b
            b = parent(player).before   ! i.e., a vehicle, etc.
            if b > 1 ! is b a direction?
                return Perform(&DoExit,parent(player))
            elseif b
                return false ! so the error message doesn't take up a turn
        }
        elseif obstacle
        {
    #ifclear NO_OBJLIB
            VMessage(&DoGo, 1)      ! "X stops you from going..."
            return true
    #endif
        }

    #ifclear NO_OBJLIB
        ! See if the object is one of the current direction set

        if object.type = direction and object in direction
        {
            moveto = object
            JumpToEnd = true
        }
    #endif

    if not JumpToEnd
    {
    #ifclear NO_OBJLIB
        if not moveto
        {
    #else
        wordnum = 1                             ! various phrasings
        if words > 1 and word[2] ~= ""
            wordnum = 2
        if word[2] = "to", "through"
            wordnum = 3
        elseif (word[2] = "in" or word[2] = "inside") and words > 2
            wordnum = 3

        select word[wordnum]
            case "north", "n":      m = n_to
            case "south", "s":      m = s_to
            case "east", "e":       m = e_to
            case "west", "w":       m = w_to
            case "northwest", "nw": m = nw_to
            case "northeast", "ne": m = ne_to
            case "southeast", "se": m = se_to
            case "southwest", "sw": m = sw_to
            case "up", "u":         m = u_to
            case "down", "d":       m = d_to
            case "in", "inside":    m = in_to
            case "out", "outside":  m = out_to

        if not m
        {
    #endif
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
    }  !  if not JumpToEnd bracket

    #ifclear NO_OBJLIB
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

            if not object
            {
                object = moveto
                if object.before
                    return true
            }
    !       else:  object = moveto
            moveto = location.(moveto.dir_to)

            if &moveto.door_to or moveto.type = door
            {
                moveto = moveto.door_to
            }
        }
    #else
        if m
        {
            if player not in location and m = out_to
            {
                if parent(player) is platform
                {
                    VMessage(&DoGo, 3)
                    return false
                }
                else
                    return Perform(&DoExit)
            }
            elseif player not in location and m = u_to
            {
                if parent(player) is container
                {
                    VMessage(&DoGo, 3)
                    return false
                }
                else
                    return Perform(&DoExit, parent(player))
            }

            moveto = location.m
            if moveto.door_to
                moveto = moveto.door_to
        }
    #endif

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
    !\ Recursive call issues
            m = verbroutine                 ! check room exiting
            verbroutine = &DoExit
            if location.before
                return true
            verbroutine = m
    \!
            MovePlayer(moveto)

            return true
        }
    }
