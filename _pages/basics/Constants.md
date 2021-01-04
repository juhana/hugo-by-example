---
title: Constants
permalink: /basics/constants/
categories: 
  - Basics
---

The **constant** command is a [declaration](declarations)
used to create an [identifier](identifier) known to the
program.

The Hugo Book does a pretty good job of explaining what constants are.
It's a little unclear on the usefulness of constants, though. Although
it doesn't say so, a constant is probably a compiler-based text
replacement, so that if you define a constant `HAPPY`, as shown below,
the compiler probably replaces every use of HAPPY with the value 1.

Let's pretend we are coding a game where characters have moods. If we
handled the moods with attributes, we'd burn through our attribute limit
(a non-modifiable limit) in no time. [Global
variables](Variables#Global_Variables) also have a hard
limit. Let's turn our moods into constants (and make a mood property):

    constant HAPPY 1
    constant SLAPPY 2
    constant SAD 3
    constant SWEDISH 4

    property mood

This allows us to define a character like this:

    character royce "Royce"
    {
          noun "royce"
          mood SWEDISH
    }

We could have a mood-checking verb routine like this:

          select speaking.mood
                case HAPPY : "Happy result."
                case SLAPPY : "Slappy result."
           !    etc....

To the engine/compiler, we are checking to see if the character's mood
equals 1, 2, or so on. To us, though, we are actually checking for
moods. As such, constants are a great organizational, memory-saving
trick.

## Enumeration

In the above constant-declaring, we could have saved ourselves some time
using the [`enumerate`](enumerate) command which
automatically applies consecutive values for us:

    enumerate start = 1 ! what number we want to start counting at. if just 'enumerate', we start at 0
    {
           HAPPY, SLAPPY, SAD, SWEDISH
    }

That gives us: HAPPY = 1, SLAPPY = 2, and so forth

We can make a "value gap" if we specifically define something midstream:

    enumerate start = 2
    {
           HAPPY, SLAPPY, SAD = 6, SWEDISH
    }

That gives us: HAPPY = 2, SLAPPY = 3, SAD = 6, and SWEDISH = 7

### step

Finally, it is possible to alter the step value of the enumeration using
the step keyword followed by +n, -n, \*n, or /n, where n is a constant
integer value. To start with 1 and count by multiples of two:

    enumerate step *2
    {
    A = 1, B, C, D
    }

giving: A = 1, B = 2, C = 4, D = 8.

-   As a side note, you can also use `enumerate` to give initial values
    to [global variables](Variables#Global_Variables)
    following the instructions [here](Variables#Enumeration).

## Not a Man of Sorrow Constants

Constants do not actually need to be given any default value to be
distinct from each other.

    constant THIS_RESULT
    constant THAT_RESULT

These two constants will have unique values from each other, as well as
from any other constant defined without a specific value.
