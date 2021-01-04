---
title: Replace PrintStatusLine
permalink: /replacements/printstatusline/
categories: 
  - Replacements
---

This version of [PrintStatusLine](/input-output/printstatusline/) uses
"[text to](/strings/text-to/)" and string routines to always place text
in the right place in the upper right corner of the screen.

## The code

    !----------------------------------------------------------------------------
    ! PrintStatusline
    ! prints an appropriate statusline as specified by global STATUSTYPE

    replace PrintStatusline
    {
       if display.linelength < 60
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

    ! (The part we're changing)
    ! print to 65; ! is 65 characters good for every window size? No!

    ! Instead, let's begin by writing the entire 'SCORE / MOVES' to array
    ! _temp_string (_temp_string is an array declared by the library)

          text to _temp_string
          if STATUSTYPE = 1
             print number score; " / "; number counter;
          elseif STATUSTYPE = 2
             print HoursMinutes(counter);
          if FORMAT & DESCFORM_F:  print "_";
          text to 0
    ! Ok, we've closed off the string array

    ! Now, if the screen is wide enough, let's move to the end of the screen
    ! MINUS the length of the _temp_string array
          if display.statusline_height = 1
             print to (display.screenwidth - (StringLength(_temp_string)));
          else
          {
             locate 1, 2
             if FORMAT & DESCFORM_F:  print "_";
          }

     ! Now let's print it!
          if STATUSTYPE = 1,2
                         StringPrint(_temp_string)
       }
       color TEXTCOLOR, BGCOLOR
       Font(DEFAULT_FONT)
    }

## Should Have Stopped While I Was Ahead

Following is another version that is unfortunately very ugly. Maybe I
will be able to make it prettier at some point. Things it does:

1.  Uses [DESCFORM_F](/guts/descform_f/) to provide consistent
    spacing on both left and right sides.
2.  Clears the window if the new status line height is smaller than the
    old.
3.  Adds a new value to [STATUSTYPE](/globals/statustype/). If set to
    3, `PrintStatusLine` prints the score/turn counter the Infocom way
    ("Score: Moves: ").

<!-- -->

    replace PrintStatusline
    {
    local newstatusheight

    ! figure out how many lines we need
    newstatusheight = FindStatusHeight

    ! remove the windows if the status window height has changed
    if newstatusheight < display.statusline_height
        window 0

    display.statusline_height = newstatusheight

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

        if newstatusheight = 1 and STATUSTYPE
            {
                print to (display.screenwidth - (StringLength(_temp_string)));
                StringPrint(_temp_string)
            }
        elseif STATUSTYPE and newstatusheight = 2
            {
                locate 1, 2
                StringPrint(_temp_string)
            }
        }
    color TEXTCOLOR, BGCOLOR
    Font(DEFAULT_FONT)
    }

    routine FindStatusHeight
    {
    local a, b
    text to _temp_string
    if not location
        print "_";
    elseif not light_source
        print "In the dark";
    else
        {
            if FORMAT & DESCFORM_F:  print "_";
            print capital location.name;
            print "_";
        }
    text to 0
    a = StringLength(_temp_string)

    if STATUSTYPE = 1
        {
        text to _temp_string
        if (FORMAT & DESCFORM_F)
            print "_";
        print number score; " / "; number counter;
        if (FORMAT & DESCFORM_F)
            print "_";
        text to 0
        }
    elseif STATUSTYPE = 3
        {
        text to _temp_string
        if (FORMAT & DESCFORM_F) : print "_";
        print "Score: "; number score; "_ "; "Moves: "; number counter;
        if (FORMAT & DESCFORM_F) : print "_";
        text to 0
        b = StringLength(_temp_string)
        }
    elseif STATUSTYPE = 2
        {
        text to _temp_string
        if (FORMAT & DESCFORM_F) : print "_";
        print HoursMinutes(counter);
        if (FORMAT & DESCFORM_F) : print "_";
        text to 0
        }

    if (b + a + 4)<display.screenwidth ! let's force a 4 character gap between
        {                               ! the two fields
        return 1
        }
    elseif (b + a - 4 ) < display.screenwidth and STATUSTYPE = 3
        {
        text to _temp_string
        if (FORMAT & DESCFORM_F) : print "_";
        print "S: "; number score; "_ "; "M: "; number counter;
        if (FORMAT & DESCFORM_F) : print "_";
        text to 0
        return 1
        }
    else
        return 2
    }
