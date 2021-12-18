!bash 

gcc -I/usr/local/include ./server.c -lfcgi -o fcgi-server.cgi
cgi-fcgi -start -connect 127.0.0.1:49223 ./fcgi-server.cgi