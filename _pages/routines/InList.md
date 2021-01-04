---
title: InList
permalink: /routines/inlist/
categories: 
  - Routines
---

`InList` is a [hugolib.h](hugolib.h)
[routine](routine) invaluable to anyone who uses property
arrays to hold information. Providing the routine with those parameters,
`InList` will return true (specifically, it returns the
[property](properties) element number) or false depending on
whether `val` is in `object`'s `property` array. Routines like
[CheckReach](CheckReach) use `InList` to check if objects are
in other object's property (in `CheckReach`'s case, the
[reach](reach) property).

## The code

    !----------------------------------------------------------------------------
    ! InList(object, property, val)
    ! returns false if <val> is not contained in the list of values held in
    ! <object>.<property>; otherwise returns the number of the (first) property
    ! element equal to <val>

    routine InList(obj, prop, val)
    {
        local i

        for (i=1; i<=obj.#prop; i++)
        {
            if obj.prop #i = val:  return i
        }
    }
