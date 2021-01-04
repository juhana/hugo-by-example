---
title: "AddSpecialDesc"
permalink: /guts/addspecialdesc
categories: 
  - Hugo Guts
  - Routines
---

`AddSpecialDesc` is a companion routine to
[SpecialDesc](SpecialDesc). It is only called if a listed
object has an [inv_desc](inv_desc) or an applicable
[initial_desc](initial_desc) property, which precludes it
from being listed with other "un-special" objects. `AddSpecialDesc` adds
[attributes](attributes) like
[already_listed](already_listed) and
[known](known) to the object and adds to the `list_count`
[global](global).

## The code

    routine AddSpecialDesc(a)
    {
        a is already_listed
        a is known
        list_count++
        AssignPronoun(a)
    }
