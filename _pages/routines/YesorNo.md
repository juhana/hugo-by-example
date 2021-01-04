---
title: YesorNo
permalink: /routines/yesorno/
categories: 
  - Routines
---

| calling form | description      |
|--------------|------------------|
| `YesorNo`    | Checks to see if the just-received input is "**yes**", "**y**", "**no**", or "**n**". If none of the above, it prompts for a yes or no answer. Once a valid answer is received, it returns true (if yes) or false (if no). |

`YesorNo` is a quick way to get one of those "Please enter YES or NO:"
prompts within a game. Among other uses, it can be used to convey that
the player has just been presented with an important decision.

### The code itself

    !----------------------------------------------------------------------------
    ! YesorNo
    ! returns true if word[1] is "yes", false if "no"; prompts for a
    ! new input if neither

    routine YesorNo
    {
        local w, count
        w = word[1]
        while true
        {
            if w = "yes", "y"
                return true
            elseif w = "no", "n"
                return false

            if ++count < 10
                Message(&YesorNo, 1)    ! ask "yes" or "no"
            else
                Message(&YesorNo, 2)
            GetInput
            w = word[1]
        }
    }

### Usage example

Imagine you're writing a game that displays important information in the
status bar. Unfortunately, status bars aren't displayed on
[cheapglk](https://github.com/erkyrath/cheapglk) clients like the one
used for [Floyd](http://www.ifwiki.org/index.php/Floyd_%28bot%29) on
[the ifMUD](http://ifmud.port4000.com/). While we can test if a game is
being played on a glk interpreter (since glk interpreters incorrectly
count the number of lines in `display.windowlines`), there's no way to
check if it is a cheapglk client. Let's ask the player! We can then code
an alternate way to display the necessary information in the game so we
can wow them at [ClubFloyd](http://www.ifwiki.org/index.php/ClubFloyd)!

    global glk
    global cheap

    routine init
    {
            ...
        if display.windowlines > display.screenheight
            glk = true
        if glk
            cheap = statuscheck
            ...
    }

    routine statuscheck
    {
        "Hugo detects that you are using a GLK interpreter. Is it a cheapglk interpreter (with no status bar)?"
        return YesorNo
    }

The above code first determines if the game is being played on a glk
client by checking `display.windowlines`. If it is, then it runs the
routine `statuscheck` which sets the global variable `cheap` to true if
the player enters "**yes**." Hooray!

### Yes? No? It's complicated!

To be perfectly honest, the above code is not fool-proof. Since
`YesorNo` checks `word[1]`, it doesn't run properly if word\[1\] is
already in memory as "**yes**." In the above example, typing "**yes**"
at the prompt and then restarting will skip the prompt the second time
around (since "restart" doesn't overwrite `word[1]` for whatever reason.
To fix that, clear `word[1]`'s value before calling `YesorNo`.

This also comes into play if you call `YesorNo` consecutively. In the
next example, we will recreate the "egress" code from *Ballyhoo*:

    s_to {
        "Are you sure you're mentally and otherwise prepared to meet up with an egress?\n"
        if YesorNo
        {
            word[1] = 0
            "Then you're fully aware of the ferociousness of this rare mammalian species, right?\n"
                if YesorNo
                    "Then you'd be helpless against this dangerous beast."
                else
                {
                    word[1] = 0
                    "Alright, so you know all about egresses.
                    But do you really want to leave the circus in all of its mystery
                    and all of its pageantry behind?\n"
                    if not YesorNo
                        "That's the spirit."
                    else
                    {
                        endflag = 3
                    }
                }
            }
        else
            "Then you'd be helpless against this dangerous beast."
    }

NOTE: As shown, `YesorNo` is a nice and quick decision-coding solution,
but if you want a more *authentic Ballyhoo egress experience*, go take a
look at [Informal Questions](/tips/informal-questions/).

### Alternatively!

If you are the sort of courageous person who has no qualms about
*enhancing* the Hugo library, instead of doing all of that `word[1]`
trickery in the previous example, you could use this `YesorNo`
replacement:

    replace YesorNo(new)
    {
        local w, count
        if new
            word[1] = 0
        w = word[1]
        while true
        {
            if w = "yes", "y"
                return true
            elseif w = "no", "n"
                return false

            if ++count < 10
                Message(&YesorNo, 1)    ! ask "yes" or "no"
            else
                Message(&YesorNo, 2)
            GetInput
            w = word[1]
        }
    }

As much as we'd like to clear `word[1]` in every scenario, doing so is
complicated by the fact that verb routines such as `DoQuit` and
`DoRestart` have their own "yes or no?" text so clearing `word[1]` would
force the player to go through it twice. The best we can do (without
replacing more of the library) is this, where calling `YesorNo` will
work in the old way, but our own calls will be `YesorNo(true)` so
`word[1]` is properly cleared.

Anyhow, wasn't that great?  
Please answer YES or NO:
