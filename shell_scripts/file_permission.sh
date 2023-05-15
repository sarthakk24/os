#!/bin/bash

echo "Enter the file name: "
read file

if [ -w "$file" ]; then
  echo "File has write permission."
else
  chmod +w "$file"
  echo "Write permission added to the file."
fi
