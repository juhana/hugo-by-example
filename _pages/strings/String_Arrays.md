---
title: String arrays
permalink: /strings/string-arrays/
categories: 
  - Strings
---

String arrays are [arrays](/basics/array/) used for text
manipulation. Every character of a string is saved to an individual
array element. Once the end of the string is reached, an array element
is set to 0 to mark that the string is over.

## Declaring a string array

As an array, they are declared just the same:

## Writing to a string array

There are a couple ways to write to a string array.

1.  **Use the [string](/strings/string/) command.**
  There is a convenient `string` command for writing to string arrays!
  | `string` command component | description | example |
  |----------------------------|-------------|---------|
  | <array>  | the string array being written to | names_array  |
  | <dict> | the dictionary entry being changed to a string  | "apple",hobo.name, etc. |
  | parse$ | write the current value of [parse$](/parsing/parse$/)  | N/A |
  | <maxlen> | maximum number of letters to write to the string  | 10, 8, 255  |
  | x  | gets set to the length of the string written to <array> | N/A |
2.  **Use the [text to](/strings/text-to/) command.**

## Now what?

Now that you have the string array, you can use it with any 
[string routine](/strings/), like
[StringCopy](/strings/stringcopy/),
[StringPrint](/strings/stringprint/), or whatever.

## Keep in mind

Be careful to not erase the last element of a string array- the one that
equals 0- as that will result in a lot of trouble when printing it.
