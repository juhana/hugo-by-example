---
title: speaking
permalink: /globals/speaking/
categories: 
  - Global Variables
---

`speaking` is a [global variable](Globals) that is used to
keep track of which NPC the player is talking to, if any. It is set by
[routines](routines) such as [SpeakTo](SpeakTo),
[DoTalk](DoTalk), [DoAsk](DoAsk), and
[DoTell](DoTell). You should set it yourself if your game
initiates a conversation without the player's input. Christopher Tate's
"converse" library contribution uses it to determine whether
[PrintStatusLine](PrintStatusLine) should draw a normal
status line or one with conversation options.
