---
title: Replace DoListen
permalink: /replacements/dolisten/
categories: 
  - Replacements
---

## Replacing DoListen

A sensory verb like "listen" could be handled many different ways. This
page will offer other alternatives.

### Room Noises

This replacement allows for rooms providing responses to &gt;LISTEN.

    replace DoListen
    {
        if not object
            {
                if not location.after
                    {
                    VMessage(&DoListen, 1)  ! "Be a little more specific..."
                    return false
                    }
                verbroutine = ""
                return true
            }
        elseif not object.after
            VMessage(&DoListen, 2)   ! "Not making any sound..."
        ! we have to clear verbroutine or else location.after.DoListen will run again
        verbroutine = ""
        return true
    }
