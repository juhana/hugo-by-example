---
title: DoLookIn
permalink: /verb-routines/dolookin/
categories: 
  - Verb Routines
---

`DoLookIn` is the [verb routine](:Category:Verb_Routines)
responsible for processing "look in" or "look on" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoLookIn
    {
        local tempformat

        if not CheckReach(object):  return false

        if not light_source
            VMessage(&DoLook, 1)     ! "It's too dark to see anything."
        else
        {
            if object is container and (object is openable and
                object is not open and object is not transparent):
                VMessage(&DoLookIn, 1)           ! "It's closed."
            else
            {
                if not object.after
                {
                    object is not quiet

                    tempformat = FORMAT
                    FORMAT = FORMAT | NOINDENT_F
                    list_nest = 0

                    if WhatsIn(object) = 0
                        VMessage(&DoLookIn, 2)   ! "It's empty."

                    FORMAT = tempformat
                }
            }
            return true
        }
    }
