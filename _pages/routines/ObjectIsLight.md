---
title: ObjectIsLight
permalink: /routines/objectislight/
categories: 
  - Routines
---

*See also: [FindLight](/routines/findlight/)*

`ObjectIsLight` checks if an object (or an object within it) has the
[light](/attributes/light/) attribute. If it finds one, it sets that
object as the [light_source](/globals/light_source/)
[global](/basics/global/) and returns true.

## The code

    routine ObjectisLight(obj)
    {
        local nextobj

        if obj is light
        {
            light_source = obj
            return light_source
        }
        if obj is not container or
            (obj is container and obj is not openable) or
            (obj is container and obj is openable and
                (obj is open or obj is transparent))
        {
            for nextobj in obj
            {
                if ObjectisLight(nextobj)
                    return light_source
            }
        }
    }
