---
title: Plumbing
permalink: /contributions/plumbing/
categories: 
  - Library Contributions
  - Classes
---

["Plumbing"](https://github.com/hugoif/library-contributions/tree/main/plumbing) is a
library contribution that intends to save some time when coding sinks
and toilets. It consists of an object class of each, a water class to
fill them, and some additional verb routines for verbs often associated
with such. It is a modified version of the `ob_plumb.hug` file from the
Future Boy! Selected Source code release, and as such, adheres to 
[its license](misc/future-boy-license/).
Very little testing has been put into this contribution.

## Usage

Look at 'plumbing_example.hug' to see how to incorporate it into your game, and alter the files as needed.

## Additional Notes

The plumbing objects in these files are [scenery](basics/scenery/),
just like they are in the original Future Boy! files, so be aware of
that. Also, there was a bug in the original where **EMPTY SINK** would
result in the fill_water object being dropped to the floor in the
original. This gets around it somewhat, but depending on how much
utility your sink has (can objects be put in it while it has water in
it?), you may need to further refine the code.
