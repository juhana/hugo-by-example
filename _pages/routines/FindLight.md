---
title: FindLight
permalink: /routines/findlight/
categories: 
  - Routines
---

`FindLight` is a [hugolib.h](/library/hugolib.h/)
[routine](/routines/) that determines if a light source is
nearby. If it finds one, it sets the
[light_source](/globals/light_source/) [global](/basics/global/) to
that object. Otherwise, `FindLight` returns false and
[DarkWarning](/guts/darkwarning/) is run.

## The code

    !----------------------------------------------------------------------------
    ! FindLight(object)
    ! returns the object number of light_source if any light is visible from
    ! within <object> (where <object> is usually a location)
    !
    ! ObjectisLight is called by FindLight

    routine FindLight(loc)
    {
        light_source = 0

        if loc is light
        {
            light_source = loc
            return light_source
        }
        elseif ObjectisLight(player)
            return light_source
        return ObjectisLight(loc)
    }
