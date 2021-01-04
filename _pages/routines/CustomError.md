---
title: CustomError
permalink: /routines/customerror/
categories: 
  - Parsing
  - Routines
---

`CustomError` is the Hugo library's way of "keeping the door open" for
making new parser error messages. It is rarely used (no openly-available
Hugo game source uses it), but it easy to set up.

#### Example

First, you replace the `CustomError` routine:

    replace CustomError(errornumber,obj)
    {
         select errornumber
              case 100 : [case 100 code] ! all CustomError cases
              case 101 : [case 101 code] ! should be error number
              case 102 : [case 102 code] ! 100 or higher
              case else : return false
         return true
    }

Then, in [PreParse](/parsing/preparse/) or a
[[verb grammar routine](/basics/grammar-tokens/) or wherever, when
you want the custom parser error message to be called, call
`ParseError(100)` (or whatever case number you are trying to call).
[ParseError](/parsing/parseerror/) will do the rest.
