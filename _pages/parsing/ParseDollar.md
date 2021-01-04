---
title: Parse$
permalink: /parsing/parse$/
categories: 
  - Parsing
  - Strings
---

Definition from the manual:

> Read-only engine variable that contains either the offending portion of an invalid input line or any section of the input line enclosed in quotes.

In any given input line, `parse$` can be several different things. If
every word in the input line is an understood dictionary entry, parse$
is set to "" (Note: "" does *not* equal 0). If the input line has no
quoted text but some words (or numbers) are not in the dictionary table,
`parse$` is set to the last not-understood word.

In a somewhat confusing third scenario:

    verb "say"
    * string             DoSay

    ...

    routine DoSay
    {
            print "parse$ = ";
            print parse$
    }

That gives us:

>&gt;say "yohoho and a bottle of rum"  
>parse$ = yohoho and a bottle of rum

What is confusing is that while DoSay understands `parse$` as "yohoho
and a bottle of rum", parser monitoring (see
HugoFix) will show that the engine still
understands `parse$` as "". This is because the current version of the
Hugo library's parser monitoring accidentally prints `parse$` *before*
parsing, so it hasn't been set yet. See "[Replace Parse](replacements/parse/)"
and "[Replace ParseError](replacements/parseerror/)".

### Pages with parse$

Since `parse$` can be used so many different ways, we'll just point you
to entries with examples that use it:
[Comments In Transcripts](tips/comments-in-transcripts/) uses
`parse$` to determine if the first character of the input line is an
asterisk.
[StringToNumber (routine)](strings/stringtonumber/) uses `parse$` for
entering numbers.
[StringDictCompare](strings/stringdictcompare/) uses it to write
quoted text to a string.
[dict (routine)](strings/dict/) will show how to use `parse$` to name
objects in-game (like the Beyond Zork naming mechanic).

### `parse$` in parser messages

`parse$` gets set to interesting things in error messages. Their
specific behavior is good to know, especially when writing new error
messages.

| ParseError Number | When Called                                               | parse$ value                  |
|-------------------|-----------------------------------------------------------|-------------------------------|
| 1                 | Not-understood word in input                              | First misunderstood word      |
| 3                 | Tried to use ALL with a verb that doesn't support it      | Set to the verb word          |
| 5                 | Player's command didn't match any object but all words are in the dictionary | Object, as it was referred to |
| 9                 | No objects available to <verb>                            | Set to the verb word          |
| 10                | Object isn't known.                                       | Object, as it was referred to |
| 11                | Known object not in current location                      | Object, as it was referred to |
| 12                | Can't do something (like, talking to a non-living object) | Object, as it was referred to |
