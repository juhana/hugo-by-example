---
title: NewMenu
permalink: /contributions/newmenu/
categories: 
  - Library Contributions
---

`NewMenu` is the b\*\*\*\*\*\*d stepchild of Menu and
the [Guilty Bastards hint system](/tips/hints/). It aims to make
game menus quicker and easier to set-up, and hopefully, they'll look
nice, too! Download it
[here](http://roody.gerynarsabode.org/hbe/newmenu.zip).

# Why NewMenu?

The [Hugo Library's](/library/) Menu
routine is a fine thing. It allows menus-within-menus and if you borrow
code from Guilty Bastards, you can have a fairly kickin' hint system.
Still, I, Roody Yogurt, wasn't completely happy with it. I found the
routine-based nature of its menu files a bit confusing- especially since
the hint system was object-based. On top of that, Hugo menus weren't
showing up on cheapglk interpreters like ifMUD's Floyd, as all menu
choices are written in the status window, a window that Floyd ignores
altogether. Lastly, I thought menu text was a bit ugly in transcripts
and could use a little *notation*.

To fix these things, `NewMenu` attempts to do the following:

1.  Turn all menu pages into configurable objects.
2.  Keep menu options in the status window so they are not printed to
    the transcript.
3.  Strengthen the relation between regular menus and hint menus.
4.  In glk menus, asterisk placement is changed, and in "cheapglk mode",
    the menu is printed out in the main window.
5.  Make Menus-within-menus more intuitive.
6.  Under regular and glk interpreters, hidden text is printed that
    should only show up in transcripts, making them look nicer.
7.  Add a "CoolPause" routine for prettier pauses.
8.  Contains an optional default menu with information about Hugo and IF
    that can standalone or coexist with game-specific pages.
9.  Has a routine called `ShowPage` for pulling up a menu page straight
    from the game, so a **&gt;COMMANDS** command can show a "special
    commands" page (while the same thing might be accessible from the
    menu itself).

# The Set-Up

To use NewMenu:

1.  \#include "newmenu.h" after "hugolib.h". If
    you want "cheap" support, \#set `CHEAP` before
    including "newmenu.h".
2.  If you'd like to use the default menu, `#set USE_DEFAULT_MENU`
    before "newmenu.h" is included.

# Creating Your Menu

## menu objects

`menu_category` class objects are the pages that hold
the menu options.

    ! MENU CATEGORIES
    menu_category main_menu "TITLE OF YOUR MAIN MENU"
    {
        title_gap 0   ! true value if there is an extra line
                          !  between menu title and "[N]ext key"
        options_gap 1 ! number of lines between "[N]ext key" and menu options
    }

1.  Your game should have one menu_category called `main_menu` that the
    `MakeMenu` routine will default to (unless it is used with another
    menu_category object.
2.  The name ("TITLE OF YOUR MAIN MENU") is the text that will show at
    the top of the screen.
3.  The gap properties just exist to allow modification of spacing at
    the top of the page.

## option objects

These are the choices that will populate the message.

    ! OPTION OBJECTS
    option contact_choice "Contact"
    {
        in main_menu    ! which menu it is
        option_available {
                if author is not unfriendly
                    return true
                else
                    return false
                }

        menu_text   {
                ""
                "_ Feel free to send me your thoughts and suggestions at
                             roody.yogurt@gmail.com! What an amazing discourse we will
                             have!\n"
                CoolPause(1)
                }
    }

1.  The name ("Contact") is both how the option will show in the menu
    and also the title of the page when it has been selected.
2.  `option_available` determines when the option will show up in the
    menu, depending on whether it returns true or not.
3.  `in main_menu` specifies which menu_category the option is in.
4.  `menu_text` is the text that shows up when someone chooses this
    option.
5.  To lead to another menu, we can do this:

<!-- -->

    option option_choice "CHOICE LEADING TO SUBMENU"
    {
        in main_menu
        menu_link    <submenu menu_category object>
    }


## hints!

So yeah, this thing also supports hints. Just make a hint-page
menu_category object, and fill it with hint_options like this:

    hint_option studiopass_hints "How do I get on the studio lot?"
    {
        in hint_menu
        hints_available
            {
            if studio_lot is visited
                return true
            else
                return false
            }
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

# Calling Your Menu

Now, to see your menu, make a routine that calls `MakeMenu`.

    routine DoAbout
    {
        MakeMenu ! automatically opens the main_menu object
    }

    routine DoHint
    {
        MakeMenu(hint_menu) ! goes straight to the hint menu
    }
