#!/bin/bash

pattern=$1

for file in *
do
  if [ -f "$file" ]; then
    if grep -q "$pattern" "$file"; then
      echo "$file: Pattern available"
    else
      echo "$file: Pattern not available"
    fi
  fi
done
