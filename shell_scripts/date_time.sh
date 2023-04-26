# Shell program to check the time and output good morning, good afternoon,
# Algorithm:

# 12

# 1. Create a variable named hour
# 2. Store the current date and time in it using $(date +"%H")
# 3. If the time value lies between 6 to 12, print “good morning”
# 4. If the time value lies between 12 to 16, print “good afternoon”
# 5. If the time value lies between 16 to 20, print “good evening”
# Code:
h=$(date +"%H")
if [ $h -gt 6 -a $h -le 12 ]
then
    echo "good morning"
elif [ $h -gt 12 -a $h -le 16 ]
then
    echo "good afternoon"
elif [ $h -gt 16 -a $h -le 20 ]
then
    echo "good evening"
else
    echo "good night"
fi
