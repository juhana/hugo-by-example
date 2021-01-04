---
title: Quick Shipboard Directions
permalink: /tips/quick-shipboard-directions/
categories: 
  - Tips
---

Say you're making a game that has a boat/ship/spaceship in it, and you
want to quickly add the ability for the PC (Player Character) to use
shipboard directions (Fore/Aft/Port/Starboard), instead of creating new
properties for the directions, and the associated verbs and verb
routines you can use the `synonym` command to make the directions
synonyms for the built-in direction commands

    ! ... some code

    synonym "fore" for "north"
    synonym "aft" for "south"
    synonym "port" for "west"
    synonym "starboard" for "east"

    ! ... some more code

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

        e_to starboardDeck
        w_to portDeck
        s_to galley
    }

With this code snippet (and the rest of the rooms defined) the player
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

But, because these are synonyms, the player can still use
`north/south/east/west` to move about. If you don't want to have this
happen, go take a look at [Tedious Shipboard Directions](/tips/tedious-shipboard-directions/).
