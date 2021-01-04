---
title: Tedious Shipboard Directions
permalink: /tips/tedious-shipboard-directions/
categories: 
  - Tips
---

Say you're making a game that has a boat/ship/spaceship in it, and you
want to tediously add the ability for the PC (Player Character) to use
shipboard directions (Fore/Aft/Port/Starboard). We will create new
properties and objects for the directions (so "GO AFT" works), and we
will add our directions to the verb grammar.

    ! Add this to your verb grammar (plus, any abbreviations if you can think of any)
    verb "aft", "fore", "port", "starboard"
        *                        DoGo

    ! Then add these properties
    property aft_to
    property fore_to
    property starboard_to
    property port_to


    ! Then add these objects to your code
    direction aft_obj "aft"
    {
        in direction
        nouns "aft"
        dir_to aft_to
        dir_from fore_obj
    }

    direction fore_obj "fore"
    {
        in direction
        nouns "fore"
        dir_to fore_to
        dir_from aft_obj
    }
    direction port_obj "port"
    {
        in direction
        nouns "port"
        dir_to port_to
        dir_from starboard_obj
    }

    direction starboard_obj "starboard"
    {
        in direction
        nouns "starboard"
        dir_to starboard_to
        dir_from port_obj

    ! Your room code will look like this:
    room bridge "Ship's bridge"
    {
        long_desc
        {
            "This is the bridge of the USS Guppy, the fastest and smallest
            scoutship in the whole fleet. To the port and starboard are
            exits to the observation decks. Aft leads you to the galley.
            That is, if a small fridge and microwave can really be called
            a galley."
        }

        starboard_to starboardDeck
        port_to portDeck
        aft_to galley
    }

    }

With this epic code block (and the rest of the rooms defined) the player
can interact in the following way:

>**Ship's bridge**  
>This is the bridge of the USS Guppy, the fastest and smallest scout ship
>in the whole fleet. To the port and starboard are exits to the
>observation decks. Aft leads you to the galley. That is, if a small
>fridge and a microwave can really be called a galley.  
>&gt;port
>
>**Port Observation Deck**  
>The stars are very pretty from this side of the scout ship.  
>&gt;starboard
>
>**Ship's bridge**  
>&gt;aft
>
>**Galley**  
>This is the "galley" of the ship.  
>&gt;

REMINDER - Players will hate you for not mentioning exits in room
descriptions.

So yeah, that's the longer way to do it. If command mimesis is not the
most important thing in your game, go take a look at
[Quick Shipboard Directions](Quick_Shipboard_Directions).
