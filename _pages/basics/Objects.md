---
title: Objects
permalink: /basics/objects/
categories: 
  - Basics
---

An **object** is a thing which the game manipulates to accomplish tasks.
An object is a single [variable](/basics/variables/) that carries all
[attributes](/attributes/) defined in the program, and can hold
multiple values through [properties](/properties/) as well as
executable code. The object command is a
[declaration](/declarations/), not something to be executed
like a [routine](/routines/).

Objects are the building blocks of the Hugo game world. They are used to
represent everything from simple things such as a basketball to complex
things such as characters.

An object is defined through the following specification:

     object <object_name> ["optional object display name"]
    {
       [optional specifications and  code for object goes here ]
    }

The following are examples of object names: An "object" is used when you
have to define a thing that is not defined by the [standard library](/library/).
If there is an existing object or
a [class](/basics/object_classes/) which defines an object that you
can use, (like a [room](/basics/rooms/) or a
[character](/characters/)) you're probably better off using the
predefined object and adding additional properties and resetting
[attributes](/attributes/) that are different from what you
need.

Every [attribute](/attributes/) defined in the program is
automatically assigned to an object, e.g. every object has the
**[living](/attributes/living/)**, **[female](/attributes/female/)**, and
*'[static](/attributes/static/)* attributes, along with all of the other
ones.

Attributes are set or cleared through the [is](/attributes/is/) command.
Properties are added to an object by specifying them.

Here is an example of a full object definition

    attribute Hard
    attribute furniture
    attribute broken
    property color

    object Table "wooden table"
    {
      is Hard, furniture, not broken
      is static
      color "Brown"
      size 20
      capacity 100
    }

In the above case, the table has set two attributes the player has
created (hard and furniture), unset one (broken), and set one standard
property (static). It has selected three properties, one is player
created (color) and two are standard (size and capacity).
