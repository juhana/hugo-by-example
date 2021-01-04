---
title: Replace vehicle
permalink: /replacements/vehicle/
categories: 
  - Replacements
---

### What it fixes

1.  The `before` routine now returns a [direction](/classes/direction/)
    if it is a valid exit direction. Otherwise, it prints the regular
    "To walk, you'll have to get out..." message and returns true. This
    way, the `before` routine should be easy enough to
    [replace](/guts/replace/). If need be, the author can throw any
    further modification into the vehicle's
    [react_before](/properties/react_before/) property.

### The code

    replace vehicle
    {
        type vehicle
        vehicle_verb "drive"            ! default verb
        prep "in", "out"                !   "     prepositions
        vehicle_move true               ! by default, always ready to move

    #ifclear NO_VERBS
        before
        {
        parent(player) DoGo
            {
            if word[2] = "out" and object = self
                {
                object = out_obj
                return false
                }
            if (object ~= u_obj, out_obj) and object.type = direction
                {
                ! "To walk, you'll have to get out..."
                OMessage(vehicle, 1, self)
                return true
                }
            else
                return object
            }
        }
    #endif
        is enterable, static
    }
