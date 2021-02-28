#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include<bits/stdc++.h>
using namespace std;

struct thread_info
{
	int sockID;
	int id;
};


//----------------------------------------------------------------------------------------------------------------------------
//
//                                                         NEW CLIENT THREAD EXECUTED HERE
//
//----------------------------------------------------------------------------------------------------------------------------


void* client_thread(void *arg)
{
	char* message =(char*) malloc(sizeof(char)*100);
	char* dataSend=(char*) malloc(sizeof(char)*100);
	memset(message, '\0', sizeof(char)*100);
	memset(dataSend, '\0', sizeof(char)*100);

	thread_info get_info = *((thread_info *) arg);
	int newSocketID = get_info.sockID;
	int thread_id = get_info.id;
	if(newSocketID < 0)
	{
		cerr << "Not successful accept()\n";
		pthread_exit(NULL);
	}
	cout<<"Client connected successfully\n";
	
	while(1)
	{
		recv(newSocketID, message, sizeof(char)*100, 0);
		if(strcmp(message, "exit")==0)
		{
			cout<<"Session terminated";
		}
		cout<<"Client "<<thread_id<<": "<<message<<"\n";	
		memset(message, '\0', sizeof(char)*100);
		

		cout<<"Server "<<thread_id<<": ";
		string data;
		getline(cin, data);
		strcpy(dataSend, data.c_str());;
		if(data == "exit")
		{
			cout<<"Client Session terminated";
			break;
		}
		send(newSocketID, dataSend,data.length() , 0);
		memset(dataSend, '\0', sizeof(char)*100);
	}
	close(newSocketID);
	free(message);
	free(dataSend);
	pthread_exit(NULL);
}

//---------------------------------------------------------------------------------------------------------------------------
//
//                                                                 MAIN FUNCTION
//
//----------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		cerr << "Missing port number\n";
		exit(0);
	}
	int port = atoi(argv[1]);

	//define a sockaddr_in struct for server socket (the socket listening)
	sockaddr_in serverSocket;
	bzero((char *)&serverSocket, sizeof(serverSocket));
	serverSocket.sin_family = AF_INET;
	serverSocket.sin_port = htons(port);
	serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

	int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSocketID < 0)
	{
		cerr << "Not successful socket()\n";
		exit(0);
	}

	int bindStatus = bind(serverSocketID, (struct sockaddr *) &serverSocket, sizeof(serverSocket));
        if(bindStatus < 0)
	{
		cerr << "Not successful bind\n";
		exit(0);
	}	
	cout<<"Waiting for client to connect...\n";

	listen(serverSocketID, 2);


	sockaddr_in newSocket;
	socklen_t newSocketLen = sizeof(newSocket);	
	pthread_t threadID[10];	
	int i = 0;
	while(1)
	{
		int newSocketID = accept(serverSocketID, (sockaddr *) &newSocket, &newSocketLen);
		thread_info to_new_thread;
		to_new_thread.sockID = newSocketID;
		to_new_thread.id = i + 1;

		//CREATING A NEW THREAD HERE
		pthread_create(&threadID[i++], NULL, client_thread, &to_new_thread);	
	}
	close(serverSocketID);
}
