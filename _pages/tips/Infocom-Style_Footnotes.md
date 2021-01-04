---
title: Infocom-style footnotes
permalink: /tips/infocom-footnotes/
categories: 
  - Tips
---

Infocom's *Hitchhiker's Guide to the Galaxy* had a footnote feature that
many fans loved. The player is told about the existence of a, say,
*Footnote 11.* He types `>FOOTNOTE 11` and is rewarded with a sly
extraneous piece of information or meta joke. This has been used in
several games since then. Kent Tessman put a footnote system in his game
Guilty Bastards, so we conveniently have some tried-and-true code here
at our disposal (he went on to use code like this in his later game
Future Boy!).


*See also: [Footnote.h](Footnotes_(Library_Contribution)) (A
footnote-enabling library contribution)*


## The Code

### Grammar

Put this in your grammar:

    ! As you can see, Kent created a INCLUDE_FOOTNOTES flag for easily compiling
    ! footnote-enabled and disabled versions. This version would require you to
    ! "#set INCLUDE_FOOTNOTES before grammar is included. Otherwise, if you always
    ! want to compile with footnotes, you could comment the "#ifset" and "#endif"
    ! lines out

    #ifset INCLUDE_FOOTNOTES
    xverb "footnote", "note"
        *                                               DoFootnote
        * number                                        DoFootnote

    xverb "help"
        * "footnotes"                   DoFootnoteMode

    xverb "footnotes", "notes"
        *                       DoFootnoteMode
        * "always"                  DoFootnoteMode
        * "on"/"normal"                 DoFootnoteMode
        * "off"/"never"                 DoFootnoteMode
    #endif

### The Rest

    !\---------------------------------------------------------------------------

        GBNOTE.HUG
        Footnoting routines for Guilty Bastards by Kent Tessman (c) 1998

    ---------------------------------------------------------------------------\!

    constant MAXFOOTNOTES 30
    array footnote_printed[MAXFOOTNOTES]
    global footnote_mode = 1

    global changing_footnote_counter    ! for footnote 1

    routine PrintFootnote(n)
    {
        if footnote_mode = 0    ! if footnote-printing is off
            return

        if not footnote_printed[n-1] or footnote_mode = 2
            print "\n\I(Footnote "; number n; ")\i"
        footnote_printed[n-1] = true
    }

    routine DoFootnoteMode
    {
        if word[2] = "on", "normal"
        {
            "\I(Normal footnote printing.)\i"
            footnote_mode = 1
        }
        elseif word[2] = "off", "never"
        {
            "\I(Footnote printing off.)\i"
            footnote_mode = 0
        }
        elseif word[2] = "always"
        {
            "\I(Footnote printing always enabled.)\i"
            footnote_mode = 2
        }
        else
            "Try \"footnote (number)\" to read a particular footnote.  \
            Normally the indication of a footnote is printed only once;
            to make sure it is always printed, use \"footnotes always\".
            Use \"footnotes never\" to turn footnote printing off or
            \"footnotes normal\" to restore the default mode."
    }

    routine DoFootnote
    {
        if object <= 0
        {
            "Try \"footnote (number)\"."
            return
        }

        select object
        case 1
        {
            "Milt Walker, the head of Rocket Pictures, is one of
            those people you've met in passing (since you don't
            exactly run in the same social circles) and under
            somewhat shady circumstances.  It was a couple years
            ago and involved Milt's son and a boatload of South
            American marijuana.  Grass, he kept calling it.  You
            remember finding it vaguely funny sitting across a table
            from this austere-looking studio head in a seedy Los
            Angeles bar while he speculated in a low voice about
            how he was going to \"get rid of that much grass.\"  \
            How he did get his son out of that jam and what part you
            played in the whole imbroglio you swore never to reveal,
            not even here."

            select changing_footnote_counter
            case 0
                PrintFootnote(2)
            case 1
                "\n\I(The footnote doesn't say anything different
                this time around.)\i"
            case 2
                "\n\I(The footnotes always say the same things.)\i"
            case 3
                "\n\I(Always.)\i"
            case 4
                "\n\I(Really.)\i"
            case else
                ! So that it doesn't wrap around(!)
                changing_footnote_counter = 10

            ++changing_footnote_counter
        }
        case 2
            "Yes, it's true:  the author heisted the idea for these
            footnotes from the Infocom game \"The Hitchhiker's Guide to
            the Galaxy\".  But they are a pretty nifty idea."
        case 3
            "In order that you not spend the entire game stuck in
            traffic, we'll assume that if you name the place you want
            to get to that you're capable of getting there.  The real
            Los Angeles freeways are not nearly so forgiving."

    !   . . .
    !
    !   Okay, you get the idea.  Let's skip to the end.
    !
    !   . . .

        case else
        {
            if object > 200
            {
                "Do you really think the author took the time to
                brew up, like, ";
                NumberWord(object)
                " footnotes?"
            }
            else
                print "There is no footnote "; number object; "."
        }
    }
