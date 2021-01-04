---
title: replace
permalink: /guts/replace/
categories: 
  - Hugo Guts
---

`replace` is a very useful command that allows one to, um, *replace*
previously-defined routines and object classes. It is because of this
feature that the first step of writing a Hugo game is not throwing the
Hugo Library into a text editor and modifying it to your means. With
`replace` we never have to change anything *within* the files
themselves; everything can be handled externally. In the matter of
[constants](/basics/constants/), one defines them before the library
files are **\#include**'d. For routines and object classes, yeah, we use
`replace`.

The replacement of routines is covered on the
[routine](/routines/)
page, so we'll take a moment to go over the replacement of
[object classes](/basics/object_classes/): The main thing to keep in mind is
that this replacement *must* be declared before your game code has any
objects of this particular class.
So, let's pretend you have a game where every character is
[unfriendly](/attributes/), but you don't want to write "is
unfriendly" on every character because that is SO MUCH WORK. You could
do this:

    replace character
    {
        type character
        pronouns "he", "him", "his", "himself"
        capacity 50
        holding 0
        is living, transparent, static, unfriendly
    }

That time spent now will be much more time for drinking later!
