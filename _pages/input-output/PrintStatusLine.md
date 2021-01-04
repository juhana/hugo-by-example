---
title: PrintStatusLine
permalink: /input-output/printstatusline/
categories: 
  - Input-Output
  - Routines
---

`PrintStatusLine` is a [hugolib.h](hugolib.h)-defined
[routine](routine) that draws the status bar (the window
above the main window). It is called by [main](main).
Depending on the [STATUSTYPE](STATUSTYPE) value, besides the
room name, it'll show score and turns, time, or even nothing at all.

## The code

    !----------------------------------------------------------------------------
    ! PrintStatusline
    ! prints an appropriate statusline as specified by global STATUSTYPE

    routine PrintStatusline
    {
        if display.linelength < 80
            display.statusline_height = 2
        else
            display.statusline_height = 1

        Font(BOLD_OFF | ITALIC_OFF | UNDERLINE_OFF | PROP_OFF)
        window display.statusline_height
        {
            color SL_TEXTCOLOR, SL_BGCOLOR
            cls
            locate 1, 1
            if not location
                print "_";
            elseif not light_source
                print "In the dark";
            else
            {
                if FORMAT & DESCFORM_F:  print "_";
                print capital location.name;
            }

            if display.statusline_height = 1
                print to 65;
            else
            {
                locate 1, 2
                if FORMAT & DESCFORM_F:  print "_";
            }

            if STATUSTYPE = 1
                print number score; " / "; number counter;
            elseif STATUSTYPE = 2
                print HoursMinutes(counter);
        }
        color TEXTCOLOR, BGCOLOR
        Font(DEFAULT_FONT)
    }
