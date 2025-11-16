Test applications with C and C++ (C/C++) just for fun! 



How to compile on windows with gcc the socket applications:

gcc udp_sender.c -o udp_sender -lws2_32 



To see the temp files, like assembly code and .o type:

gcc helloworld.c -o helloworld --save-temp ; ./helloworld.exe
