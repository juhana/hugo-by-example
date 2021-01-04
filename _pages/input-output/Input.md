---
title: Input
permalink: /input-output/input/
categories: 
  - Input-Output
---

`input` is a built-in command that calls a prompt where the player can
enter text, as opposed to just waiting for the next prompt initiated by
the [game loop](game_loop). What the player enters is not
processed by [grammar](grammar) like a normal command, but
all understood words are still sent to the [word
array](word_array) (and a quoted string is saved as
[parse$](parse$)). This way, the author can check for
specific entries on a word-by-word basis.

When called by itself, the player's input has no textual
[prompt](prompt) ("&gt;"). Because of this, `input` is often
called indirectly by something like [GetInput](GetInput)
which makes printing a prompt more convenient.
