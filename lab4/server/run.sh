#!/bin/bash

echo "Starting compilation..."
gcc -I/usr/local/include ./server.c -lfcgi -o server.cgi
echo "Server starting..."
cgi-fcgi -start -connect 127.0.0.1:49223 ./server.cgi
