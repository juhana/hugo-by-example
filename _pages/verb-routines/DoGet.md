---
title: DoGet
permalink: /verb-routines/doget/
categories: 
  - Verb Routines
---

`DoGet` is the [verb routine](/verb-routines/)
responsible for processing "get" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoGet
    {
        local b, p

        if object in player
            VMessage(&DoGet, 1)      ! "You already have that."
        elseif object = player
        {
            VMessage(&DoGet, 2)     ! player trying to get player
            return false
        }
        elseif object is living and object is static
        {
            VMessage(&DoGet, 3)     ! player trying to get character
            return false
        }
        elseif parent(object) is living and parent(object) is unfriendly
            VMessage(&DoGet, 4)      ! "X doesn't want to give it to you."
        elseif (parent(object) is openable, not open) and
            parent(object) is container:
        {
            VMessage(&DoGet, 5)     ! "X is closed."
            return false
        }
        elseif Contains(object, player)
        {
            if object is static
                VMessage(&DoGet, 7) ! "You can't take that."
            else
                VMessage(&DoGet, 6)     ! "Not while you're in/on it..."
            return false
        }
        else
        {
            if not CheckReach(object)
                return false
            elseif object is static
            {
                VMessage(&DoGet, 7)      ! "You can't take that."
                return true
            }

            ! Because the engine calls location.before
            if (parent(object)~=location)
                b = parent(object).before

            if not b
            {
                xobject = parent(object)

                if object not in location
                {
                    CalculateHolding(xobject)
                    p = xobject
                }

                if Acquire(player, object)
                {
                    object is not hidden

                    if not object.after
                    {
                        ! Again, to avoid duplication or
                        ! echoing:
                        !
                        b = 0
                        if xobject ~= location
                            b = xobject.after

                        if b = false
                            ! "Taken."
                            VMessage(&DoGet, 8)
                    }
                }
                else
                    ! "You're carrying too much to take that."
                    VMessage(&DoGet, 9)
            }
        }
        return true
    }
