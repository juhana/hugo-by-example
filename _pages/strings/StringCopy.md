---
title: StringCopy
permalink: /strings/stringcopy/
categories: 
  - Strings
  - Routines
---

| calling form                  | description                                               |
|-------------------------------|-----------------------------------------------------------|
| `StringCopy(new, old[, len])` | Copies the contents of the array at the address given by `old` to the array at `new`, to a maximum of `len` characters if `len` is given, or the length of `old` if it isn’t. |

`StringCopy` is another rarely-used string routine, but hey, let's make
up an example where we would use it. Let's say we wanted to do the
*Hitchhiker's Guide to the Galaxy* thing of taking the player's first
typo and rubbing it in their face much later in the game. We would use
`StringCopy` to copy [parse$](parsing/parse$/) (where unknown words
are sent) to the string array of our choice so we can recall it later
using [StringPrint](strings/stringprint/).
