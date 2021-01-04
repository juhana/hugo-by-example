---
title: Scope
permalink: /scope/
categories: 
  - Scope
  - Definitions
---

The scope of objects in the game refers to whether or not the
player-character (PC for short) can interact with a specific object. For
example, let's say the PC is in a kitchen, and he (or she) can see a
breadbox, and that the breadbox is closed. Inside the breadbox is a key.

The PC can interact with the breadbox. (He can e**x**amin it, pick it
up, etc...). The breadbox is said to be "in scope". Until he opens the
box, he cannot interact with the key. The key is considered "out of
scope".

Generally, the Hugo [parser](parser) uses scope rules to
determine what the PC is referring to.

### Scope (Programming)

Scope on the programming side of things refers what part of the program
can "see" a variable. Hugo supports two kinds of scope: **global** and
**local**.

A variable that has global scope can be accessed anywhere in the code. A
variable that has local scope is only visible *inside* the **routine**
where it's defined.

    ...
    global gVariable = 3 ! This variable will be visible anywhere in the code
    ...

    procedure DoSomethingInteresting
    {
        local lVar ! This variable is only visible inside the DoSomethingInteresting routine
        lVar = "I'm local"

        print "Current global threat level is "; number gVariable
        print "The local variable says \""; lVar; "\""
    }

The above code sample will print out the following:

<div class="output">

Current global threat level is 3
The local variable says "I'm local"

</div>

If the gVariable line was left out of the above example, the compiler
would stop and give you an error message.
