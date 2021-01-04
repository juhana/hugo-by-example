---
title: mobile
permalink: /attributes/mobile/
categories: 
  - Attributes
---

The `mobile` attribute, as used by the 
[Standard Library](Standard_Library), is solely used for
[attachments](attachments), representing objects that can be
dragged from room to room. The "[Rolling
Objects](Rolling_Objects)" page uses it to represent objects
that can be pushed from room to room (of course, those two uses might
not work together).

In either case, if the mobile object can be picked up, be sure to use
the [CalculateHolding replacement](Replace_CalculateHolding),
which fixes a bug where non-[clothing](clothing) mobile
objects don't count towards one's [holding](holding) (as
`mobile` is an [alias](alias) of [worn](worn)).
