# Shell program to print all the days of a week and check if it is a weekday or weekend-
# Algorithm:

# 1. echo weekday: $i gets called every iteration
# 2. for loop yields an element every iteration to i variable.
# 3. i is not an array index, increment i after every iteration
# 4. Print weekday or weekend depending on value of i
# Code:
#!/bin/bash
for i in mon tue wed thurs fri sat
do
  if [ "$i" == "fri" ] || [ "$i" == "sat" ]
  then
    echo "weekend: $i"
  else
    echo "weekday: $i"
  fi
done
