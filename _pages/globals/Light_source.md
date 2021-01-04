---
title: light_source
permalink: /globals/light_source/
categories: 
  - Global Variables
---

`light_source` is a [hugolib.h](hugolib.h)-defined [global
variable](Globals). The routines
[FindLight](FindLight) or
[ObjectIsLight](ObjectIsLight) look for objects providing
light, setting `light_source` to the first one found. If nothing is
found, `light_source` equals 0, and routines like
[PrintStatusLine](PrintStatusLine) print "In the dark"
instead of the location name.
