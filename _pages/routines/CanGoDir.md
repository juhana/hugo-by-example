---
title: CanGoDir
permalink: /routines/cangodir/
categories: 
  - Routines
---

`CanGoDir` is an exit-checking routine. One would use it if he wants to
check if the player is heading in a successful direction and wants to
run some code or print something before the game executes
[DoGo](/verb-routines/dogo/).

In its current incarnation, it'll return true if the player heads in a
direction that returns a location or enters an open or unlocked door (or
even just something with a [door_to](/properties/door_to/) property).

It will not return true if the player is just getting out of a platform
(like a chair) or container, but you can modify it to fit your needs.

## The code

    routine CanGoDir
    {
        if object.type ~= direction and object is not enterable and object.type ~= door
            return false
        if object is openable ! in case the object is a door
            {
            if object is open or object is not locked
                return true
            else
                return false
            }
        else
            {
            local m
            if object.type = direction
                m = location.(object.dir_to)
            else
                m = object.door_to
            if m > 1    ! since a message always returns 1
                return true
            else
                return false
            }
    }

## Usage Example

    object banana "banana peel"
    {
        article "the"
        adjective "banana"
        noun "peel"
        in eastroom
        react_before
            {
            if verbroutine = &DoGo and CanGoDir and banana in location
                {
                "You head off in that direction but slip on the banana peel. Whoops!"
                return true
                }
            else
                return false
            }
    }

Now, our player will only slip if he or she was heading in a successful
direction! Slapstick!

## Final Notes

As is, it should work fine with doors that use the door class.
Otherwise, if you give [door_to](/properties/door_to/) properties to
other openable objects and only want them enterable when they are open,
you'll have to do something like this:

    object portal "portal"
    {
    noun "portal"
    door_to otherdimension
    before {
        object DoGo,DoEnter
            {
            if self is not open
                {
                "The portal is closed."
                return true
                }
            return false
            }
        }
        is openable
    }
