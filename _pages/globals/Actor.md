---
title: "Actor"
permalink: /globals/actor
categories: 
  - Global variables
---

`actor` is a [global variable](globals) that represents the
character performing the [current action](verbroutine). In
the case of an average verb routine, `actor` is set to the
[player](player) object. In the case of [character
scripts](Scripts), though, `actor` is set to the character in
question. Checking for the `actor` global allows code that works for
several different characters.