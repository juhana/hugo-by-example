---
title: DoOpen
permalink: /verb-routines/doopen/
categories: 
  - Verb Routines
---

`DoOpen` is the [verb routine](/verb-routines/)
responsible for processing "open" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoOpen
    {
        local tempformat

        if not CheckReach(object):  return false

        if object is not openable
        {
            VMessage(&DoOpen, 1)             ! "You can't open that."
            return
        }
        elseif object is open
            VMessage(&DoOpen, 2)             ! "It's already open."
        elseif object is locked
            VMessage(&DoOpen, 3)             ! "It's locked."
        else
        {
            object is open
            object is moved
            if not object.after
            {
                VMessage(&DoOpen, 4)     ! "Opened."

                FindLight(location)     ! in case the light source
                            ! has been revealed
                if children(object) and object is not quiet
                {
                    print ""
                    tempformat = FORMAT
                    FORMAT = FORMAT | NOINDENT_F
                    list_nest = 0
                    WhatsIn(object)
                    FORMAT = tempformat
                }
            }
        }
        return true
    }
