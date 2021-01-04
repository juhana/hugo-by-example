---
title: Hints
permalink: /tips/hints/
categories: 
  - Tips
---

See also: [NewMenu.h](/contributions/newmenu/)

Kent Tessman's game Guilty Bastards has a great adaptive hint system
(more hints are added as you progress further in the game). This page
contains the code from that game, only *slightly* modified.

If you look at it, you'll see that the heart of it is a
Menu-calling routine that organizes groups of hints
by category.

## The code

    !----------------------------------------------------------------------------
    ! HINT SYSTEM:
    !----------------------------------------------------------------------------

    routine DoHint          ! i.e., in response to "hint" or "hints"
    {
        Help_Hints

        window 0
        cls
        PrintStatusline
        DescribePlace(location)
    }

    #ifset INCLUDE_HINTS

    array hint_categories[MAX_MENUITEMS]

    routine Help_Hints
    {
        local i, count, category, old_category
        local topic, old_topic

        MENU_TEXTCOLOR = DEF_FOREGROUND
        MENU_BGCOLOR = DEF_BACKGROUND
        MENU_SELECTCOLOR = DEF_SL_FOREGROUND
        MENU_SELECTBGCOLOR = DEF_SL_BACKGROUND

        ! Since we're corrupting the graphics window
        last_drawn_picture = 0

    :PickHintCategory
        ! First, create a list of hint categories:
        count = 0
        for category in hint_category
        {
            if category.hints_available
            {
                menuitem[++count] = category.name
                hint_categories[count] = category
            }
        }

        if count = 0
        {
            CenterTitle("HINTS")
            "\n[No hints available.  Press any key...]";
            pause
            return
        }

        menuitem[0] = "HINTS"
        category = Menu(count, 0, old_category)
        old_category = category
        if category = 0:  return

        ! Convert category from a menu selection number to a
        ! hint_category class:
        category = hint_categories[category]

    :PickHintTopic
        ! For a selected category, create a list of subcategories:

        ! the original code
    !\  for (topic=1; category.(hint1-1+topic)~=""; topic++)
        {
            menuitem[topic] = category.(hint1-1+topic)
            hint_categories[topic] = category.(hint1-1+topic) #2
        } \!

        ! the new code
        ! new loop so you can drop hints from the menu when the player is
        ! past that part
        ! (To clear a hint:  "hotel_hints.hint4 = 0" )
        local new
        for (topic=1 ; topic <= 10 ; topic++)
            {
            if category.(hint1-1+topic)~=""
                {
                menuitem[++new] = category.(hint1-1+topic)
                hint_categories[new] = category.(hint1-1+topic) #2
                }
            }
        menuitem[0] = category.name
        ! let's clear out the rest of the menu
        for ( new = new + 1 ; new <= 10 ; new++ )
            {
            menuitem[new] = ""
            }

        ! Get the desired topic:
        topic = Menu(topic-1, 0, old_topic)
        new = 0
        old_topic = topic
        if topic = 0
            jump PickHintCategory

        ! If we get here, then we've successfully selected a topic
        ! and can start printing the actual hints:
        CenterTitle(menuitem[topic])

        ! Change topic from a menu selection number to a
        ! hint_topic class:
        topic = hint_categories[topic]

        i = 0
    :PrintHints
        for (; i<=topic.hints_revealed; i++)
        {
            print ""
            run topic.(hint1+i)
        }

        if &topic.(hint1+i) = 0         ! i.e., no more topics
        {
            "\n[No more hints.  Press any key...]";
            pause
            jump PickHintTopic
        }
        else
        {
            "[Press 'H' for another hint, or 'Q' to quit]";
    :GetHintKey
            pause
            if word[0] = 'Q', 'q', ESCAPE_KEY
                jump PickHintTopic
            if word[0] = 'H', 'h'
            {
                topic.hints_revealed++
                print newline
                jump PrintHints
            }
            jump GetHintKey
        }
    }

    property hint1 alias n_to
    property hint2 alias ne_to
    property hint3 alias e_to
    property hint4 alias se_to
    property hint5 alias s_to
    property hint6 alias sw_to
    property hint7 alias w_to
    property hint8 alias nw_to
    property hint9 alias u_to
    property hint10 alias d_to

    property hints_available alias in_to
    property hints_revealed alias out_to

    ! hint_category objects must be explicitly placed "in hint_category".  They
    ! should contain two values for each hint1, hint2, etc.:  a label/question
    ! and the name of the hint_topic object.  hint_topic objects should be
    ! comprised of property routines for hint1, hint2, etc., giving successive
    ! hints on the topic.

    class hint_category
    {
        hints_available true
    }

    class hint_topic
    {
        hints_revealed 0
    }

## Hint Examples

    !---------------
    ! STUDIO HINTS:
    !---------------

    hint_category studio_hints "Rocket Pictures Studios"
    {
        in hint_category
        hints_available
        {
            if studiogate is visited
                return true
            else
                return false
        }
        hint1 "How do I get on the studio lot?", studiopass_hints
        hint2 "How do I open the soundstage door?", soundstage_hints
        hint3 "Who is the mysterious figure?", figure_hints
    }

    hint_topic studiopass_hints
    {
        hint1
        {
            "Movie studio security is on par with Area 51.  To get on
            the lot, you'll need a pass."
        }
        hint2
        {
            "There's a studio pass in the envelope that was slipped
            under the door of your hotel room."
        }
        hint3
        {
            "Drive to the studio lot.  Make sure you've got the pass
            handy.  Get out of the car and go north."
        }
    }

Hint categories only show up if the property `hints_available` returns
true. This way, you can avoid listing hints for areas the player hasn't
seen yet.

## The Slight Modification

The code on this page has been modified so that you can also remove
hints from a category once a player has passed a certain puzzle. In the
above example, if the player has made it on to the studio lot, we could
add the following to our code at some point:

    studio_hints.hint1 = 0

That option would then be skipped in the listing. Theren't aren't any
checks right now to make sure that an available category has available
hints, so you'll have to code for that yourself if your game has
categories is full of hints that will be removed.
