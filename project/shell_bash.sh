#!/bin/bash
if [ "$1" = "-s" ]
then
    if [[ `find /home -iname "$2"` ]]
    then
    echo "`find /home -iname "$2"`"
    echo "$1"
    else
    echo "file not found"
    fi
elif [ "$1" = "-h" ]
then
  val1="$2""$3"
  val2="$2"".$3"
 echo `mv "$val1" "$val2"`
 echo "successfully hide"
elif [ "$1" = "-uh" ]
then
  val1="$2""$3"
  val2="$2"".$3"
 echo `mv "$val2" "$val1"`
 echo "successfully unhide"
fi
