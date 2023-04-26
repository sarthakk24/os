# Algorithm:
# 1. Enter the directory you want to search
# 2. Use a for loop with a variable i to iterate through the directory files
# 3. Increment the value of i after each iteration
# 4. Use ‘echo $i’ command to print the name of the file
# Code:
#!/bin/bash
for i in *
do 
  echo "$i"
done
