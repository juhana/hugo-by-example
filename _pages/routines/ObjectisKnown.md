---
title: ObjectisKnown
permalink: /routines/objectisknown/
categories: 
  - Routines
---

| calling form            | description                                          |
|-------------------------|------------------------------------------------------|
| `ObjectisKnown(object)` | Returns true if the object is `known` to the player. |

Among other things, it is called by [FindObject](/scope/findobject/)
and must return true for [FindObject](/scope/findobject/) to work.
For this reason, the Hugo Book recommends
[replacing](/guts/replace/) `ObjectisKnown` with a routine that
unconditionally returns true if your game requires
[FindObject](/scope/findobject/) to work with un`known` objects.
