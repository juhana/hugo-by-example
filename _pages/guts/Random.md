---
title: random
permalink: /guts/random/
categories: 
  - Hugo Guts
---

`random` is a command for getting random numbers. It can be used for
randomized action results, [jukebox code](Music_Engine), or
what have you. `random` will return a number between 1 and the integer
provided.

### Anything but the last choice picked

In the case of music engine songs or character actions, you often don't
want things to repeat themselves. You can combine your `random` call
with a [while](while) loop like this:

    local x,y
    x = some_object.last_value
    while x = some_object.last_value
        {
        y = random(<max choices>)
        x = y
        }
    some_object.last_value = x

This loop will run until the `random` command comes up with a different
value.

## Turning "random" off

For testing purposes, you can turn off randomization using either
[HugoFix](HugoFix) commands or calling the appropriate
[system](system) number yourself somewhere in the code.
