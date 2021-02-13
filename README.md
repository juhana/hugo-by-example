# Adding content

## Formatting

### Line length

Note that you don't need to split long lines into shorter ones. The many manual line breaks inside paragraphs is an artifact of the Wiki conversion.

### Less than / greater than

Use `&lt;` for &lt; characters and `&gt;` for &gt; characters, otherwise the formatting engine can mistake them for HTML tags.

Example:

    &gt;give &lt;object&gt; to &lt;person&gt;

Output:

>&gt;give &lt;object&gt; to &lt;person&gt;

<!-- the above only makes sense when viewed as rendered Markdown -->

### Code blocks inside lists

If you're making code blocks by indenting the code with 4 spaces, you need an empty HTML comment (`<!-- -->`) between the list item and the code. Otherwise the code is considered normal text and part of the previous list item.

    * Blah blah
    * Blah blah blah

    <!-- -->

        if(true)
        {
            this.codeblock is formatted.correctly()
        }


## Page metadata

Add page metadata at the start of the .md file:

    ---
    title: Page Title
    permalink: /url/to/page/
    categories: 
    - One
    - Two
    - Three
    ---

Remember to add both leading and trailing `/` to the URL.

Escape special characters with a backslash, e.g.

    title: \#include


## Images

Add image files to the assets/images directory and display them with

`![Description](assets/images/filename.jpg)`


## Transcript examples

Use `>` to make it a blockquote. Add two spaces at the end of a line to force a line break.

    >Location title  (<-- two spaces at the end)
    >Example room description.
    >
    >&gt;x me


## New categories

Add the new category to _pages/category-archive.md with the following format:

    ## Name

    Description of the category.

    {% include category.md name="Name" %}

(where `Name` is the name of the new category)


## Table of Contents

If you want to show an internal table of contents in a long article, add the following lines to the page's header:

    toc: true
    toc_label: Title shown on the TOC

See the [Category Index](_pages/category-archive.md) for an example.


## Hidden spoilers

    <details>
    <summary>Show answer</summary>
    Bruce Willis was Luke's father the whole time
    </details>


## Page anchor links

For internal links to page chapters you need to include `{{page.url}}` at the start of the link:

    [link label]({{page.url}}#headerID)

The header id is the header text in lowercase, non-alphanumeric characters removed, spaces replaced with dashes ("My Header" -> "#my-header")


## Wide pages

To make a page wider, add this to the header:

    classes: wide

Note that if the page has a table of contents it'll be shown at the start of the page.


# Development tools

## Local server

If you want to see how the pages look on your own computer before committing changes to the actual web site, install [Jekyll](https://jekyllrb.com) and run:

```
bundle exec jekyll serve --livereload --incremental
```

See https://docs.github.com/en/github/working-with-github-pages/testing-your-github-pages-site-locally-with-jekyll


## Checking for broken links

While the local server is running:

```
npx broken-link-checker http://localhost:4000 -ro --exclude="ifdb"
```
