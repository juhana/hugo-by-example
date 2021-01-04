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
by [its license](Future_Boy_Selected_Source_License). It
requires the inclusion of the Hugo Library's
[system.h](System.h) file.

Download it [here](http://roody.gerynarsabode.org/hbe/time.h)

## Why??

Maybe you want your game to seem like it takes place \*right now\* and
want to use some its routines that grab the current time and date for
you. Maybe you want your game to write dates to file so you can make fun
of the player when he comes back to it months later. This extension
makes these things easier!

## For instance, a game "jukebox"

[Here](http://roody.gerynarsabode.org/jukebox.zip) are some files that
use the time routines to improve upon the [Music
Engine](Music_Engine) from the [Tips](Tips)
category without being bothered by the passage of hours, days, and so
forth. Of course, it relies on [Hugor's](Hugor) handling of
music files, in which a minimized window is muted (and the music is not
paused), but it is likely that future official Hugo interpreters will
also work that way.

What will *you* do with it?
