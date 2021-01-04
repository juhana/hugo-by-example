---
title: noun
permalink: /properties/noun/
categories: 
  - Properties
---

`noun` and [adjective](/properties/adjective/) are two important
[object](/globals/object/) [properties](/properties/). Without
them, a player isn't able to refer to a game object at all, as they
specify what the parser is matching against in any given input.

    object ramp_object "ramp"
    {
       noun "ramp"
       article "the"
       in arena
    }

Things to keep in mind:

1.  As everything the player enters is understood as lowercase, nouns
    and adjectives should always be entered as lowercase letters (even
    for names of characters and such).
2.  When the player's command matches both one object's `noun` property
    and another object's `adjective` property (like, "EXAMINE GREEN" in
    a room with both a green bag and a golf green), the noun-object will
    be chosen.
3.  If two objects in scope have the same `noun`,
    [parse_rank](/properties/parse_rank/) values comes into effect.
4.  Only the first six characters of a `noun` and `adjective` are
    matched against.
