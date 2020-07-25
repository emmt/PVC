#! /bin/sh
#
# tee.sh -
#
# Simple script to replace the `tee` command.
#
#---------------------------------------------------------------------------
#
# This file is part of PVC software released under the MIT "Expat" license.
#
# Copyright (c) 2020: Éric Thiébaut <https://github.com/emmt/PVC>
#

append="no"
while test $# -ge 1; do
    case "$1" in
        -h | --help )
            echo ""
            echo "Usage: $0 [OPTIONS] [--] DEST"
            echo ""
            echo "Read from standard input and write to standard output and to"
            echo "the file DEST.  Each line is printed as quickly as possible."
            echo ""
            echo "Options:"
            echo "    -a, --append    Append to the output file, do not overwrite."
            echo "    -h, --help      Print this help."
            echo ""
            exit 0
            ;;
        -a | --append )
            append="yes"
            shift
            ;;
        -- )
            shift
            break
            ;;
        * )
            break
            ;;
    esac
done

if test $# -ne 1; then
    echo >&2 "Usage: $0 [OPTIONS] [--] DEST"
    exit 1
fi
dest="$1"

# Change IFS variable to avoid that leading and trailing spaces be
# removed.
IFS=""

while read -r line; do
    echo "$line"
    if test "$append" = "no"; then
        echo "$line" >"$dest"
        append="yes"
    else
        echo "$line" >>"$dest"
    fi
done
