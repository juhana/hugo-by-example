---
title: Spellsys
permalink: /contributions/spellsys/
categories: 
  - Library Contributions
---

`Spellsys` is a neat Enchanter-spell library extension by Cardinal
Teulbachs distributed in the form of an incomplete game. It has code for
the spells gnusto, frotz, blorple, girgol, and logrig, but it presumably
could be expanded to cover many other\* of the Enchanter and Zork
series' spells. In its original state, it won't compile under Hugo 3.1.

-   For a list of all of the spells from the Enchanter and Zork series,
    go to [here](http://quendor.robinlionheart.com/spells)

## Modifications

The release notes disallow the distribution of a modified version of the
file, so this page will explain all of the steps necessary to get it
going.

### turn off precompiled headers

It's easiest to just comment that, out. If you *do* want some practice
at compiling with a precompiled library, be sure to compile with the
flags `#set USE_PLURAL_OBJECTS` and `#set USE_ATTACHABLES`.

### grammar

Change `#include "grammar.g"` to `#include "verblib.g"`. Before that,
add the following:

    verb "girgol","logrig"
        *                   DoSpell

### updating you

The player character object has to be changed to match the current
library. Change the `character` class to `player_character`. Change the
name from "yourself" to "you". Also, delete the `nouns` and `is plural`
lines.

### event definition

On line 464, change `event sky_change` to `event in meadow`.

### an improvement

After line 1014 ( "you don't have so-and-so spell memorized"), insert
this before the `break` line: `AssignPronoun(obj)`

This'll allow players to just type **&gt;MEMORIZE IT** right away.
That's all of them. Have fun!
