---
title: light_source
permalink: /globals/light_source/
categories: 
  - Global Variables
---

`light_source` is a [hugolib.h](/library/hugolib.h/)-defined
[global variable](/basics/global/). The routines
[FindLight](/routines/findlight/) or
[ObjectIsLight](/routines/ObjectIsLight/) look for objects providing
light, setting `light_source` to the first one found. If nothing is
found, `light_source` equals 0, and routines like
[PrintStatusLine](/input-output/printstatusline/) print "In the dark"
instead of the location name.
