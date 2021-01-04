---
title: StringToNumber
permalink: /strings/stringtonumber/
categories: 
  - Strings
  - Routines
---

From hugolib.h:

>StringToNumber(word) - returns the numerical value of a word such as "100";
>note that it returns 0 for any non-number, not just "0"

`StringToNumber` is a not-mentioned-in-the-manual routine that is
especially helpful when you want the player to enter a number at a
prompt (Footnote 1).

### Regular Execution

Let's throw together a simple routine, shall we? Here goes:

    routine TestRoutine()
    {
            local temp
            GetInput("\"Please enter a number as small or large as you like.\">")
        "Executing the code under parse$."
        temp = StringToNumber(parse$)
            "Your number is ";
            print number temp ;
            "."
    }

That gives us:

>"Please enter a number as small or large as you like."&gt;4  
>Executing the code under parse$.  
>Your number is 4.

With no numbers defined in the source, any number the player enters will
be held in `parse$` which we can just shuttle into `StringToNumber`.

### The Most Singular Complication of Plurality

*AKA Hey, my game uses the USE_PLURAL_OBJECTS flag and now numbers 1 through 10 are broke!!!*

If `USE_PLURAL_OBJECTS` is set, the library includes a routine called
`WordIsNumber` which adds "0" through "10 to the dictionary table. Let's
use `word[1]` to get around that:

    routine TestRoutine()
    {
            local temp
            GetInput("\"Please enter a number as small or large as you like.\">")
            if word[1]
        {
            "Executing the code under word[1]"
            temp = StringToNumber(word[1])

        }
        else
        {
            "Executing the code under parse."
            print parse$
            temp = StringToNumber(parse$)
        }

            "Your number is ";
            print number temp ;
            "."
    }

### Not to force the issue...

*"Ok, let's force the issue" Part 1*

We don't really trust that pesky player who never types what we really
want! Let's add some code so that player is caught in a loop until he
puts in a number.

    routine TestRoutine()
    {
            local temp
            GetInput("\"Please enter a number as small or large as you like.\">")
    :TryAgain
            if word[1]
        {
            "Executing the code under word[1]"
            temp = StringToNumber(word[1])

        }
        else
        {
            "Executing the code under parse."
            print parse$
            temp = StringToNumber(parse$)
        }
            if temp ~= 0
            jump PrintTemp
            GetInput("\"No, really, enter a number.\">")
            jump TryAgain
    :PrintTemp
            "Your number is ";
            print number temp ;
            "."
    }

That takes care of everything, right? No? Drat!

### Be A Zero, Not A Hero

*"Ok, let's force the issue" Part 2*

What if the player really wants to enter 0 as the number? Let's code for
that, too:

    routine DoTestRoutine
    {
            local temp
            GetInput("\"Please enter a number as small or large as you like.\">")
    :TryAgain
        ! if we check for "0", it is automatically added to the dictionary table
        if word[1] = "0"
                 jump PrintTemp
            if word[1]
        {
            "Executing the code under word[1]"
            temp = StringToNumber(word[1])

        }
        else
        {
            "Executing the code under parse."
            print parse$
            temp = StringToNumber(parse$)
        }
            if temp ~= 0
                 jump PrintTemp
            GetInput("\"No, really, enter a number.\">")
            jump TryAgain
    :PrintTemp
            "Your number is ";
            print number temp ;
            "."
    }

Hopefully, all of these examples have hammered `StringToNumber` into
your brain and has been a good example of thinking a problem through.

Footnote 1 - In commands like &gt;SET DIAL TO 100, StringToNumber is not
necessary. Go look at the DoTurnDial routine and grammar definition in
the Guilty Bastards source.
