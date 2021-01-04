---
title: Scenery
permalink: /basics/scenery/
categories: 
  - Basics
  - Classes
---

From *objlib.h*:

>Scenery objects are accessible to actions, but are not individually listed as part of the room contents (although their children are). They are intended to be mentioned in the room description, and still require explicit names, articles, nouns, and adjectives. The type property of a scenery object should never be changed.

## `scenery` class definition

    class scenery
    {
        type scenery
        exclude_from_all
        {
    #ifclear NO_VERBS
            if verbroutine = &DoGet    ! In games that use the standard verb library,
                return true        ! this object will be skipped by commands such
            else                       ! as >GET ALL
    #endif
                return false
        }
        is static, hidden
    }

The [static](attributes/) attribute keeps the player from
moving or getting the object. The [hidden](attributes/)
attribute keeps the item from being listed as a room content. This is
why the `scenery` class is often used for objects already mentioned in a
room's description or for objects that are strongly implied.

### for example

    scenery asphalt "asphalt driveway"
    {
    article "the"
    adjective "asphalt"
    noun "driveway"
    long_desc
       "You don't say this often, but this driveway was paved \Ireally\i well. Man."
    in InTheDriveway
    }
