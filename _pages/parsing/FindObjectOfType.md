---
title: FindObjectOfType
permalink: /parsing/findobjectoftype/
categories: 
  - Parsing
  - Routines
---

Kent Tessman's **Future Boy!** has a lot of parser-helping routines.
Whenever possible, if the player didn't specify *every* part of a
command (like, for example, *which* book should be consulted), **Future
Boy!** executes `FindObjectOfType` which goes through every object in
the current location and returns the first object found of a certain
type (like, a book).

See [FindObjectOfAttribute](/parsing/findobjectofattribute/) for a
version that works off of attributes.

## The code

    ! FindObjectOfType(t, location)
    ! Used to find an object of type t; returns either the single available
    ! object, or nothing.

    routine FindObjectOfType(t, loc)
    {
        local i, obj, suspect

        if loc = 0:  loc = location

        for i in loc
        {
            if i.type = t
            {
                suspect = i
            }
            elseif children(i) and (i is not container or i is open or i is not openable)
            {
                obj = FindObjectOfType(t, i)
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
                if i.type = t and i ~= suspect
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
