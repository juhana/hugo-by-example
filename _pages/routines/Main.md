---
title: main
permalink: /routines/main/
categories: 
  - Routines
---

`main` is the routine that is called every turn after a successful verb
routine (not an "xverb" like `SAVE` or a "You can't go that way."
message). Let's look at the `main` routine from the 
"[New Shell](New_Shell)" page:

```
routine main
{
        counter = counter + 1
        PrintStatusLine
        run location.each_turn
        runevents
        RunScripts
        if speaking not in location
                speaking = 0
}
```

Line by line:

-   **Line 3** Increase the turn counter by 1, using the [global
    variable](Variables#Global_Variable) `counter`
-   **Line 4** Refresh the status line
-   **Lines 5** Run the current location's
    [each_turn](Each_turn)
    [property](Properties), if any exist
-   **Line 6** Run any [events](Events) that are in scope
-   **Line 7** Run any [character scripts](Scripts) that
    exist
-   **Lines 8-9** If the player is no longer in the same room as the
    character he or she was talking to, clear the `speaking` [global
    variable](Variables#Global_Variable)

In a multi-[window](Window) game with
[graphics](Resources), you'd want to call your
"DrawGraphicWindows" routine in the `main` routine. And so on.
