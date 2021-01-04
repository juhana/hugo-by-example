---
title: ObjectisKnown
permalink: /routines/objectisknown/
categories: 
  - Routines
---

| calling form            | description                                          |
|-------------------------|------------------------------------------------------|
| `ObjectisKnown(object)` | Returns true if the object is `known` to the player. |

Among other things, it is called by [FindObject](FindObject)
and must return true for [FindObject](FindObject) to work.
For this reason, the Hugo Book recommends
[replacing](Replace) `ObjectisKnown` with a routine that
unconditionally returns true if your game requires
[FindObject](FindObject) to work with un`known` objects.
