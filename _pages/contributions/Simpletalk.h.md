---
title: Simpletalk.h
permalink: /contributions/simpletalk.h/
categories: 
  - Library Contributions
---

 `Simpletalk.h` is a modified version of Robb Sherwin's
port of Adam Cadre's Inform 6 Phototalk extension. Among other things,
it has been made into the format of a library contribution for easy
inclusion. You can download it
[here](http://roody.gerynarsabode.org/simpletalk.zip)

### Special notes

Usage is explained in the comments in simpletalk.h, but you can also
take a look at the included sample "game".

### The extension itself

    !\-----------------------------------------------------------------------
    Simpletalk.h version 1.5, based on code written by Robb Sherwin, updated and
    turned into an includable library by Jon Blask.

    This is a simplified version of Sherwin's Phototalk port. This one drops support
    for contextualized multiple-choice menus (which it seems the original Inform 6 version had) and is just a
    bare-bones list-all-available-quips system.

    Usage notes:

    Of course, #include this from your main file.

    Also, add the following:

    !----------------------------------------------------------------------------
    ! Set up the quip declarations
    array qflag[100]            ! where 100 = total number of quips in the game
    array quips[5] = 20, 20, 20, 20, 20     ! 5 = number of characters, the 20s are how many quips are alloted to each

    Change that as needed to fit your code.

    Give characters that you can talk to in the game the property "charnumber" and a value starting at
    1 (first character gets 1, 2nd character is 2, and so on)

    Also, add the following routines:

    routine SayQ (char, line)
    {
        select(char)
        case 1
            {
            select(line)
            case 0: {">This is the first thing you can say to char one."}
            case 1: {">This is the second thing you can say to char one."}
            }
        case 2
            {
            select(line)
            case 0: {">This is the first thing you can say to char two."}
            case 1: {">This is the second thing you can say to char two."}
            }
    }

    routine Respond (char, line)
    {
        select(char)
        case 1
            {
            select(line)
            case 0: "This is the first response from character number one."
            case 1: "This is the second response from character number one."
            }
         case 2
            {
            select(line)
            case 0: "This is the first response from character number two."
            case 1: "This is the second response from character number two."
            }
    ! Let's turn off whichever quip we selected
        SetQuip(char,line,0)
    }

        And fill them to suit your game.

        Make another routine:

    routine SetUpQuips
    {
        SetQuip(1,0,1)
        SetQuip(1,1,1)
        SetQuip(2,0,1)
        SetQuip(2,1,1)
    }

        And add SetUpQuips to the init routine in your game. This sets up all of the
        quips available at the start of the game. The first number in SetQuip is the
        character's charnumber, the second is the line that's now available through
        SayQ, and the third should just be 1 (turning the question on).

        Call SetQuip(#,#,1) to turn on other quips as the game progresses.
    -----------------------------------------------------------------------\!

    #ifclear _SIMPLETALK_H
    #set _SIMPLETALK_H

    #ifset VERSIONS
    #message "Simpletalk.h version 1.5"
    #endif

    replace DoTalk
    {
        if word[2] = "to" and not xobject
        {
            if object is unfriendly
            {
                if not object.ignore_response
                    Message(&Speakto, 4)    ! "X ignores you."
                speaking = 0
            }
            elseif object = player
            {
                Message(&Speakto, 1)    ! "Stop talking to yourself."
                return false
            }
            elseif object is not living
            {
            "You can't talk to that!"
            return false
            }
            else
            {
                speaking = object
                DoPhototalk
    #ifclear NO_SCRIPTS
                SkipScript(object)
    #endif
            }
            return true
        }

        print "Just talking to "; art(object); " will suffice."
        return false
    }

    routine DoPhototalk
    {
        local x, y, z, ok = 0
        local selected

    ! Count up all the lines by previous characters.
        if object.charnumber
            {
            for (x=0; x < object.charnumber; x++)
                {
                y = (y + quips[x])
                }
            }

    ! Check and make sure you have something to say.
        for (x=y; x<(y+quips[object.charnumber]); x++)
            {
            if (QuipOn(object.charnumber,x-y))
                {
                ok++
                break
                }
            }

    ! Write contents to the screen
        if ok
            {
            "Please select one:\n"

    ! List the player's choices
            for (x=y;  x < (y+(quips[object.charnumber])); x++)
                {
                if (QuipOn(object.charnumber,x-y))
                    {
                    z++
                    print "("; number z; ")";
                    SayQ(object.charnumber,x-y)
                    }
                }

    ! Get the choice
    !       "\n"
            ""
            selected = GetDial(z)
            if (selected ~= 0)
                {
                ok=0
                ""
                    for (x=y;  x < (y+quips[object.charnumber]); x++)
                    {
                    if (QuipOn(object.charnumber,x-y))
                        {
                        ok++
                        if (ok = selected)
                            {
                            Respond(object.charnumber,x-y)
                            }
                        }
                    }
                }
            return(true);
        }

        PhotoMessage(&DoPhotoTalk,1) ! "You really have nothing to say right now."
    }


    routine GetDial(max)
    {
        word[1] = ""
        local temp,prompttext
        prompttext = PhotoMessage(&GetDial,1)
        ! "Select a choice or 0 to keep quiet. >> "
        GetInput( prompttext )

    :TryAgain
    ! checking for it should add "0" to dictionary table no matter what
        if word[1] = "0" or words = 0
            jump ReturnTemp
    #ifset USE_PLURAL_OBJECTS
        if word[1]
            temp = StringToNumber(word[1])
        else
            temp = StringToNumber(parse$)
    #else
        temp = StringToNumber(parse$)
    #endif
        if temp ~= 0 and temp <= max
            jump ReturnTemp
        GetInput( prompttext )
        temp = 0
       jump TryAgain

    :ReturnTemp

        if not temp
            {
            ""
            PhotoMessage(&GetDial,2) ! "Eeeagh! Stage fright! Abort!"
            }
        return temp
    }

    routine SetQuip (char, line, onoff)
    {
        local x n

        for (x=0; x<char; x++)
            {
                n=(n + quips[x])
            }

        n = (n + line)

        if (onoff = 1)
            {
             qflag[n] = 1 ! ((qflag[y]) | (z))
            }

        if (onoff = 0)
            {
            qflag[n] = 0 ! ((qflag[y]) & (~z))
            }
    }

    routine QuipOn (char, line)
    {
        local x n

        for (x=0; x<char; x++)
            {
             n = (n + quips[x])
            }
        n = n + line
        if (qflag[n] = 1)
            {
            return(1)
            }
        return(0)
    }

    replace DoAsk
    {
        return PrintConverseUsage
    }

    replace DoAskQuestion
    {
        return PrintConverseUsage
    }

    replace DoTell
    {
        return PrintConverseUsage
    }

    routine PrintConverseUsage
    {
        "Try \B>TALK TO CHARACTER\b instead."
        return false
    }

    routine PhotoMessage(r, num, a, b)
    {
        if NewPhotoMessages(r, num, a, b):  return

        select r
            case &DoPhotoTalk
                {
                select num
                    case 1: "You really have nothing to say right now."
                }
            case &GetDial
                {
                select num
                    case 1
                        return "Select a choice or 0 to keep quiet. >> "
    !\ If you want a custom prompt, make sure &GetDial case 1 is
        { return "prompt text" } , not just "prompt text"     \!
                    case 2
                        "Eeeagh! Stage fright! Abort!"
                }
    }

    !\ The NewPhotoMessages routine may be REPLACED and should return
    true if a replacement message exists for routine <r> \!

    routine NewPhotoMessages(r, num, a, b)
    {
        return false
    }

    #endif

### Ways To Improve

Author's Note: It didn't seem worthwhile to put too much work into this
(it is called *Simpletalk*, afterall), and I can see ways how one could
improve it. For instance, you could add some code so that the player
stays inside the conversation until he runs out of things to say or
explicitly leaves the conversation menu.
