#include<string>
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<unistd.h>
#include<cstdio>
#include<regex>

#include<wait.h>
#include<stdlib.h>
#include<pthread.h>
#include<queue>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unordered_map>

#define PROCESS_STOPPED 0
#define PROCESS_RUNNING 1
#define PROCESS_ERROR 2

#define R 0
#define W 1

struct process
{
    int pid;
    char* command;
    int exit_status;
    int state;

    // add exec time
};

struct monitor_info
{
    struct sockaddr_in monitor; 
    int socket;
};

// Message types
#define MESS_EXEC_COMM 0
#define MESS_SEND_STAT 1

struct message
{
    int type;
    char command[256];
    bool isshellcmd;
    bool respond;
};

struct response
{
    bool isSuccess;
    char error[256];
    char resp[256];
    bool isComplete;
    bool hasNext;
};

//configuration
int loadDefaultConfig();
int loadConfig();
std::string getConfig(std::string configKey);

//executer
// int executeCommandAsync(char* command);

// comms
// int startServer();
// void readMessage(char *buffer, message* m);
// void writeResponse(response* resp, char* buffer);
