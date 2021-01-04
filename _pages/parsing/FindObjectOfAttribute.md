---
title: FindObjectOfAttribute
permalink: /parsing/findobjectofattribute/
categories: 
  - Parsing
  - Routines
---

`FindObjectOfAttribute` is just a modification of
[FindObjectOfType](/parsing/findobjectoftype/) to work with attributes
instead of types. It was created mainly with characters in mind, who can
be of type "character" or type "female_character". Now the author can
check for attribute "living"! `FindObjectOfAttribute` ignores the player
object in its results.

## The code

    ! FindObjectOfAttribute(att, location)
    ! Used to find an object of attribute att; returns either the single available
    ! object, or nothing.

    routine FindObjectOfAttribute(att, loc)
    {
        local i, obj, suspect

        if loc = 0:  loc = location

        for i in loc
        {
            if i is att and i ~= player
            {
                suspect = i
            }
            elseif children(i) and (i is not container or i is open or i is not openable)
            {
                obj = FindObjectOfAttribute(att, i)
                if obj
                {
                    if suspect
                        ! More than 1
                        return nothing
                    else
                        suspect = obj
                }
            }
        }

        ! Only do the whole-tree check when loc is a room-level object:
        if parent(loc) = nothing and not suspect
        {
            for (i=1; i<=objects; i++)
            {
                if i is att and i ~= suspect and i ~= player
                {
                    if FindObject(i, location)
                    {
                        if suspect
                            ! More than one
                            return nothing
                        else
                            suspect = obj
                    }
                }
            }
        }
        return suspect
    }
