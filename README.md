*This project has been created as part of the 42 curriculum by Halbit.*

# minitalk

# Description
minitalk is a client-server communication program from the 42 curriculum.  
The program transmits a string from a client to a server using only UNIX signals (`SIGUSR1` and `SIGUSR2`).

Each character is sent bit by bit, reconstructed on the server side, and displayed once the complete message is received.

# Instructions
```bash
make
Execution:

bash
Copy code
./server
./client <server_pid> "Hello World"
# Resources
42 subject PDF: minitalk
UNIX manual pages (signal, sigaction, kill, getpid, pause)
POSIX documentation on async-signal-safe functions
General documentation on bitwise operations in C

# Use of AI
AI tools were used to understand signal handling, bitwise communication, and synchronization between processes.

