---
title: Replace PreParse
permalink: /replacements/preparse/
categories: 
  - Replacements
---

As the [PreParse](parsing/preparse/) page shows, `PreParse` can be
used for a bunch of purposes.

## Redrawing the screen

This version of `PreParse` was written to accompany the more-elaborate
version of `PrintStatusLine` on the
[Replace PrintStatusLine](replacements/printstatusline/) page.

    replace PreParse
    {
        ! if the screen size has changed, we'll clear the screen,
        ! print the player's command, and redraw the status line before
        ! proceeding to interpret the command

        if display.needs_repaint
            {
            ! some text so transcripts aren't confusing when the player's
            ! input is listed twice
            "[Detected screen size change; starting turn over...]"
            cls
            print prompt;
            local i = 1, showfullstops
            while word[i] ~= ""
                {
                print word[i];
                if word[++i] ~= ""
                    print " ";
                elseif word[++i] ~= ""
                    {
                    showfullstops = true
                    print ". ";
                    }
                if word[i] = "" and showfullstops
                    {
                    print ".";
                    }
                }
            print ""
            display.needs_repaint = false
            PrintStatusLine
            }
    }
