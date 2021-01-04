---
title: verbosity
permalink: /globals/verbosity/
categories: 
  - Global Variables
---

`verbosity` is a [global variable](basics/global/) that affects how
room descriptions are printed. It is basically a legacy feature from
olden days when the amount of room text could actually affect the
loading times in the game (or even older olden days, when some people
played IF games with no monitor, having output go straight to a printer).

| verbosity value | mode name  | mode behavior                |
|-----------------|------------|------------------------------|
| 0               | Brief      | Full description is printed first time a room is visited, followed by abridged versions (this was the default in olden days) |
| 1               | Superbrief | Terse description is printed every single |
| 2               | Verbose    | Full room descriptions every time. |
