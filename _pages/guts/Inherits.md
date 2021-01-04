---
title: Inherits
permalink: /guts/inherits/
categories: 
  - Hugo Guts
---

`inherits` is a convenient command for when you'd like one object to its
properties from more than one [object class](Object_Classes).

    <class1> <objectname> "name"
    {
    inherits <class2>[, <class3>,...]
    ...
    }
    ! or even
    object <objectname> "name"
    {
    inherits <class1>, <class2>[, <class3>,...]
    ...
    }

More commonly, it is used as a convenient way to add properties quickly
to objects not of a particular class.
[Timesasked.h](Timesasked.h) uses it like so:

    class topics
    {
        timesasked #TOTALCHARACTERS
        timestold #TOTALCHARACTERS
    }

    player_character you "you"
    {
        inherits topics ! we can ask about ourselves
    }

    room STARTLOCATION "Start Location"
    {
        noun "room"
        inherits topics
    }
