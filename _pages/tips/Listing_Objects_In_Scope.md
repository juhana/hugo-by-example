---
title: Listing Objects in Scope
permalink: /tips/listing-objects-in-scope/
categories: 
  - Betatesting
  - Tips
---

The following code allows you to type `>SCOPE` to see everything within
the player's scope in the current location or `>SCOPE ROOMS` to see
what's available (at the moment) in all rooms. This code has beta and
alphatesting in mind, when an author is starting to lose track of what
he or she has written for every room and what he or she still yet needs
to write.

## Usage Notes

The code starts at the player character object and works up from there,
so you'll want to make sure that all rooms and objects that you want to
keep track of are declared after the player object. Otherwise, you can
alter the code to fit your game.

Also, if you have separate source files with objects in them, you'll
want to include them AFTER the player character is declared. Conversely,
if you have objects that you don't want included (like topic objects in
some conversation systems), include them BEFORE the player character.

## The code

    ! Add to your verb grammar
    verb "scope"
        *                       DoScope
        * "rooms"                   DoScopeRooms

    ! Now the routines themselves

    routine DoScope
    {
            print "Total objects: "; number objects
        print "Highest object number: "; number (objects - 1)
        "Objects in scope:"
        local a
        for (a=player ; a< objects ; a=a+1)
            {
            if a.type ~= room
                {
                if FindObject(a,location)
                                  {
                                  print "_  ";
                      print a.name
                                  }
                }
            }
    }

    routine DoScopeRooms
    {
        local a, b
            print "Total objects: "; number objects
        print "Highest object number: "; number (objects - 1)
        a = player
        do
        {
            if a.type = room
                {
                print ""
                print "Room: "; a.name
                print "In scope:"
                for (b=you ; b< objects ; b=b+1)
                    {
                    if b.type ~= room
                        {
                        if FindObject(b,a)
                                                {
                            print "_  "; b.name
                                                }
                        }
                    }
                }
            a++
        }
        while a< objects
    }

## Fancify it

You could add code so it only runs when DEBUG or BETA is set, whatever!
Season to taste!
