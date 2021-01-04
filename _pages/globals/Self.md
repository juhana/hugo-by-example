---
title: self
permalink: /globals/self/
categories: 
  - Global Variables
---

`self` is a [global variable](/basics/global/) declared and (usually)
set by the engine. It refers to the current object or fuse while that
code is being read.

    object mirror "mirror"
    {
       misc 0
       long_desc
          {
          print "You have looked at the mirror "; NumberWord(++self.misc);
          if self.misc < 2
             " time."
          else
             " times."
          }
    }
