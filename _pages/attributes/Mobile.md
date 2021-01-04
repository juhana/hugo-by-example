---
title: mobile
permalink: /attributes/mobile/
categories: 
  - Attributes
---

The `mobile` attribute, as used by the 
[Standard Library](/library/), is solely used for
attachments, representing objects that can be
dragged from room to room. The 
"Rolling Objects" page uses it to represent objects
that can be pushed from room to room (of course, those two uses might
not work together).

In either case, if the mobile object can be picked up, be sure to use
the [CalculateHolding replacement](/replacements/calculateholding/),
which fixes a bug where non-[clothing](/attributes/clothing/) mobile
objects don't count towards one's [holding](/properties/holding/) (as
`mobile` is an [alias](/basics/alias/) of [worn](/attributes/worn/)).
