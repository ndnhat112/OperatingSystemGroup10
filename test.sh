#!/bin/bash

if [ -z "$1" ]; then
    echo "Vui long cung cap dia chi dung den thu muc."
    exit 1
fi

directory=$1  # Nhan duong dan thu muc tu tham so dong lenh

zero_size_files=$(find "$directory" -type f -size 0)

# Kiem tra cac file 0KB
if [ -z "$zero_size_files" ]; then
    echo "Khong tim thay file nao co kich thuoc 0KB."
else
    echo "Cac file co kich thuoc 0KB trong thu muc $directory:"
    echo "$zero_size_files"
fi



# Vong lap xoa file ban mong muon
for file in $zero_size_files; do
    echo "File: $file"
 
    # goi chuong trinh C hien thi menu lua chon xoa file
    ./a.exe "Yes" "No"

    # lay gia tri tra ve tu chuong trinh
    answer=$?

    # Kiem tra gia tri tra ve 
    if [ "$answer" = "1" ]; then
        rm "$file"
        echo "$file deleted."
    else
        echo "$file kept."
    fi
done

