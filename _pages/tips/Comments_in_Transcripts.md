---
title: Comments in Transcripts
permalink: /tips/comments-in-transcripts/
categories: 
  - Tips
---

When sending out your game to your beta-testers (you *do*
[beta](/betatesting/) test your games, right?), it's a good idea for
them to use the **[transcript](/definitions/transcript/)** to keep track of
their play so you can see what issues they run into. Unfortunately, the
standard Hugo library does not include a way for a player to put a
comment in the transcript itself. But thanks to Bert Byfield, there's a
remedy for that.

First, near the top of the code, you need to add a global
[variable](/basics/variables/) to keep track of whether the transcript
is on or off.

        global transcript_is_on = false    ! starts out as false, because the transcript isn't on, yet

Then, elsewhere in your code, you'll need to replace the `DoScriptOnOff`
[routine](/routines/) with the following code:

    replace DoScriptOnOff
    {
        if word[2] = "on" or words = 1
        {
            if (transcript_is_on) or (not scripton)
                VMessage(&DoScriptOnOff, 1) ! "Unable to begin..."
            else
            {
                transcript_is_on = true
                VMessage(&DoScriptOnOff, 2) ! "Transcription on."
            }
        }
        elseif word[2] = "off"
        {
            if (not transcript_is_on) or (not scriptoff)
                VMessage(&DoScriptOnOff, 3) ! "Unable to end..."
            else
            {
                transcript_is_on = false
                VMessage(&DoScriptOnOff, 4) ! "Transcription off."
            }
        }
    }

    replace NewParseError(errornumber, obj)
    {
        string(_temp_string, parse$, 1) !get 1st byte of input
        if (_temp_string[0] = '*')
        {
            if (transcript_is_on)
                VMessage(&DoScriptOnOff, 5) ! Comment recorded!
            else
                VMessage(&DoScriptOnOff, 6) ! Comment not recorded!
            return true
        }
    }

    replace NewVMessages(r, num, a, b)
    {
        select r
        case &DoScriptOnOff
        {
            select num
            case 1
            {
                if (transcript_is_on)
                    print "Transcription is already on."
                else
                    print "Unable to begin transcription."
            }
            case 2:  print "Transcription on."
            case 3
            {
                if (not transcript_is_on)
                    print "Transcription is not currently on."
                else
                    print "Unable to end transcription."
            }
            case 4:  print "Transcription off."
            case 5: print "Comment recorded!"
            case 6: print "Comment not recorded!"
            return true
        }
        return false !So all other VMessages work as-is.
    }
