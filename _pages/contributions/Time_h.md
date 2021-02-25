---
title: Time.h
permalink: /contributions/time.h/
categories: 
  - Library Contributions
---

`Time.h` is an extension by Kent Tessman (based on Future Boy! source)
that collects several routines for dealing with the passage of time (in
terms of seconds, minutes, hours, days, and years). This
slightly-modified version (some properties have been aliased and some
routines have been added) follows the instructions benevolently dictated
by [its license](misc/future-boy-license/). It
requires the inclusion of the Hugo Library's
[system.h](library/system.h/) file.

Get it [here](https://github.com/hugoif/library-contributions/blob/main/time/time.hug).

## Why??

Maybe you want your game to seem like it takes place \*right now\* and
want to use some its routines that grab the current time and date for
you. Maybe you want your game to write dates to file so you can make fun
of the player when he comes back to it months later. This extension
makes these things easier!

## For instance, a game "jukebox"

[Here](https://github.com/hugoif/library-contributions/tree/main/time) are some files that
use the time routines to improve upon the [Music Engine](tips/music-engine/)
from the [Tips](categories/#tips)
category without being bothered by the passage of hours, days, and so
forth. Of course, it relies on [Hugor's](interpreters/hugor/) handling of
music files, in which a minimized window is muted (and the music is not
paused), but it is likely that future official Hugo interpreters will
also work that way.

What will *you* do with it?
