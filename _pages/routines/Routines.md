---
title: Routines
permalink: /routines/
categories: 
  - Routines
  - Basics
---

A *routine* in Hugo is group of instruction that perform a particular
task. It is the equivalent of a "subroutine", "procedure", or "function"
in other programming languages.

There are two types of routines, those that are used for processing
*[verbs](/declarations/verb/)*, i.e. a piece of code when the task needs to
define what happens when the player types a verb, and those that are
*called* by other routines.

Routines are defined by the **routine** keyword, followed by the name of
the routine, and possibly followed by arguments. It is preceded by an
open brace **{** before the code of the routine, and is followed by a
close brace **}** after the end of the code for the routine.

The value of **routine_name** and each argument, if any, must conform
to the rules for identifiers: 31 or fewer characters; must begin with a
letter; after the first, additional characters may be a letter, a
number, or the underscore. Identifiers cannot be the same as keywords.

## Routine without arguments

Here is an example of a simple routine that does not need any extra
information (known as *arguments*) from the Scavenger Hunt tutorial
(available at the ifarchive
[ScavHuntFull.zip](http://ifarchive.org/if-archive/programming/hugo/examples/ScavHuntFull.zip):

    routine DoBowl
    {
        if not location = bowlingalley
            "This isn't an appropriate location for bowling."
        else
            if not Contains( bowlingalley, bowlingball )
                "I don't see any bowling ball around here. That is, any \Bavailable\b one."
            else
                return Bowling
    }

## Routines *with* arguments

Sometimes the routine will need some information from you when it's
called. To pass information to the routine, you put the needed
information in parenthesis after the routine name. The following example
is from the *hugolib.h* file. It's the routine that prints the **\*\*\*
YOU WON THE GAME! \*\*\*** or **\*\*\* YOU HAVE DIED \*\*\*** message at
the end of a game. This routine needs to know whether the player has won
or lost (died), so it is called with the information in the argument
*end_type*. *This routine is called by another routine, it is not
usually called by the programmer directly.*

    routine PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        select end_type
            case 1:  print "\n*** YOU'VE WON THE GAME! ***"
            case 2
            {
                if player_person = 2
                    print "\n*** YOU HAVE DIED ***"
                else
                    print "\n*** "; CThe(player); \
                        MatchPlural(player, "has", "have"); \
                        " died! ***"
            }

        Font(BOLD_OFF)
        PrintScore(true)
    }

## Replacing a previously defined routine

Sometimes, there's a routine that does *mostly* what you need it to do,
but you need to customize it to fit with your game. There are also many
pre-defined routines in the *verbstub.h* file
that actually need to be coded so they actually do something in your
game.

If you were to try create a routine with the same name as one that's
already been defined, you will get an error when you try to compile the
code. This is where the **replace** command comes in. It lets you
replace a previously defined routine with one of your own. Generally you
will only be replacing routines from the Hugo Library to customize them
for your game.

Replace is used pretty much in the same manner as *routine*

Let's say that the PC cannot die in your game. The standard
*PrintEndGame* routine has only two options for messages printed, either
**\*\*\* YOU'VE WON THE GAME \*\*\*** or **\*\*\* YOU HAVE DIED
\*\*\***. Which is not what you need. Because it's already been defined
in the library, and it's been included, you cannot just type **routine
PrintEndGame**, you'll have to replace it like so:

    replace PrintEndGame(end_type)
    {
        Font(BOLD_ON)
        select end_type
            case 1:  print "\n*** YOU'VE GRADUATED ***"
            case 2:  print "\n*** YOU'VE FAILED, LOOKS LIKE IT'S SUMMER SCHOOL FOR YOU! ***"

        Font(BOLD_OFF)
        PrintScore(true)
    }
