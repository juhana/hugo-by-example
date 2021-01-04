---
title: DoDrop
permalink: /verb-routines/dodrop/
categories: 
  - Verb Routines
---

`DoDrop` is the [verb routine](/verb-routines/)
responsible for processing "drop" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoDrop
    {
        if object is clothing and object is worn
            VMessage(&DoDrop, 1)     ! "You'll have to take it off first."

        ! For the following, xobject is true only
        ! when called by DoPutonGround:
        elseif player not in location and (parent(player) is container or
            parent(player) is platform) and not xobject
        {
            Perform(&DoPutIn, object, parent(player))
        }
        else
        {
            move object to location
            object is moved
            player.holding = player.holding - object.size
            if not object.after
                VMessage(&DoDrop, 2)     ! "Dropped."
        }
        xobject = 0
        return true
    }
