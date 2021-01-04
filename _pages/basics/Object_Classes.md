---
title: Object Classes
permalink: /basics/object_classes/
categories:
  - Basics
---

The **class** directive is a definition of a template
[object](globals/object/), that is, a particular object that has some
predefined [declarations](declarations/) of
[attributes](attributes/), [code](definitions/code/) including
[before](properties/before/) and [after](properties/after/) code, and/or
[properties](properties/).

A class is defined the same way as an object

    class <classname> ["optional name"]
    {

    [ declarations and code related to that class of object ]

    }

You define the class to describe the declarations

    class bear
    {
        is fuzzy
        article "a"
        size 45
        adjective "bear"
    }

Then you create objects of that class by naming them using the class
name instead of "object". So the class is used like this:

    bear teddy "extraordinary teddy bear"
    {
       adjective "teddy"
       article "an"
    }

    bear soft "soft teddy bear"
    {

    }

This automatically defines every object of class **bear**, has
predefined attribute fuzzy, is prefixed with "a", and has a specific
size and adjective used to access it by the player. These can be
overridden in the case of "teddy" which defines its adjective as "teddy"
and its article as "an" (replacing the class definition of "a" so that
it's listed as "an extraordinary teddy bear" instead of "a extraordinary
teddy bear"). The "soft" bear has everything it needs defined by the
class, so it has nothing added to it.

Object classes are a time-saving feature that are useful when a game has
a lot of objects that share the same properties. Several classes are
already defined in *objlib.h*. Some instances:

    !----------------------------------------------------------------------------
    ! BASIC ROOM:
    !----------------------------------------------------------------------------

    class room
    {
        type room
        is static, light, open
    }

    !----------------------------------------------------------------------------
    ! STANDARD CHARACTERS:
    !----------------------------------------------------------------------------

    class character
    {
        type character
        pronouns "he", "him", "his", "himself"
        capacity 50
        holding 0
        is living, transparent, static
    }

    !----------------------------------------------------------------------------
    ! COMPASS DIRECTIONS:
    !----------------------------------------------------------------------------

    property dir_to alias capacity          ! for directions only
    property dir_from alias size            !

    class direction
    {
        type direction
        article "the"
        found_in
        {
            if self in direction
                return location
        }
        long_desc
        {
            OMessage(direction, 1)
        }
        is static, known
    }

    ! and now let's show an object from the direction class

    direction n_obj "north"
    {
        in direction
        nouns "n", "north"
        dir_to n_to
        dir_from s_obj
    }

    !----------------------------------------------------------------------------
    ! SCENERY:
    !
    ! Scenery objects are accessible to actions, but are not individually listed
    ! as part of the room contents (although their children are).  They are
    ! intended to be mentioned in the room description, and still require
    ! explicit names, articles, nouns, and adjectives.  The type property
    ! of a scenery object should never be changed.
    !----------------------------------------------------------------------------

    class scenery
    {
        type scenery
        exclude_from_all
        {
    #ifclear NO_VERBS
            if verbroutine = &DoGet
                return true
            else
    #endif
                return false
        }
        is static, hidden
    }

It is class descriptions like the above that allows for code like this:


    room StartRoom "First Room"
    {
         e_to SecondRoom
    }

    scenery lamp "lamp"
    {
         in StartRoom
    }

Because of the class declarations, we know (among other things):

1. StartRoom will have light
2. `e_to` is a valid property
3. lamp will not be mentioned and cannot be moved (or taken)

### Using the property "borrowing" technique with classes

When you have an object of type class, if you define a pre-existing
property, it completely overwrites the original code (this is why it's
good to always be aware of what exactly is defined in the original
case). For instance, if you add some more `nouns` to the
`player_character` object, it'll overwrite the pre-existing nouns, "me"
and "myself."

Instead of re-writing everything, though, you can do what the manual
calls "borrowing" properties. The example from the manual:

    class food
    {
         bites_left 5
         eating
              {
              self.bites_left = self.bites_left - 1
              if self.bites_left = 0
              remove self ! all gone
              }
    }

    food health_food
    {
         eating
              {
              actor.health = actor.health + 1
              run food..eating
              }
    }

In the above example, health_food has its own `eating` instruction, but
the `run food..eating` line runs `food.eating` with `self` set to
`health_food`, not `food`.

Of course, property borrowing isn't limited to object class usage, but
it can be especially useful with classes.
