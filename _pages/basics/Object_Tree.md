---
title: Object Tree
permalink: /basics/object-tree
categories:
  - Basics
  - Object Tree
---

The object tree is the hierarchy of [objects](basics/objects/) in the
Hugo world that you create. The object tree is the internal
representation of the relationships between the various objects in the
game.

## The Branches

The first object that is defined (in the Hugo standard library) is the
**nothing** object. This is the root of the object tree and all the
other objects are *children* of this one.

Let's take a look at a sample. Let's say you've created a room called
**kitchen** with a table and counter located inside it. On the table are
a plate and fork, and on the counter some eggs. The object tree may be
something like the following:

![Object tree](assets/images/Object tree 1.jpg)

The parent of the *kitchen* object (room) is the **nothing** object. The
children of the kitchen are table, counter and the player character. The
**table** object has two children (the plate and fork) and the
**counter** has one child (the eggs).

## Climbing Around

There are a number of built-in functions that can be used to read the
object tree:

| Function     | Definition                                                                                             |
|--------------|--------------------------------------------------------------------------------------------------------|
| `parent()`   | Returns the parent of the object                                                                       |
| `sibling()`  | Returns the next sibling                                                                               |
| `child()`    | Returns the child of the object                                                                        |
| `youngest()` | Returns the youngest child of the object                                                               |
| `elder()`    | Returns the older sibling (the next object to the left on the object tree graph)                       |
| `eldest()`   | Returns the oldest child of the object (same as child())                                               |
| `younger()`  | Returns the younger sibling (the next object to the right on the object tree graph); same as sibling() |
| `children()` | Returns the number of children the object has                                                          |

Each of these functions takes a single object as an argument. If we were
to use the functions on the above table, they would return the
following:

| Function | Returns |
| --- | --- |
| `parent(table)` | kitchen |
| `sibling(table)`<br>`younger(table)` | counter |
| `child(counter)`<br>`eldest(counter)` | eggs |
| `youngest(kitchen)` | player |
| `elder(table)` | 0 (nothing) |
| `elder(plate)` | 0 (nothing) |
| `children(kitchen)` | 3 (number of objects that are directly below kitchen) |
| `children(eggs)` | 0 |

Now, let's take a look at the table if the player types the following
commands in the game

>&gt;Get eggs. Put eggs on the plate.

The object tree will now look like this:

![Object tree](assets/images/Object tree 2.jpg)

As you can see, the parent of *eggs* has become the *plate* object.

When creating an object, use the `in <object>` command to place it in a
certain part of the tree.

    object table "kitchen table"
    {
        noun "table"
        adjectives "brown", "kitchen", "small"
        in kitchen

        long_desc
        {
          ! rest of code
        }
    }

If you don't specify where in the tree an object resides, it will
default to **nothing**.

### The `nearby` property

You can also use the command `nearby` or `nearby <object>` to give
object the same parent as `<object>`, or if `<object>` is not specified, the
same parent as the last-defined object.

    object eraser "chalkboard eraser"
    {
       article "the"
       adjective "chalkboard"
       noun "eraser"
       nearby chalkboard ! starts in same room as chalkboard object
    }

    object desk "desk"
    {
       article "the"
       noun "desk"
       nearby   ! is in the same room as last-defined object
    }

## Falling Off (AKA Rookie Mistakes)

Generally, it's a lot safer to check up the object tree instead of down.
**if child(object) = other_object** will only work when `other_object`
is the oldest child in the tree.

On the flip side of that coin, though, are statements like 
**if parent(object) = location**. If you're checking on the player, it'll be
false if the player is in a vehicle or on a platform (like a chair). If
you're checking for an object, it'll be false if it's on a platform or
in a container or in the player's possession, even. This might be
obvious right now- as you've just read this page- but it's easy to
forget!

To get around these issues, you'll want to use routines like
[Contains](routines/contains/), which checks to see if an object is a
child or grandchild of another object, or
[FindObject](scope/findobject/), which checks to see if an object is
in a specific location. It even returns a special value if it can be
seen but can't be reached (like in a closed, transparent container).

That's it! Go hug an object tree today!
