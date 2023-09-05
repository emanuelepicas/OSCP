#!/bin/bash

# Check if at least one argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <IP1> <IP2> <IP3> ..."
    exit 1
fi

# Loop through the provided IP addresses and run enum4linux for each
for ip in "$@"; do
    echo "Enumerating $ip"
    enum4linux "$ip" > $ip
    echo "----------------------------------"
done

