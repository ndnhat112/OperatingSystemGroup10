#!/bin/bash

declare -a empty_files

if [ ! -e menu ]
then
    gcc -o menu menu.c
fi

delete_confirmation() 
{
    local item="$1"
    
    echo "Xoa file $item ?"
    ./menu 
    declare -i choice="$?"

    if [ "$choice" -eq 1 ]
    then
        rm $item
        echo "Da xoa!"
    fi

    echo "Nhap phim bat ki de thoat!"
    read esc
    clear
}

check_empty() 
{
    local dir="$1"

    for item in "$dir"/*
    do  
        if [ -d "$item" ]
        then
            check_empty "$item"
        elif [ -f "$item" ]
        then
            if [ ! -s "$item" ]
            then
                empty_files+=("$item")
            fi
        fi
    done
}

delete_empty() 
{
    check_empty "$1"

    empty_files_size=${#empty_files[@]}
    if [ "$empty_files_size" -eq 0 ]
    then 
        echo "Khong co file rong trong thu muc: $1"
    else
        echo "File rong trong thu muc: $1: "

        for i in "${!empty_files[@]}"
        do
            echo ${empty_files[i]}
        done

        for i in "${!empty_files[@]}"
        do
            delete_confirmation ${empty_files[i]} 
        done
    fi
}

delete_empty "$1"