---
title: ChangeColorMenu
permalink: /routines/changecolormenu/
categories: 
  - Routines
---

I wanted the player to be able to set the foreground and background
color of a Hugo game inside the game itself. This is what I came up
with.

(The numbers for the colors correspond to the enumerated color values in
"COLOR CONSTANTS AND GLOBALS", in [hugolib.h](library/hugolib.h/).)

    routine ChangeColorMenu()
    {
    local tempInput

        "Pick a color for the game's text:"

        "0) Black 1) Blue 2) Green 3) Cyan 4) Red 5) Magenta 6) Brown 7) White\n
        8) Dark Gray 9) Light Blue 10) Light Green 11) Light Cyan 12) Light Red\n
        13) Light Magenta 14) Yellow 15) Bright White"
        ">";

        input

        if word[1]
        {
            tempInput = StringToNumber(word[1])
        }
        else
        {
            tempInput = StringToNumber(parse$)
        }

        TEXTCOLOR = tempInput


        "Pick a color for the game's background:"

        "0) Black 1) Blue 2) Green 3) Cyan 4) Red 5) Magenta 6) Brown 7) White\n
        8) Dark Gray 9) Light Blue 10) Light Green 11) Light Cyan 12) Light Red\n
        13) Light Magenta 14) Yellow 15) Bright White"
        ">";

        input

        if word[1]
        {
            tempInput = StringToNumber(word[1])
        }
        else
        {
            tempInput = StringToNumber(parse$)
        }

        BGCOLOR = tempInput

        color TEXTCOLOR, BGCOLOR
    }
