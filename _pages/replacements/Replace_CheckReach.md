---
title: Replace CheckReach
permalink: /replacements/checkreach/
categories: 
  - Replacements
---

### What it fixes

The original [CheckReach](routines/checkreach/) can be fooled by some
instances of [components](classes/components/). This version checks
than an object is not a part of something within reach before returning
false.

### The code

    replace CheckReach(obj)
    {
        local i,p

        if not obj or obj = parent(player)
            return true

    #ifclear NO_VERBS
        if (verbroutine ~= &DoLook, &DoLookIn) and parent(object) and
            parent(object) ~= player and
            parent(object) is transparent and parent(object) is not open and
            parent(object) is not living
        {
            VMessage(&DoGet, 5)     ! "X is closed."
            return false
        }
    #endif

        if not parent(player).reach or
           Contains(parent(player), obj)
            return true

        p = obj.part_of
        while p
        {
        if Contains(parent(player), p)
            return true
        p = p.part_of
        }

    #ifclear NO_VERBS
        if parent(obj) is living
        {
            if verbroutine ~= &DoGet, &DoLook

                ! "Except that X has it..."
                Message(&CheckReach, 1, obj)

            elseif verbroutine = &DoGet and parent(obj) is unfriendly

                ! "Except that X doesn't want to give it to you..."
                Message(&CheckReach, 2, obj)
        }
    #endif

        for (i=1; i<=parent(player).#reach; i++)
        {
         if Contains(parent(player).reach #i, obj) or   ! is the object inside a reach object
              obj = parent(player).reach #i ! is the object a reach object
            {
                return true
            }
        }

        p = obj.part_of
        while p
        {
        for (i=1; i<=parent(player).#reach; i++)
        {
         if Contains(parent(player).reach #i, p) or ! is the object part of an object inside the reach object
              p = parent(player).reach #i ! is the object part of a reach object
            {
                return true
            }
        }
        p = p.part_of
        }

    #ifset USE_ATTACHABLES
        if parent(player).type = attachable
        {
            if InList(parent(player), attached_to, obj)
                return true
        }
        if obj.type = attachable
        {
            if InList(obj, attached_to, parent(player))
                return true
        }
    #endif

        ! "You can't reach it..."
        Message(&CheckReach, 3, obj)
    }
