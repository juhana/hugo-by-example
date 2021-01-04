---
title: window
permalink: /input-output/window/
categories: 
  - Input-Output
---

There may come a time that you'd like to split your game window into
multiple sub-windows. Perhaps you'd like information that's always
visible to the player. Items such as a mini-map or an exit lister, or an
inventory list. 

## window command

The Hugo language includes the **window** command to make this possible.
When a window is defined, cursor positioning, line-wrapping, etc. are
limited to the size of the defined window.

Using the **window** command.

<table>
<thead>
<tr class="header">
<th><p>window Command Syntax</p></th>
<th><p>Description</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><code>window 0</code></p></td>
<td><p>Restores output to the full screen</p></td>
</tr>
<tr class="even">
<td><p><code>window </code><em><code>n</code></em><br />
<code>{ ... }</code></p></td>
<td><p>Creates a window of <em>n</em> lines at the top of full window. Each line is also the full length of the of the screen.<br />
(The statusline area is an example of this kind of window.)</p></td>
</tr>
<tr class="odd">
<td><p><code>window </code><em><code>l</code></em><code>, </code><em><code>t</code></em><code>, </code><em><code>r</code></em><code>, </code><em><code>b</code></em><br />
<code>{ ... }</code></p></td>
<td><p>Creates a window with the left-top corner at <em>l, t</em> and the right-bottom at <em>r, b</em> where these character coordinates on the full screen.</p></td>
</tr>
<tr class="even">
<td><p><code>window</code><br />
<code>{...}</code></p></td>
<td><p>Redraws the last window</p></td>
</tr>
</tbody>
</table>

The output to the defined window only lasts as long as the code that is
in between the { } characters. Outside the characters, the output
returns to the main window (which is defined to be below the bottom most
sub-window)

