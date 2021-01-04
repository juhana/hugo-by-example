---
title: Dictionary Words
permalink: /definitions/dictionary-words/
categories: 
  - Definitions
---

"Dictionary words" are single-word [strings](strings/) within
your code. Even if they are not a [noun](properties/noun/) or
[adjective](properties/adjective/) property, their mere existence will
make them recognized by the game's parser, giving *"Better start with a verb."*
or *"That doesn't make any sense."* errors instead of 
*"You don't need to use the word '&lt;unrecognized word&gt;'."* 
when referred to by the player.

### Faking game knowledge with the dictionary table

Like we can do with the [known](attributes/known/) attribute, we can make
our game seem smarter by adding dictionary words. If your game stars
some French guy, sneak `"france"` into your code somewhere so the player
never gets a *"You don't need to use the word 'france'."* response.
