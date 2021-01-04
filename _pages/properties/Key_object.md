---
title: key_object
permalink: /properties/key_object/
categories: 
  - Properties
---

`key_object` is given to objects with the
[lockable](lockable) attribute. They specify the object that
can be used to lock or unlock the lockable object. `key_object` is an
[alias](alias) of [ne_to](ne_to).

### Examples:

    object treasurechest "treasure chest"
    {
        article "the"
        adjective "treasure"
        noun "chest"
        key_object blackbeardskey
        is container openable lockable locked
    }

    door red_door "red door"
    {
        article "the"
        adjective "red"
        noun "door"
        key_object skeleton_key
        is lockable locked
        between room1 room2
    }

### Hugo Homework

As they stand, `DoLock` and `DoUnlock` only check the first element of
the `key_object` property. [Replace](Replace) them with
versions that allow for multiple `key_object`s, using
[InList](InList) and multiple property elements!
