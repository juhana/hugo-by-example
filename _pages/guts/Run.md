---
title: run
permalink: /guts/run/
categories: 
  - Hugo Guts
---

`run` is a command for executing [property routines](/properties/).

If <object> does not have <property>, or if <object>.<property> is not a
routine, nothing happens. Otherwise, the property routine executes.
Property routines do not take arguments. ===<Example:===> Here is a
terminal switch from Distress that redirects an examination to a
terminal object.

    object term_switch "on/off switch"
    {
        nouns "switch", "on/off"
        adjectives "on/off"
        article "an"
        inherits component
        part_of terminal
        is switchable
        long_desc {
            if (terminal is not moved) and (covegn.found_in = location) {
                run terminal.long_desc
            } else {
                print "It's "; The(self); " for "; The(terminal); "."
            }
        }
        before {
            object DoPush, DoTouch {
                if (terminal is switchedon) {
                    perform(&DoSwitchOff,terminal)
                } else {
                    perform(&DoSwitchOn,terminal)
                }
            }
            object DoSwitchOn,DoSwitchOff {
                perform(verbroutine,terminal,xobject)
            }
        }
    }
