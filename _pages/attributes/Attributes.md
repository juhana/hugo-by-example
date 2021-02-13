---
title: Attributes
permalink: /attributes/
categories: 
  - Attributes
  - Basics
---

You can think of an attribute as something that an object has, or
doesn't have. It represents a simple YES/NO definition. Is the object
open, can the object be locked, etc... 

### Predefined attributes

Unlike some properties, there are no predefined attributes created by
the compiler, although there are some which are predefined by the
[standard libraries](library/). You can define a
maximum of 128 attributes, including those defined by the standard
libraries. This is one of the [Hugo Compiler](basics/compiler/)'s 
*hard limits* (it can't be
changed). Using the [alias](basics/alias/) command, you can get
around this limitation. There are several attributes defined in the Hugo
standard library (in the order shown under *order defined*) in the
following table.

| Attribute name | Attribute value | Order defined | Used for | Notes | 
|----------------|-----------------|---------------|----------|-------| 
| [active](attributes/active) | 14 | 17 | Set if an object is active | (alias for [switchedon](attributes/switchedon)) | 
| [already_listed](attributes/already_listed) | 23 | 28 | For library use. | (alias for [workflag](attributes/workflag)) | 
| [clothing](attributes/clothing) | 15 | 18 | Set if an object can be worn |  | 
| [container](attributes/container) | 18 | 22 | Set if an object can contain things (have something put in them). | Conflicts with platform (see below) | 
| [enterable](attributes/enterable) | 17 | 21 | Set an object may be entered |  | 
| [female](attributes/female) | 05 | 07 | Set if a character is female (default is male) |  | 
| [hidden](attributes/hidden) | 20 | 24 | Set if an object is not listed |  | 
| [known](attributes/known) | 00 | 01 | Set when an object is known by the player |  | 
| [light](attributes/light) | 11 | 13 | Set if an object is/provides light |  | 
| [living](attributes/living) | 04 | 06 | Set if an object is a character |  | 
| [lockable](attributes/lockable) | 08 | 10 | Set if an object can be locked |  | 
| [locked](attributes/locked) | 09 | 11 | Set if an object is locked |  | 
| [mobile](attributes/mobile) | 16 | 20 | Set if an object may be moved around. | (alias for [worn](attributes/worn)) | 
| [moved](attributes/moved) | 01 | 02 | Set when an object has been moved | aliased by [visited](attributes/visited) | 
| [open](attributes/open) | 07 | 09 | Set if an object is open |  | 
| [openable](attributes/openable) | 06 | 08 | Set if an object can be opened |  | 
| [platform](attributes/platform) | 19 | 23 | Set if an object can contain things (have something put on them). | Conflicts with [container](attributes/container) (see below) | 
| [plural](attributes/plural) | 03 | 05 | Set for plural objects |  | 
| [quiet](attributes/quiet) | 21 | 25 | Set if a container/platform is quiet (contents not initially listed). |  | 
| [readable](attributes/readable) | 12 | 14 | Set if an object can be read |  | 
| [special](attributes/special) | 24 | 29 | For miscellaneous use. |  | 
| [static](attributes/static) | 02 | 04 | Set for an object that cannot be taken |  | 
| [switchable](attributes/switchable) | 13 | 15 | Set if an object can be switched on/off |  | 
| [switchedon](attributes/switchedon) | 14 | 16 | Set if an object is switched on |  | 
| [transparent](attributes/transparent) | 22 | 26 | Set if an object is not opaque (it can be seen through.) |  | 
| [unfriendly](attributes/unfriendly) | 10 | 12 | Set if a character is an opponent |  | 
| [visited](attributes/visited) | 01 | 03 | Set when a room has been visited | (alias for [moved](attributes/moved)) | 
| [workflag](attributes/workflag) | 23 | 27 | For library use. | aliased by [already_listed](attributes/already_listed) | 
| [worn](attributes/worn) | 16 | 19 | Set if an object is being worn. | aliased by [mobile](attributes/mobile) | 


After the attributes mentioned in the above table, you have a total of
104 available (non-aliased) attributes left that you can define for your
game.

### New attribute definition

To define an attribute, use the attribute command `attribute `<name>.
For example, if an object in your game can be magic or not, you may
create an attribute like so:


    attribute magic

    object lantern "Magic lantern"
    {
        nouns "lantern", "light"
        adjectives "magic", "small"

        long_desc
        {
            "A small, magic lantern is sitting here."
        }

        is magic, light
    }

### Importance of proper object attribution

Several verb [grammar tokens](basics/grammar/) rely on attributes
being set correctly. This means that even when you want your game to
deny a specific command, the proper attribute needs to be set for it to
work correctly. Imagine, if you will, a television set with the
following `before` code:

    Object TV "television"
    {
        is static   !  Can't be moved

        before {
            object DoSwitchOff
            {
                "You'd turn off the tv, but you're pretty sure \"Wheel of Misfortune\" is on next."
                return true
            }
        }
    }

Without the `switchable` attribute, &gt;TURN OFF TV will get the
response "You can't do that with the television." and all of your
players will be left to wonder when- *if ever*- "Wheel of Misfortune"
will air. Don't do that to them. In this example, the second line of the
definition should be changed to:

    is static, switchable   !  Can't be moved, can be turned on

### Aliases


*Main Article: [alias](basics/alias/)*

If you need to define a lot of attributes and might run out of them,
what you can do is define some attribute as an alias of another
attribute. If there are two conditions that are mutually exclusive, or
that they don't apply to different classes of objects, then you can
alias an existing attribute to something else. For example, let's say
you have an attribute called 'broken' to indicate the player broke
something. This is only going to be used by an object that can be
broken, so if you have a scenery object - like a radioactive boulder -
that can't be broken but has to glow, you could do the following:

    attribute broken
    attribute glow alias broken

Then the attributes 'broken' and 'glow' are the same attribute, and you
can use them interchangeably.
