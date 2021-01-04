---
title: Variables
permalink: /basics/variables/
categories: 
  - Basics
  - Declarations
---

A variable is a memory space defined in the program. There are several
types of variables in the Hugo Programming languages. Public variables
are defined through the [declarative](/declarations/) command
[global](/basics/global/). Variables used only by a
[routine](/routines/) are defined through the declarative
command [local](/basics/locals/). Variables which are attached to an
object are either declared as [attributes](/attributes/), which
can hold only a true/false value, or as
[properties](/properties/), which can hold any value.


A variable is a named location in the computer's memory. Each variable
is used to hold a piece of information that your game may need to refer
to in various places of the code and where the data stored in that
variable might not be the same at the beginning of the game as in the
middle, or the end (i.e. the information <i>varies</i>. If you have a
piece of information that will never change, you're better off using a
[constant](/basics/constants/).

A variable is defined by an [identifier](/definitions/identifier/), which
is the name of that variable and how it is referenced by the program. An
identifier can contain up to 32 alpha-numeric characters. The only
punctuation character allowed in an identifier is the underscore ("_").
The name of a variable also cannot be any one of Hugo's predefined words
(like [property](/properties/), [routine](/routines/),
and function names). If a variable is [global](/basics/global/) to the
program (as opposed to a [local](/basics/locals/) defined in a routine)
it must not have the same name as any other global,
[attribute](/attributes/), or [object](/globals/object/).

### Global Variables

*Main article: [global](/basics/global/)*

A global variable is one that is available anywhere in the program at
any time. It must be unique to any other global variable, property or
object.

Format: **global** *[identifier](/definitions/identifier/)* \[= *optional value*\]

    global xyzzy
    global favorite_color = "blue"

If a global is not given a value, it defaults to 0.

#### Enumeration

Like [constants](/basics/constants/), you can use the
[`enumerate`](/guts/enumerate/) command to define your global
variables with initial values. You just need to use the
[`globals`](/basics/global/) attribute:

    enumerate globals
    {
    <global1>, <global2>,...
    }

`global1` = 0, `global2` = 1, etc. (Check out the 
[Constants page](/basics/constants/) for more information on
enumeration)

### Local Variables


'' Main article: [locals](/basics/locals/)

A local variable is a variable that can only be accessed within the
routine that it is defined in. Other routines do not have access to
another routine's local variable. A local variable is defined in a very
similar manner to a global.

Lets say you need a [routine](/routines/) that will count down
from any number that is passed to it, it might be defined like this:

        routine CountDown(count_from)
        {
            local count

            print "The countdown has begun!\n"

            for (count = count_from; count > 1; count = count - 1)
                print number count; " seconds remain."

            "Boom goes the dynamite."

        }

        routine HowManyCoins
        {
            local count

            for count in mywallet
                {
                count = count + 1
                }

            print "There are "; number count; " coins in my wallet."
        }

In this sample, we have two routines, each of which defines a local
variable named `count`. Because they are defined in two different
routines, they can have the same name. The `count` variable in the
`CountDown` routine will never be confused with the `count` variable in
the `HowManyCoins` routine.

### Do's and Don'ts

If you create a class, be sure it's not the same as
a prior variable you've used. The compiler will allow you to use a class
name as a variable, and if you do, the run-time will crash. For example,
if you used the following:

    global Merchandise


    [ and in several places you had the following code: ]

        Merchandise++

If later, you decided to change that variable to Merchandise_Count, and
then created a class called Merchandise, if you forget to change all
references of **Merchandise++** to **Merchandise_Count++** (or any
other arithmetic reference), once you add one to the class name, the
run-time will crash the game.

See Also: [attributes](/attributes/),
[identifier](/definitions/identifier/), [properties](/properties/)
