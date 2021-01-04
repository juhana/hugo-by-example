---
title: FORMAT
permalink: /globals/format/
categories: 
  - Global Variables
---

The `FORMAT` [variable](Variables) is used to hold printing
format mask constants which determine several aspects of the game.

| Printing Format Mask Constant        | What It Does                                              |
|--------------------------------------|-----------------------------------------------------------|
| LIST_F                              | print itemized lists, not sentences                       |
| NORECURSE_F                         | do not recurse object contents                            |
| NOINDENT_F                          | do not indent listings                                    |
| [DESCFORM_F](DESCFORM_F) | alternate room description formatting                     |
| GROUPPLURALS_F                      | list plurals together where possible                      |
| NOPARENTHESES_F                     | ignore printing by ObjectIs (*is worn*, *is light*, etc.) |

    ! You set the FORMAT like this:
    FORMAT = LIST_F | NORECURSE_F | DESCFORM_F

    ! To add FORMAT settings to preexisting settings
    FORMAT = FORMAT | LIST_F

    ! To check for a FORMAT mask
    if(FORMAT & NORECURSE_F)

    ! To clear a FORMAT mask
    FORMAT = FORMAT & ~LIST_F
