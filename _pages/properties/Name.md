---
title: name
permalink: /properties/name/
categories: 
  - Properties
---

The **`name`** [property](property) is defined as an
intrinsic property by the compiler. It determines the name used when an
object is listed in an inventory or room listing (or even in the object
tree). Because it is intrinsic, all [objects](objects) are
given a *name* property.

In the following code:


    object puppy "Fred"
    {
        in livingroom
        is living
    }

    object puppytopic
    {
         long_desc
               "This is some kind of dummy object used for an object-based conversation system."
    }

Both objects have names. In the first example, the puppy object's name
is "Fred." In the second object, the name is "(puppytopic)". The
parentheses are added automatically by the compiler.

## Changing Names

Names, like any other property, can be changed mid-game. This can be
useful for both locations or objects where state changes dramatically.


    object egg "egg"
    {
         after
         {
         object DoHit
               {
               if self.name = "egg"
                     {
                     "You smash the egg."
                     self.name = "broken egg"
                     }
               "You're unlikely to cause any more damage."
               }
         }
    }

## Conditional Names

If you want to have a situation where an object or room's `name`
property returns different names depending on external values, have the
conditional code return the string itself, like this:

    room STARTLOCATION
    {
        name    {
            if not changebit  ! changebit is some global we are testing for
                return "Start Location"
            else
                return "Start Location Take Two"
            }
    }
