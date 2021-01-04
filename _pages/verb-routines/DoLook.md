---
title: DoLook
permalink: /verb-routines/dolook/
categories: 
  - Verb Routines
---

`DoLook` is the [verb routine](verb-routines/)
responsible for looking at objects.

## The code

    !----------------------------------------------------------------------------
    routine DoLook
    {
        local i

        if not light_source
            VMessage(&DoLook, 1)     ! "It's too dark to see anything."
        else
        {
            if not object.long_desc
                ! "Looks just like you'd expect..."
                VMessage(&DoLook, 2)

    !       if object is living, transparent, not quiet
            if ((object is living, transparent) or
                object is platform or
                (object is container and (object is open or object is not openable))) and
                object is not quiet and object is not already_listed
            {
                for i in object
                {
                    if i is not hidden
                        break
                }
                if i and object ~= player
                {
                    local tempformat
                    tempformat = FORMAT
                    FORMAT = FORMAT | NOINDENT_F
                    list_nest = 0
                    print ""
                    WhatsIn(object)
                    FORMAT = tempformat
                }
            }

            run object.after
            return true
        }
    }
