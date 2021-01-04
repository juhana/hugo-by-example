---
title: Acquire
permalink: /guts/acquire
categories: 
  - Hugo Guts
---

`Acquire` is a [hugolib.h](hugolib.h)
[routine](routine) for moving objects into
[containers](containers) or
[platforms](platforms). Unlike a straight
`move <object> to <other object>`, it only performs the move if the
possible parent object has room for the possible child (it uses
[size](size), [holding](holding), and
[capacity](capacity) properties to determine this). If not
possible, it returns false. This way, verb routines can have both
successful and unsuccessful attempt messages.

## The code

    !----------------------------------------------------------------------------
    ! Acquire(object 1, object 2)
    ! moves <object 2> to <object 1>; returns true if successful

    routine Acquire(newparent, newchild)
    {
        local p

        CalculateHolding(newparent)

        if newparent.holding + newchild.size > newparent.capacity
            return false
        else
        {
            p = parent(newchild)
            move newchild to newparent
            CalculateHolding(p)
            newchild is moved
            newchild is not hidden
            newparent.holding = newparent.holding + newchild.size
            return true
        }
    }
