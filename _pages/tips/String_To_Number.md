---
title: String To Number
permalink: /tips/string-to-number/
categories: 
  - Tips
---

Hugo has a routine called StringToNumber, which will convert a string
into a number. It sounds straightforward, but I would like to provide
some sample code:

    routine TestRoutine()
    {
        GetInput("\"Please enter a number as small or large as you like.\">")

        if word[1]
        {
            "Executing the code under word[1]"
            temp = StringToNumber(word[1])
        }
        else
        {
            "Executing the code under parse."
            print parse$
            temp = StringToNumber(parse$)
        }

        "Your number is ";
        print number temp ;
        "."
    }

I believe what's going on here is that Hugo understands the values 1
through 10. They end up in word\[1\]. It doesn't know 11 through 32,767
(although I really just tried 11 and 12 and assumed the other thirty
thousand would behave the same way). It places that into parse$.
Regardless, using the power of StringToNumber, you can then manipulate
what your player gave you as an int afterwards.
