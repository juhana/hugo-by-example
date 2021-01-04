---
title: Transcript
permalink: /definitions/transcript/
categories: 
  - Definitions
  - Betatesting
  - Input-Output
---

"Transcripts" are the term for text files that represent an IF
playthrough. While scripting is on, each command entered and all
resulting text is written to the specified text file. Among other
reasons, this can be a good way to find grammar or spelling mistakes in
game prose.

## Starting a transcript

A transcript is started by the command `scripton`. `DoScriptOnOff` has
this code:

    if not scripton
        VMessage(&DoScriptOnOff, 1)      ! "Unable to begin..."
    else
        VMessage(&DoScriptOnOff, 2)      ! "Transcription on."

In-game, this is called by **&gt;SCRIPT ON**.

## Ending a transcript

A transcript is stopped with `scriptoff`. `DoScriptOnOff` has this code:

    if not scriptoff
        VMessage(&DoScriptOnOff, 3)      ! "Unable to end..."
    else
        VMessage(&DoScriptOnOff, 4)      ! "Transcription off."

In-game, this is called by **&gt;SCRIPT OFF**.

## Other adventures in transcript-ing

The [Beta.h](/contributions/beta.h/) library extension modifies
`DoScriptOnOff` and [ParseError](/parsing/parseerror/) so that
betatesters can leave comments in their transcripts by prefacing notes
with an asterisk ("\*").
