---
title: While
permalink: /loops/while/
categories: 
  - Loops
---

The `while` loop is pretty simple.

    while <expression> (is true)
    {
        code to execute
    }

Similarly, there is also the `do-while` loop.

    do 
    {
        code to execute
    }
    while <expression> (is true)

The two versions work almost identically except that in the case of
`do-while`, the code will be executed at least once (even if the `while`
expression is false). This is not the case for the strictly `while`
example.

## `while` loops in Hugo

Among other things, the `while` loops are often used for emptying
containers. Let's take a look at a somewhat slimmed-down version of
`DoEmpty`:

    !----------------------------------------------------------------------------
    routine DoEmpty
    {
        local a, b, obj, xobj
        local thisobj, nextobj

            ! some skipped code

        thisobj = child(object)

        while thisobj ! run this code as long as there are children of the container
        {
            nextobj = sibling(thisobj) ! determine if there is another object in this container to do
                                               ! after this one

            print thisobj.name; ":  ";

            if thisobj is static
                VMessage(&DoEmpty, 3)    ! "You can't move that."
            else
            {
                         ! actual emptying code trimmed
            }

            thisobj = nextobj  ! this line will be important
        }

        run object.after
        return true
    }

You'll notice that, at the end of the "code to execute", the code
changes the `thisobj` [local variable](basics/variables/) 
to the object's sibling.

If the object *had* been moved and the value of `thisobj` wasn't
changed, the program would determine that it was no longer a child of
the container and go, whew, guess I'm done! Changing the value there
keeps the loop going. If `thisobj` *had* been the last child of the
container, its [sibling](basics/object-tree) will be `0` so the loop
will break when it gets to the end.

## `do-while` loops in Hugo

Look at `do-while` in this next example, which could be used for a
randomized event (like a NPC's behavior in a room) where you don't want
one response repeating twice in a row:

    local a
    do
    {
        a = random(3)
        object.misc = a
    }
    while a = object.misc

In the above example, if your game didn't give an initial value to
`object.misc` and there *wasn't* that `do` block, the randomization code
would never be executed. With the `do` code, we can be sure that things
are set in motion properly.
