const { resolve, basename } = require('path');
const { readdir, readFile, writeFile } = require('fs').promises;

// from https://stackoverflow.com/a/45130990
async function* getFiles(dir) {
    const dirents = await readdir(dir, { withFileTypes: true });
    for (const dirent of dirents) {
        const res = resolve(dir, dirent.name);
        if (dirent.isDirectory()) {
            yield* getFiles(res);
        } else {
            yield res;
        }
    }
}

const replacements = {
    attribute: "/attributes/",
    standard_library: "/library/",
    hugo_library: "/library/",
    supercontainer: "/contributions/contain.h/",
    property: "/properties/",
    long_desc: "/properties/descriptions/",
    short_desc: "/properties/descriptions/",
    when_open: "/properties/descriptions/",
    when_closed: "/properties/descriptions/",
    declaration: "/declarations/",
    routine: "/routines/",
    books: "/contributions/books.hug/",
    string_array: "/strings/string-arrays/",
    beta: "/betatesting/",
    arrays: "/basics/array/",
    event: "/timers/events/",
    initial_desc: "/properties/descriptions/",
    character_scripts: "/characters/scripts/",
    new_shell: "/basics/new-shell/",
    arguments: "/definitions/argument",
    display: "/guts/display-object/",
    pronouns: "/properties/pronoun/",
    vehicles: "/classes/vehicle/",
    containers: "/basics/containers-and-platforms/",
    platforms: "/basics/containers-and-platforms/",
    inherit: "/guts/inherits/",
    globals: "/basics/global/",
    verb_grammar: "/basics/grammar/",
    verb_routine: "/verb-routines/",
    operator: "/operators/",
    transcripts: "/definitions/transcript/",
    local: "/basics/locals/",
    constant: "/basics/constants/",
    room: "/basics/rooms/",
    door: "/classes/doors/",
    parameters: "/definitions/parameter/"
};

(async () => {
    const articles = [];
    const missing = new Set();

    // Pass 1: collect article URLs
    for await (const f of getFiles("../_pages/")) {
        const file = await readFile( f, { encoding: "utf-8" });
        const lines = file.split("\n");
        articles.push({
            title: lines[1].substr( "Title: ".length ).toLowerCase(),
            url: lines[2].substr( "Permalink: ".length ),
        });
    }
    
    // Pass 2: find and fix internal links
    for await (const f of getFiles("../_pages/")) {
        const file = await readFile( f, { encoding: "utf-8" });
        const linkRegex = /\[(.+?)\]\((.*?)\)/gm;
        let link;
        let newFile = file;

        while( link = linkRegex.exec( file ) ) {
            let [ whole, label, url ] = link;

            url = url.toLowerCase();

            const hash = url.indexOf('#');

            if(hash > -1) {
                url = url.substr(0, url.indexOf('#'));
            }

            if(!url) {
                // skip internal links
                continue;
            }

            if(url.indexOf( "http" ) === 0) {
                // skip external links
                continue;
            }

            if(url.indexOf( "/assets/" ) === 0) {
                // skip assets
                continue;
            }

            if(url.indexOf( "/categories/" ) === 0) {
                // skip category page
                continue;
            } 

            if( articles.some( article => article.url === url ) ) {
                // already ok
                continue;
            }

            const newArticle = articles.find( article => article.title === url || article.title.replaceAll( " ", "_" ) === url );

            if( newArticle ) {
                // change to correct url
                newFile = newFile.replaceAll( whole, `[${label}](${newArticle.url})` );
                continue;
            }

            if( replacements[ url ] ) {
                newFile = newFile.replaceAll( whole, `[${label}](${replacements[ url ]})` );
                continue;
            }

            console.log(url)
            // can't fix automatically, show what needs to be checked separately
            missing.add( basename( f ) );
        }

        if( newFile !== file ) {
            await writeFile( f, newFile, "utf8" );
        }
    }

    console.log( missing, missing.size );

    console.log('\nDone.');
})()