---
title: order_response
permalink: /properties/order_response/
categories: 
  - Properties
---

**`order_response`** is a [property](properties/) defined by the
[standard library](library/) and is an alias for the
directional property [sw_to](directions/sw_to/). It may look like a
simple object property, but with the help of the
[SpeakTo](parsing/speakto/) routine, all character commands
(&gt;CLOWN, MAKE BALLOON ANIMAL) are funneled its way. A fleshed-out
character would make great use of its capabilities.

    character fred "Fred"
    {
        noun "fred"
        in STARTLOCATION
        order_response
            {
            if verbroutine = &DoLook and object = player
                {
                "He says, \"Wow, you look lurvly.\""
                return true
                }
            return false
            }
    }

`order_response` should return false if a case hasn't been provided for,
at which point the character's `ignore_response` will be run (if there
isn't one, it'll give the default "*\[X\] ignores you*."

### Watch That Scope

[SpeakTo](parsing/speakto/) doesn't check that any object you have the
character interact with is in scope, so you'll have to code for that
yourself.

    character fred "Fred"
    {
        noun "fred"
        in STARTLOCATION
        order_response
            {
            if verbroutine = &DoGet and object
                {
                if not FindObject(object, parent(self)) ! assuming the character won't be in any vehicles or containers
                     "Fred can't see that."
                            else
                                 {
                                 if not Acquire(self,object)
                                       "Fred is carrying too much to take that."
                                 else
                                       print "Fred picks up "; Art(object); "."
                                 }
                            return true
                            }
            return false
            }
    }

### Super Sidekick

In a game with lots of complicated character commands, you may want to
point `order_response` to a routine just for readability.

    character fred "Fred"
    {
        noun "fred"
        in STARTLOCATION
        order_response
            {
                if not FredOrders
                 return false
                    else : return true
            }
    }

    routine FredOrders
    {
         ! insert a ton of well-coded cases here
    }
