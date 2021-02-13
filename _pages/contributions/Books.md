---
title: Books.hug
permalink: /contributions/books.hug/
categories: 
  - Classes
  - Library Contributions
---

    !\--------------------------------------------------------------------------->

        books.hug

        A book object class with support routines.

        DoConsult - >READ BOOK ABOUT THING
        DoReadAbout -   >READ ABOUT THING IN BOOK

    ---------------------------------------------------------------------------\!

`Books.hug` is Kent Tessman's `ob_book.hug` file from the Future Boy!
Selected Source release with a few changes (the name was changed, some
lines were commented out, and a necessary routine from `misc.hug` was
added). As such, it adheres to 
[its license](misc/future-boy-license/). You can
download it [here](https://github.com/hugoif/library-contributions/blob/main/books.hug).

## Book Example

Beyond adding the contents of `books.hug` and its grammar to your code,
you can then code books like this:

    book bigbook "big book about you"
    {
        noun "book" "you"
        adjective "big" "about"
        after
            {
            object DoConsult
                {
                select xobject
                    case you
                        {
                        "You find an article saying you are the greatest!"
                        }
                    case else
                        return false
                }
            }
        in STARTLOCATION
    }

Well, hopefully your books are better.
