#!/usr/bin/env bash
#
#   compiledb-generator: Tool for generating LLVM Compilation Database
#   files for make-based build systems.
#
#   Copyright (c) 2017 Nick Diego Yamane <nick.diego@gmail.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
set -e

scriptdir=$(cd "$(dirname "$0")" && pwd)
parser_cmd=${scriptdir}/compiledb-gen-parser.py

show_help() {
    cat << EOF

usage: compiledb-gen-make [-h] [-v] [-f] [MAKE_ARGS] -- [PARSER_ARGS]

 Generates compilation database file for an arbitrary make-based directory.
 Acts like a make wrapper, forwarding all MAKE_ARGS to make and PARSER_ARGS
 compiledb-gen-parser

arguments:
  MAKE_ARGS                make arguments (e.g: -j4, all, target_x, etc..)
  PARSER_ARGS              compiledb-gen-parser args (e.g: -o abc.json, -v, etc..)

optional arguments:
  -h, --help            show this help message and exit
  -v, --verbose         Show output from build process

EOF
}

declare -a make_opts parser_opts
is_make_arg=1
while (( $# )); do
    case $1 in
        -h | --help)
            show_help
            exit 0;;
        --)
            is_make_arg=0
            ;;
        *)
            (( is_make_arg )) && make_opts+=( "$1" ) \
                || parser_opts+=( "$1" )
            ;;
    esac
    shift
done

make -Bnkw "${make_opts[@]}" | $parser_cmd "${parser_opts[@]}"

# ex: ts=1 sw=4 et filetype=sh
