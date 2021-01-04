---
title: Unique ids
permalink: /tips/unique-ids/
categories: 
  - Tips
---

I originally made a very quick routine to generate unique IDs for
characters in my work in progress.

Roody improved it by eliminating the case statement, and just using
ASCII values. His code is here:

    constant UID_LIMIT 32
    array TempUID[UID_LIMIT]
    global testValue

    routine createUID(arr)
    {
    local x, y

    if not arr
        arr = TempUID

    ! This will be a 32-character id that each character gets.

        for (x =0; x<(array arr[] - 1); x++)
        {
            y=random(2)
            select y
                case 1
                    {
                    y = random(10)
                    y = 58 - y
                    }
                case 2
                    {
                    y = random(26)
                    y = 91 - y
                    }
            array arr[x] = y
        }

        array arr[x] = 0

        "Printing the array we created: ";
        StringPrint(array arr)
        ""
        "The size of the string we created is ";
        testValue = StringLength(array arr)
        print number testValue
        pause
    }

As you can see, in my program, there's half a chance that a digit will
be a number and half a chance it's a letter. I didn't know if it was
supposed to be skewed to one or the other.

Anyhow, it turned out, the ASCII value itself does the job just fine.
