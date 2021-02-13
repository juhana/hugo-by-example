---
title: Plumbing
permalink: /contributions/plumbing/
categories: 
  - Library Contributions
  - Classes
---

[Plumbing.zip](https://raw.githubusercontent.com/hugoif/library-contributions/main/plumbing.zip) is a
library contribution that intends to save some time when coding sinks
and toilets. It consists of an object class of each, a water class to
fill them, and some additional verb routines for verbs often associated
with such. It is a modified version of the `ob_plumb.hug` file from the
Future Boy! Selected Source code release, and as such, adheres to 
[its license](misc/future-boy-license/).
Very little testing has been put into this contribution.

## Usage

Copy as much as you need from `plumbing.h` or `plumbing.g` to your game
(you may have some of those verbs already defined), then take a look at
`plumbing.hug` to see how objects are further defined.

## Additional Notes

The plumbing objects in these files are [scenery](basics/scenery/),
just like they are in the original Future Boy! files, so be aware of
that. Also, there was a bug in the original where **EMPTY SINK** would
result in the fill_water object being dropped to the floor in the
original. This gets around it somewhat, but depending on how much
utility your sink has (can objects be put in it while it has water in
it?), you may need to further refine the code.
