# Client-Server-Chat-App

## Introduction
A simple client server chat application using socket programming which has support for multiple clients upto 10 Clients which can be easily increased but is limited by the harware.

A network protocol is a set of rules that defines how data is transmitted among devices in same network. We here discuss two of the important network protocols, namely - TCP (Transmission Control Protocol). 
TCP is a connection oriented protocol ( a connection must be established between the devices before the start of communication (the 3 way handshake) and must close after it is completed) while this is not the case with UDP. Due to this feature as well as it's error checking and acknowledging mechanisms , TCP is more reliable than UDP.

## Tech Stack used

- Socket Programming
- Coded in C++
- Operating System: Linux
- Pthread Library

## How To Run

Make sure you have G++ compiler installed.

Step 1. Download the source code to system in zip format or clone repo.
```
git clone https://github.com/pragyad3188/Client-Server-Chat-App.git
``` 
Step 2. On linux shell navigate to the folder 
```
cd Client-Server-Chat-App
```
Step 3. Compile the server code as:-
```
g++ -o server.bin  Server.cpp -pthread
```
Step 4. Run the server code with by specifying the port number in the argument
```
./server.bin 2000
```
Step 5.Compile the Client code as:-
```
g++ -o client.bin  Client.cpp -pthread
``` 
Step 6.Now open many terminals such that each will act  as a client. I have opened 3 Clients.Type the following command in each client terminal 
```
./client.bin 127.0.0.1 2000
```
We have to specify the Ip and port number of the server we are trying tto connect.

Now you can chat through all the clients.
Note:- When a message is sent from a client pls respond immediately through the server and then other Clients.

## New Features

1. Support for multiple Clients has been added using Multi threading.

## Working Demo
- The working of the Chat app with Three clients connected to one server is shown in the figure
  
![Image 1](/image1.png)
## Future Goals

- Support for UDP protocol with multi client can be done 
- Better implemenet the multi client interface by fixing some issues occuring in multi-threading. 