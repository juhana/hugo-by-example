---
title: Grammar Tokens
permalink: /basics/grammar-tokens/
categories: 
  - Basics
---

There are many kinds of tokens we can use in our
[grammar](basics/grammar/) definitions. This page devotes some
attention to each one.

## Token List

#### `attribute`

| token       | applies to                            | common error message   |
|-------------|---------------------------------------|------------------------|
| `attribute` | any visible object that is attribute. | "You can't wear that." |

    verb "wear"
    * clothing                DoWear



#### `parent`

| token    | applies to                                  | common error message              |
|----------|---------------------------------------------|-----------------------------------|
| `parent` | an xobject that is the parent of the object | "You don't see \[object\] there." |

    verb "get"
        * object "from"/"off"/"on"/"in" parent                   DoGet



#### `held`

| token  | applies to                                | common error message       |
|--------|-------------------------------------------|----------------------------|
| `held` | any object possessed by the player object | "You're not holding that." |

    verb "put"
        * held "on" platform                   DoPutOn



#### `notheld`

| token     | applies to                    | common error message (if item is already held) |
|-----------|-------------------------------|------------------------------------------------|
| `notheld` | an object explicitly not held | "You don't see that."                          |

    ! This example does not represent the actual DoGet definition
    verb "get"
        * notheld                   DoGet



#### `anything`

| token      | applies to                              | common error message (if item isn't known)    |
|------------|-----------------------------------------|-----------------------------------------------|
| `anything` | any object, held or not, visible or not | "You haven't encountered anything like that." |

    verb "ask"
        * living "about" anything          DoAsk



#### `multi, multiheld, multinotheld`

| token                            | applies to                        | common error message |
|----------------------------------|-----------------------------------|----------------------|
| `multi, multiheld, multinotheld` | multiple objects (several or all) | none, really         |

    verb "get"
        * multi          DoGet



#### `number`

| token    | applies to                | common error message           |
|----------|---------------------------|--------------------------------|
| `number` | a positive integer number | "That doesn't make any sense." |

    verb "set"
        * object "to" number          DoSet



#### `word`

| token  | applies to          | common error message                                         |
|--------|---------------------|--------------------------------------------------------------|
| `word` | any dictionary word | "You don't need to use the word \[word not in dictionary\]." |

    verb "choose"
        * word          DoChooseColor



#### `string`

| token    | applies to      | common error message                                         |
|----------|-----------------|--------------------------------------------------------------|
| `string` | a quoted string | "You don't need to use the word \[word not in dictionary\]." |

    verb "scrawl"
        * string "in" object          DoScrawl


*Note: what the player enters in the quotes (&gt;SCRAWL "HUGO RULEZ" IN SAND) is sent to [`parse$`](parsing/parse$/)*


#### `(RoutineName)`

| token         | applies to                     |
|---------------|--------------------------------|
| `RoutineName` | a routine name, in parenthesis |

    verb "talk"
        * "to" (SpeakEnglish)          DoTalk
    ...
    routine SpeakEnglish(var)
    {
         if var is not living or var.language = "english"
               return true
         else
               print capital Art(var); " doesn't speak English!"
         return false
    }

This one is a bit more complicated than your average grammar token.

On the player's side of things, the parser will accept any known object,
like the
[anything]({{page.url}}#anything)
token. When the routine is executed, the parser hasn't yet determined
`object` and `xobject`. You must provide a variable (like "var" there)
that will be set to the object it is fed. If you have the routine return
true, it'll continue to process the command normally and run the regular
verb routine. If you have it return false, be sure to print an error
message or else nothing at all will be printed (of course, `main` will
not be called).

This is one of the least-used Hugo features. Currently, no shared-source
games use it, so how you want to use it is up to you.

#### `(objectname)`

| token          | applies to                           |
|----------------|--------------------------------------|
| `(objectname)` | a single object name, in parenthesis |

    verb "watch"
        * (television)          DoWatchTV

As the description implies, you can not use this feature towards object
classes, just single objects. It is useful when one object breaks the
verb grammar's defaults, but you do not want to rewrite the grammar or
verb routines. For instance, you have a window object that you want
players to be able to look into but don't want to make the window a
[container](basics/containers-and-platforms/).
