---
title: GetInput
permalink: /input-output/getinput/
categories: 
  - Input-Output
---

`GetInput` is a small [hugolib.h](/library/hugolib.h/)
[routine](/routines/) for printing a quick prompt and waiting
for an [input](/input-output/input/).

## The code

    !----------------------------------------------------------------------------
    ! GetInput
    ! receives input from the keyboard, parsing into the word[] array; unknown
    ! words--i.e. those that aren't in the dictionary--are equated to the null
    ! string ("")
    !
    ! GetInput(prompt)
    ! where the optional <prompt> represents a dictionary word, prints <prompt>
    ! before receiving input

    routine GetInput(p)
    {
        print p;
        input
    }
