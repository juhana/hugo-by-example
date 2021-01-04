---
title: Asterisk
permalink: /operators/asterisk/
categories: 
  - Operators
---

The **asterisk** symbol ( **\*** ) has two uses in the Hugo language. As
the first symbol on a line, it is a
[declaration](/declarations/) used to define a parameter to the
[verb](/declarations/verb/) command. Otherwise it is used as an
[operator](/operators/) to multiply two numbers. Here are a few
examples of how it is used.

As a declaration:

    verb "incinerate"
        *                  DoIncinerate
        * "me"             DoSuicide

As an operator:

    i = j * 2

    ! Or an example from the book:

    enumerate step *2
    {
    A = 1, B, C, D
    }

giving: A = 1, B = 2, C = 4, D = 8.

See Also: [verb](/declarations/verb/), [operators](/operators/)
