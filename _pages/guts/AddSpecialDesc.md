---
title: "AddSpecialDesc"
permalink: /guts/addspecialdesc
categories: 
  - Hugo Guts
  - Routines
---

`AddSpecialDesc` is a companion routine to
[SpecialDesc](routines/specialdesc/). It is only called if a listed
object has an [inv_desc](properties/inv_desc/) or an applicable
[initial_desc](properties/descriptions/#initial_desc) property, which precludes it
from being listed with other "un-special" objects. `AddSpecialDesc` adds
[attributes](attributes/) like
[already_listed](attributes/already_listed/) and
[known](attributes/known/) to the object and adds to the `list_count`
[global](basics/global/).

## The code

    routine AddSpecialDesc(a)
    {
        a is already_listed
        a is known
        list_count++
        AssignPronoun(a)
    }
