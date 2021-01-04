---
title: Recordings
permalink: /definitions/recordings/
categories: 
  - Definitions
  - Basics
---

Recordings are similar to [transcripts](transcripts). Instead
of writing all text to a text file, only commands are saved. The main
purpose of recordings is so that authors can quickly get through
sections of games, as saved games won't work over multiple compiles.
Anything entered at the main prompt or [input](input) is
written to the file; individual keypresses during pauses and such are
not.

## Starting a recording

A recording is started by the command `recordon`. `DoRecordOnOff` has
this code:

            if not recordon
                VMessage(&DoRecordOnOff, 3)  ! "Unable to begin..."
            else
                VMessage(&DoRecordOnOff, 4)  ! "Recording on."

In-game, this is called by **&gt;RECORD ON**.

## Ending a recording

A recording is stopped with `recordoff`. `DoRecordOnOff` has this code:

            if not recordoff
                VMessage(&DoRecordOnOff, 5)  ! "Unable to end..."
            else
                VMessage(&DoRecordOnOff, 6)  ! "Recording off."

In-game, this is called by **&gt;RECORD OFF**.

## Playing a recording

The command for playing a recording is `playback`. `DoRecordOnOff` has
this code:

            if not playback
                VMessage(&DoRecordOnOff, 1)  ! "Unable to begin..."
            else
                VMessage(&DoRecordOnOff, 2)  ! "Playback beginning..."

In-game, this is called by **&gt;PLAYBACK**.
