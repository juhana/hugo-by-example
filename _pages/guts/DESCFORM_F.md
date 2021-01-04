---
title: DESCFORM_F
permalink: /guts/descform_f/
categories: 
  - Hugo Guts
---

`DESCFORM_F` is an interesting [FORMAT](FORMAT) mask as it
has an effect in a couple places. In
[PrintStatusLine](PrintStatusLine), if it is turned on, a
couple spaces are added before the location's name is printed. In
[DescribePlace](DescribePlace), there is an extra blank line
between the room's [initial_desc](initial_desc) or
[long_desc](long_desc) before room contents are listed.

These are both "Infocom"-ish type behaviors, although both were also
handled a little differently by Infocom, too (Infocom's status bars
handle the score/turn counter differently, and all room contents get
extra blank lines, not just the one). Because of this, [Replace
PrintStatusLine](Replace_PrintStatusLine) and [Replace
DescribePlace](Replace_DescribePlace) use `DESCFORM_F` to
further Infocom emulation.
