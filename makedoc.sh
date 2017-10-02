#!/bin/bash

rec() {
    for i in $(ls "$1" | sed 's/ /\//g')
    do
        NAME="$(echo "$i" | sed 's/\// /g')"
        echo "\\$2section{$NAME}"
        if [ -d "$1/$NAME" ]; then
            "rec" "$1/$NAME" "$2sub"
        else
            echo "\\lstinputlisting{\"$1/$NAME\"}"
        fi
    done
}

"rec" "$1" "$2"
