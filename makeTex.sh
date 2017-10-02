#!/bin/bash

rec() {
    for i in $(ls "$1" | sed 's/ /\//g')
    do
        NAME="$(echo "$i" | sed 's/\// /g')"
        if [ -d "$1/$NAME" ]; then
            echo "\\$2section{$NAME}"
            "rec" "$1/$NAME" "$2sub"
        else
            echo "\\$2section{$(echo -n "$NAME" | sed 's/.cpp$//')}"
            echo "\\lstinputlisting{\"$1/$NAME\"}"
        fi
    done
}

"rec" "$1" "$2"
