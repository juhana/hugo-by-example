---
title: Verb Routines
permalink: /verb-routines/
categories: 
  - Verb Routines
  - Definitions
---

A **verb routine** is a routine which processes a
[verb](verb) typed in by the user. In this
[declaration](declaration):

    verb "command"
       *                         DoCommand
       * "word2"                 DoCommand2
       * object                  DoCommand3
       * "word3"/"word4"         DoCommand4

The routine **DoCommand** is a verb routine for the verb *command* with
no arguments. The routine **DoCommand2** is a verb routine for the verb
"command" with the argument "word2", etc.
