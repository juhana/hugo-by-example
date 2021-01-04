---
title: DarkWarning
permalink: /guts/darkwarning/
categories: 
  - Hugo Guts
---

*From [hugolib.h](library/hugolib.h/):*

>MovePlayer calls DarkWarning when there is no light source in the new
>location; replace it with a new DarkWarning routine for a more elaborate
>response, such as the possible demise of the player

Really, I think that says it best.

## The code

    routine DarkWarning
    {
        print CThe(player); " stumble"; MatchSubject(player); \
            " around in the dark."
    }
