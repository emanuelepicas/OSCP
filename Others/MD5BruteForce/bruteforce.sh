#!/bin/bash

echo "This is a sample program, which has the aim to demostrate the timing that can take trying to hashing a md5SUM, in this case the password is PASS.
On my enviroment the timing to find the password, iterating all combination with 4 character took 569 seconds"

alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
password=$( echo -n "PASS" | md5sum | awk '{ print $1 }')

start=$(date +%s)
for((i=0;i<${#alphabet};i++))
do

	for((j=0;j<${#alphabet};j++))
	do
		for((k=0;k<${#alphabet};k++))
		do
			for((x=0;x<${#alphabet};x++))
			do

				guess=${alphabet:i:1}${alphabet:j:1}${alphabet:k:1}${alphabet:x:1}
				hash=$(echo -n $guess | md5sum)
				hash=${hash%%\ *} #taking just the first field,component
				echo "$hash \= $password"
				if [ $hash = $password ]; then
					echo "Success the password gussed is $guess"
					break 4 #blocking all the four level of iteration
				fi
			done
		done
	done
done
end=$(date +%s)
echo The duration of the attack lasted $((end -start)) seconds 

