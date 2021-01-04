---
title: list_contents
permalink: /properties/list_contents/
categories: 
  - Properties
---

`list_contents`, when true, precludes an object or room's contents from
being listed as usual. Because of this, it defaults to false, but it can
be very useful.

### Careful what you look for

Sometimes you'll want to prevent contents from being listed altogether
(like with [vehicles](vehicles) or something). Other times,
say, you might have a non-[hidden](hidden),
not-[quiet](quiet) container in a room, but you only want the
player to see the contents if he specifically *looks into it* (and not,
say, in the room description). Do something like this:

    object cauldron "cauldron"
    {
       noun "cauldron"
       in CauldronRoom
       is container, open
       list_contents
       {
          ! Skip contents-listing if not looking specifically inside
          if verbroutine ~= &DoLookIn
          {
               return 1
          }
          else
          {
                return 0
          }
       }
    }

    object oysters "oysters"
    {
       noun "oysters"
       is plural
       in cauldron
    }
