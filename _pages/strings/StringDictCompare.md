---
title: StringDictCompare
permalink: /strings/stringdictcompare/
categories: 
  - Strings
  - Routines
---

| calling form                         | description                              |
|--------------------------------------|------------------------------------------|
| `StringDictCompare(array,dictentry)` | Performs a `StringCompare`-like comparison of a string array given by `array` and the dictionary entry `dictentry`, returning 1, -1, or 0 if `array` is lexically greater than, less than, or equal to `dictentry`, respectively. |

Actually, if you take a look at `StringDictCompare`'s code, you'll see
that it just writes the dictionary entry to a string array and does a
[StringCompare](StringCompare). Still, a step saved is a step
saved, right?

Here is a silly usage example:

    "The puzzlebot turns to you and asks, \"What is in the middle of holes?\""
    GetInput("ENTER ANSWER IN QUOTES>")
    string(names, parse$, 10)
    if StringDictCompare(names, "l") = 0
        print "Correct!"
    else
        print "Wrong!"

Which results in:

>The puzzlebot turns to you and asks, "What is in the middle of holes?"  
>ENTER ANSWER IN QUOTES&gt;"L"  
>Correct!

Some things to keep in mind:

1. The above source code assumes that an array called `names` has been
created.
2. Just having "l" in `StringDictCompare`'s routine calling adds it to
the game's dictionary table (yay self-fulfilling prophecies!).
3. Also, as implied by the prompt text, the quotation marks around the
"L" are important.
4. Lastly, `parse$` is stored as lowercase text, so you can see that our
uppercase "L" in the output did not fool it. Conversely, if
`StringDictCompare` was looking for an "L" from `parse$`, it'd never
recognize it, so keep that in mind if you are trying to match a string
written from `parse$` to a capitalized `object.name` property.

## Why The Previous Example Is A Bad Example

If we had asked the
player to *not* put the answer in quotes, we could have just had the line:

    if word[1] = "l"
         ....

Just checking for it automatically adds "l" to the dictionary table so
we can use the word array instead of [parse$](Parse$). Still,
the author hasn't replaced this page yet because he couldn't think of a
better example.
