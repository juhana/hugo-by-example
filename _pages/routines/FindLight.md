---
title: FindLight
permalink: /routines/findlight/
categories: 
  - Routines
---

`FindLight` is a [hugolib.h](hugolib.h)
[routine](routine) that determines if a light source is
nearby. If it finds one, it sets the
[light_source](light_source) [global](global) to
that object. Otherwise, `FindLight` returns false and
[DarkWarning](DarkWarning) is run.

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
