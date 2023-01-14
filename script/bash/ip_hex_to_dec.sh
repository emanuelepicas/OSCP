#!/bin/bash
#You can conver an ip address in hex that you can find in this path of a server: 
# /proc/net/route 
#pass the hex as a parameter 1+ 

for addr
do
	echo -n $((16#${addr:6:2})).$((16#${addr:4:2})).$((16#${addr:2:2})).$((16#${addr:0:2}))
	echo -n " "
done
echo
