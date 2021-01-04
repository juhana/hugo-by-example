---
title: Descriptions
permalink: /properties/descriptions/
categories: 
  - Basics
  - Properties
---

Hugo offers three types of descriptions in the standard library. These
are long_desc, short_desc and initial_desc. 

### long_desc

The long_desc is a property that holds the description used when
looking at or examining an object. When used on the
[room](rooms) object, the long description is what appears
when the the room is first visited (unless there's an initial_desc
defined). For other objects, this is used when the player examines the
object.

    object photograph "photograph"
    {
        long_desc
           "It's an old, black and white photograph of your father, standing next to his prized banana tree."
    }

### short_desc

This is basically used for `X is here` descriptions.

    object photograph "photograph"
    {
         long_desc
            "It's an old, black and white photograph of your father, standing next to his prized banana tree."

         short_desc
            "A black and white photograph is here."
    }

##### `when_open` and `when_closed`

[Unhidden](hidden), [openable](openable)
[objects](objects) in the [room](rooms) can have
special descriptions, depending on whether they are
[open](open) or closed. In that case, the matching property
is called instead of `short_desc`.

    object treasurechest "treasure chest"
    {
        article "the"
        adjective "treasure"
        noun "chest"
        is openable static container
        long_desc
             "<long description>"
        when_open
             "A treasure chest sits in the corner, doubloons practically spilling out."
        when_closed
             "A treasure chest sits in the corner, closed, keeping its contents a mystery."
    }

### initial_desc

If the object has not been `moved` (or the room is not `visited`) this
description is displayed instead of the `long_desc` or `short_desc`

    object photograph "photograph"
    {
         long_desc
            "It's an old, black and white photograph of your father, standing next to his prized banana tree."

         short_desc
            "A black and white photograph is here."

         initial_desc
            "A piece of paper is on the floor near the desk."
    }
