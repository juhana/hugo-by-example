---
title: serial$
permalink: /guts/serial$/
categories: 
  - Hugo Guts
---

Different IF languages have different takes on the thing known as a
"serial number". The serial number is a number that is basically just
the date of compilation. Infocom and Inform serial numbers are in the
format: YYMMDD. TADS games, in general, ignores the serial number
concept (actually, according to Johnny Rivera, TADS-style is YYYYMMDD).
Hugo, on the other hand, uses a MM-DD-YY format.

At compilation time, a "MM-DD-YY" string gets saved to `serial$`. A Hugo
author can do with this whatever he pleases.

## serial number alternatives

If you don't like the look of the standard serial number, you can use
string manipulation routines for creating your own versions.

### Infocom style

If you are a traditionalist, you can use Johnny Rivera's code to make an
Infocom-style serial number:

    array _serial[10]

    routine GetSerial
    {
       local i
       string(i, serial$, 10)
       StringCopy(_serial, i)
    }

    routine PrintSerial
    {
       StringPrint(_serial, 6, 8)
       StringPrint(_serial, 0, 2)
       StringPrint(_serial, 3, 5)
    }

### Revision-number style

This [new shell](/basics/new-shell/) code uses `serial$` to print beta
"build" numbers in the style of "beta build: YYYYMMDD":

    #ifset BETA  ! this section gives build numbers to beta releases
            string(_temp_string, serial$, 8)
            "beta build: \B20";
            StringPrint(_temp_string, 6, 8)
            StringPrint(_temp_string, 0, 2)
            StringPrint(_temp_string, 3, 5)
            "\b"
    #endif