Sample: Single sub-window, on the upper portion of the game window

    window 5
    {
      window 5
      {
        "Info you want visible\n"
        "all the time\n"
        "or maybe even\n"
        "a graphic image\n"
        "You want to show."
    }

Because many interpreters are being run in a GUI (Windows/OS X), there's
a chance that the player will be changing the size of the game window as
play progresses. Because of this, it is a good idea not to hard-code the
width and/or height of the sub window(s). Use the built-in
[display](guts/display-object/) object to get the current window size.

    ! bad way, will not re-adjust itself when user resizes the game window.
    window 1, 1, 40, 15
    {
      "stuff you want to output goes here."
    }

    ! Right Way, because it takes the size of the game window into account
    ! create a window in the upper left quarter of the screen
    local l, t, r, b
    l = 1
    t = 1
    r = display.screenwidth / 2
    b = display.screenheight / 2

    window l, t, r, b
    {
      "Each time the main window is resized, the code here will
       automatically re-calculate the the size of this sub-window."
    }

## Using the window class

In the [hugo library](library/), there's a file that can
be included that makes it a little easier to use windows by defining a
window class (see [window.h](library/window.h/))

Below is sample code that divides the game window into 3 windows, an
extra description area in the upper left of the game screen, an
inventory list in the upper right portion of the screen, and the the
bottom half is the game text. The sample "game" is woefully under
implemented and is mainly used to show one way to define and use
windows.

    !::
    ! Window Sampler
    !
    !:: Flags
    !#set HUGOFIX             ! Compile with HugoFix Debugging Library commands available (type $? in game)
    !#set HDX                 ! Produce a Hugo Debuggable Executable (.hdx) file for use with debugger
    !#set PRECOMPILED_LIBRARY ! Use a precompiled header library (see manual)
    !#set VERBSTUBS           ! Include the grammar and routines from verbstubs.g and verbstubs.h, respectively
    !#set USE_PLURAL_OBJECTS  ! Use plural objects
    !#set USE_ATTACHABLES     ! Use attachable items
    !#set NO_AUX_MATH         ! No advanced math needed
    !#set NO_FONTS            ! Don't use font effects
    !#set NO_FUSES            ! Don't use fuses
    !#set NO_MENUS            ! Don't use menus
    !#set NO_RECORDING        ! Don't allow transcripts
    !#set NO_SCRIPTS          ! Don't use character scripts
    !#set NO_STRING_ARRAYS    ! Don't use string arrays
    !#set NO_VERBS            ! Don't use any standard verbs
    !#set NO_XVERBS           ! Don't use any standard "out-of-world" verbs


    !:: switches              ! example how one can add compiler switches to source
    !#switches -ls            ! print compilation stats to .LST file

    #ifset HUGOFIX
    #set DEBUG
    #endif
    #ifset HDX
    #switches -d              ! sets the debug compiler switch (producing Hugo Debuggable Executables) if the flag is set
                              ! note: will produce .hdx as .hex file under some versions (like the Windows compiler)
                              !       unless -d flag is set in actual compiler
    #endif

    !:: Constants and globals  (some constants must be set before hugolib is included)
    !constant AFTER_PERIOD " "     ! include one space after full stops (as opposed to two)
    constant INDENT_SIZE 0        ! no indentation in room descriptions and room content listings
    constant IFID "5E565EFE-75BF-45E8-BAAF-61255CF6008A"
    constant TITLE "Your Office"

    ! create a new property for room descriptions for use in the
    ! room description window
    property win_desc

    !:: Includes (grammar must come first)
    ! put your new grammar here

    ! new grammar needs to be defined before the including verblib
    #include "verblib.g"    ! Verb Library

    #ifset PRECOMPILED_LIBRARY
    #link "hugolib.hlb"     ! Your Precompiled Library
    #else
    #include "hugolib.h"    ! Standard Hugo Library
    #endif
    #include "window.h"

    !:: Game Initialization routine
    routine init
    {
            STATUSTYPE = 1  ! 0 = none :: 1 = score/turns :: 2 = time
            counter = -1    ! 1 step before first turn

            TEXTCOLOR = DEF_FOREGROUND
            BGCOLOR = DEF_BACKGROUND
            SL_TEXTCOLOR = DEF_SL_FOREGROUND
            SL_BGCOLOR = DEF_SL_BACKGROUND
            color TEXTCOLOR, BGCOLOR

            verbosity = 2   ! 1 = normal (rooms described only if not previously
                            !     described)
                            ! 2 = full (rooms described every time they are entered)

            display.title_caption = TITLE  ! used for GUI clients for title bar text.
            prompt = ">"

            window 0 ! resets the windows in case the player is restarting a game
            cls

            DEFAULT_FONT = PROP_ON
            Font(DEFAULT_FONT)

            !:: Opening Text
            "Just a sample of using the window.h header file routines."
            print ""    ! For a blank line between the intro and the game title

            Font(BOLD_ON)
            print TITLE
            Font(BOLD_OFF)
            "An Intro to Hugo Programming Project"
            print BANNER;
            #ifset HUGOFIX
            print " (Now with HugoFix Technology TM!)"
            #else
            print ""
            #endif
            print IFID

            player = you
            location = office

            move player to location
            old_location = location
            FindLight(location)
            DescribePlace(location)
            location is visited
            CalculateHolding(player)
            ! give the player character some inventory at the beginning
            SetUpInventory

            #ifset USE_PLURAL_OBJECTS
            InitPluralObjects
            #endif
    }

    !:: Main game loop
    #ifset PRECOMPILED_LIBRARY
    replace main
    {
    #else
    routine main
    {
    #endif
            counter = counter + 1
            PrintStatusLine
            run location.each_turn
            runevents
            RunScripts
            if speaking not in location
                    speaking = 0
            ! We want the sub windows updating each turn, so
            ! we call our routines to do so here in the main routine
            UpdateInventoryWin
            UpdateRoomDesc(location)
    }

    player_character you "you"
    {
    }

    room office "Your Office"
    {
        long_desc
        {
            "Your office. It took many years of hard work (and brown-nosing) to
            finally get a position where you get the privacy of your own office."
        }

        win_desc
        {
            "Typical, generic office. There's a desk and chair, and other things
            one would expect to find in such a location."
        }

        e_to hall
        s_to bathroom
    }

    scenery desk "Your desk"
    {
        noun "desk"
        adjectives "white", "your", "my"

        short_desc
        {
            "Your new desk. Nice and white."
        }

        long_desc
        {
            "A decent sized, white desk sits near the back of your office.
            There's nothing on it. You like to think this shows the efficiency
            of your organizational skills, but deep down, you know there's nothing
            on it because it's your first day in your new position."
        }
    }

    room hall "Hallway"
    {
        long_desc
        {
            "Long, drab hall that leads to the various offices on this floor. To
            the west you can see your office."
        }

        win_desc
        {
            "Long, drab hall. Doors line both sides of the hallway, leading to
            your co-worker's offices. Maintenance said that your door will arrive
            in two to three weeks."
        }
        w_to office
    }

    room bathroom
    {
        long_desc
        {
            "Very, shall we say small, bathroom with a toilet, sink and mirror."
        }

        win_desc
        {
            "Claustrophobic bathroom that barely holds the toilet and vanity."
        }

        n_to office
    }

    !:: Routines ------------------------------------------------------------------

    ! Update the information in the Inventory window (upper right)
    routine UpdateInventoryWin
    {
        ! Initialize the inventory window and list the inventory
        run inventoryWindow.win_init
        window
        {
            run inventoryWindow.win_clear
            locate 1,1
            ! We need to save the player's preferred inventory listing format
            ! so we can change it back. In this window, we want it to be in the
            ! in the sentence format (to make it fit easier in this window if
            ! there are many items.) It is probably not a good idea to do inventory
            ! listing like this, as there's no way to scroll the window in many
            ! 'terps.

            local initial_format
            initial_format = FORMAT
            FORMAT = FORMAT | LIST_F

            ! next, we call the inventory listing routine
            Perform(&DoInventory, 0, 0, 0)

            ! then return the format to what we saved earlier
            FORMAT = initial_format
        }
        ! We're done with this window
        run inventoryWindow.win_end
    }

    ! Update the information in the Description window
    ! using the rooms win_desc property we created.
    ! if there is no win_desc, we display "NOTHING WAS DESCRIBED"
    ! as a visual flag to let us know we left it out
    ! of one of our rooms.
    routine UpdateRoomDesc(place)
    {
        run descriptionWindow.win_init
        window
        {
            run descriptionWindow.win_clear
            locate 1,1

            if &place.win_desc
            {
                run place.win_desc
            }
            else
            {
                "NOTHING WAS DESCRIBED"
            }
        }
        run descriptionWindow.win_end

    }

    routine SetUpInventory
    {
        Acquire(you, pencil)
        Acquire(you, coffeeCup)
        Acquire(you, cap)
        Acquire(you, notePad)
    }

    !:: Objects ------------------------------------------------------------------

    object pencil "No. 2 Pencil"
    {
        noun "pencil", "no", "number"
        adjective "yellow", "blunt", "unsharpened"

        inv_desc
        {
            "A yellow, number 2 pencil (unsharpened)";
        }

        long_desc
        {
            "A standard, yellow pencil. It is labeled as a 'Number 2 Pencil'.
            It new and has not been sharpened yet."
        }
    }

    object coffeeCup "Coffee Cup"
    {
        noun "cup"
        adjective "coffee", "big", "oversized"
        inv_desc
        {
            "Oversized coffee cup (empty) ";
        }
        long_desc
        {
            "It's an oversized coffee cup, the brown stains inside show that
            it has been used often, and rarely cleaned."
        }
    }

    object cap "cap"
    {
        noun "cap", "hat"
        adjective "red", "baseball"
        inv_desc
        {
            "A red baseball cap ";
        }
    }

    object notePad "Note pad"
    {
        noun "paper", "book", "notepad", "pad"
        adjective "black", "small"
        inv_desc
        {
            "Small, black note pad ";
        }
        long_desc
        {
            "One of those cheap, black note pads you can get at any dollar store.
            It's not very useful at the moment due to the fact that all the pages
            are stuck together, thanks to the \"Cola Incident\"."
        }
    }

    ! Window object definitions

    window_class inventoryWindow
    {
        ! The inventory window is the top-right rectangle of the screen:
        win_left
            return display.screenwidth/2 + 1
        win_top
            return 1 + display.statusline_height
        win_right
            return display.screenwidth
        win_bottom
            return display.screenheight/2
        win_textcolor BLACK
        win_backcolor WHITE
    }

    window_class descriptionWindow
    {
        ! the description window is the top-left of the screen
        win_left 1
        win_top
            return inventoryWindow.win_top
        win_right
            return display.screenwidth/2
        win_bottom
            return display.screenheight/2
        win_textcolor LIGHT_CYAN
        win_backcolor BLUE
    }

## graphic distortion due to text in windows (Hugo Homework)

In a game with side-by-side windows, text printed in the window on the
right can slightly distort the edge between the two windows (assuming
they have different background colors). What can one do to avoid this?

<details>
<summary>Show answer</summary>
Have the window on the right actually
be *two* windows of the same color- one "margin" window that goes right
up to the edge of the next window over and another window with a left
edge one or two characters to the right. This way, you can print
whatever text you want in the text window without worry of graphic
distortion.
</details>