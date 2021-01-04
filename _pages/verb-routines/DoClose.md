---
title: DoClose
permalink: /verb-routines/doclose/
categories: 
  - Verb Routines
---

`DoClose` is the [verb routine](/verb-routines/)
responsible for processing "close" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoClose
    {
        if not CheckReach(object):  return false

        if object is not openable
        {
            VMessage(&DoClose, 1)            ! "You can't close that."
            return
        }
        elseif object is not open
            VMessage(&DoClose, 2)            ! "It's already closed."
        else
        {
            object is not open
            object is moved
            if not object.after
                VMessage(&DoClose, 3)    ! "Closed."

            if not FindLight(location)      ! in case the light source
                            ! has been concealed

                VMessage(&DoClose, 4)    ! "Everything goes dark."
        }
        return true
    }
