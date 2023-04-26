# Shell program to check if the file is executable or not-
# Algorithm:

# 1. Enter the filename
# 2. Read the filename
# 3. Check if the file has “-x” permission
# 4. If yes, print “file is executable”
# 5. Else, print “file is not executable”
# Code:
#!/bin/bash
read file
if [[ -x "$file" ]]
then
  echo "file '$file' is executable"
else
  echo "file '$file' is not executable"
fi
