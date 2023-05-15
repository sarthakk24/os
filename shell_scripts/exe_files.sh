#!/bin/bash

echo "Executable files in the present working directory:"

for file in *
do
  if [ -x "$file" ]; then
    echo "$file"
  fi
done
