---
title: SetObjWord
permalink: /parsing/setobjword/
categories: 
  - Parsing
  - Routines
---

| calling form                  | description |
|-------------------------------|-------------|
| `SetObjWord(position,object)` | Inserts the specified object in the word array in the format: **“adjective1 adjective2 ... noun”** |

This routine is for hardcore disambiguity parsing, it seems. The only
place it is called in the Hugo Library or any released game source is in
the routine `ParsePluralObjects` in *objlib.h*.
