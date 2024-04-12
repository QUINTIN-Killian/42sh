#!/bin/bash

if [ "$#" -eq 1 -a "$1" = "-h" ]; then
    echo -e "$0 [BIN] [FILE]"
    echo -e "\t[BIN] project binary"
    echo -e "\t[FILE] a file containing terminal commands on each line with a break at the end of the file"
    exit 0
fi

if [ "$#" -ne 2 ]; then
    echo "Error : incorrect number of arguments (it must be 2 but it is $#)."
    exit 84
fi

if [ ! -x "$1" ]; then
    echo "Error : first parameter must be an executable."
    exit 84
fi

if [ ! -f "$2" ]; then
    echo "Error : second parameter must be a file."
    exit 84
fi

passed=0
nb_tests=$(wc -l < "$2")
n=0

compare_results() {
    local cmd="$1"
    local res_mysh="$2"
    local res_tcsh="$3"
    local ret_mysh="$4"
    local ret_tcsh="$5"

    ((n+=1))

    echo -e "\e[33m[ Test n°$n - executing \"$cmd\" ]\e[0m"
    echo -e "\e[35mMYSH RESULT :\e[0m"
    echo -e "\e[34m$res_mysh\e[0m"
    echo -e "- return value :\n\e[34m$ret_mysh\e[0m"
    echo -e "\n\e[35mTCSH RESULT :\e[0m"
    echo -e "\e[34m$res_tcsh\e[0m"
    echo -e "- return value :\n\e[34m$ret_tcsh\e[0m"

    if [ "$res_mysh" != "$res_tcsh" -o "$ret_mysh" != "$ret_tcsh" ]; then
        echo -e "\n\e[31m>>> FAILURE\e[0m"
    else
        echo -e "\n\e[32m>>> SUCCESS\e[0m"
        ((passed+=1))
    fi
    echo -e "\n\n"
}

while IFS= read -r cmd; do
    res_mysh=$(echo "$cmd" | "./$1" 2>&1)
    ret_mysh="$?"
    res_tcsh=$(echo "$cmd" | tcsh 2>&1)
    ret_tcsh="$?"

    compare_results "$cmd" "$res_mysh" "$res_tcsh" "$ret_mysh" "$ret_tcsh"
done < "$2"

echo -e "\e[35mTOTAL : $passed/$nb_tests\e[0m"
