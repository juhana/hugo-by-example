---
title: react_before
permalink: /properties/react_before/
categories: 
  - Properties
---

**react_before** is a [property](/properties/) available for use
by an [object](/globals/object/), and is defined by the
[standard library](/library/).

## react_before

`react_before` is used "to allow reaction by an object that is not
directly involved in that action."

This has several different uses. The scenario imagined in the
joltcountry.com forums has an NPC keeping the player from going a
certain direction. This could be done by playing with player.before or
the location.before, but the poster wanted to attach the check to the
NPC so the game's world model matched how he imagined it.

    character jerk "Jerk"
    {
        noun "jerk"
        react_before
            {
            if actor = player and verbroutine = &DoGo and object = e_obj
                {
                "Jerk stops you! Whaddajerk!"
                return true
                }
            else
            return false
            }
        in STARTLOCATION
    }

The code would have looked something like that. Well, it would be
slightly different since the poster only wanted the NPC to warn the
player once and then let him go on his merry way. In this instance, if
the player did something that made the NPC leave, the react_before
condition would go with it and the player could freely go east, and hey,
that happens all of the time in IF, too.

Another way that `react_before` can be used is to successfully trigger
something where it normally would be skipped. Say you have an object
that makes noise, and you want to override the default "listen" response
in any location it is in. A verb such as "listen," used without an
object, only checks player.before and location.before (since object and
xobject are not used). `react_before` can add another check.

    object dogs "dog"
    {
        noun "dogs"
        is plural
        react_before {
            if verbroutine = &DoListen
                {
                "You hear dogs barking!"
                }
            else
            return false
            }
        in STARTLOCATION
    }

Things to be aware of:

That will NOT override the "listen" response for a location that has a
location.before DoListen entry (since location.before is called before
react_before). Also, react_before is not checked for items that are
being held by the player. Lastly, you'll notice that when you use
react_before, you have to specify the verbroutine as shown (and actor
or player or location as applicable) and return false for all cases that
don't fit.
