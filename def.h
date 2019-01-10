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
#include<vector>
#include<fcntl.h>

#define PROCESS_STOPPED 0
#define PROCESS_RUNNING 1
#define PROCESS_ERROR 2

#define R 0
#define W 1

#define ISALIVE(x) ((*x == 0))
typedef int** ping_t;

#define CONN_STATE_CON 0
#define CONN_STATE_DIS 1
#define CONN_STATE_NOT 2
#define CONN_STATE_ERR 3

#define CONN_STATE_STR(x) (x==0?"CONNECTED":(x==1?"DISCONNECT":(x==2?"NOTCONNECTED":"CONNECTIONERR")))

struct servers
{
    char ip[15];
    int conn_state;
    char cmd[255];
    int socket;
};

// Message types
#define MESS_EXEC_COMM 0
#define MESS_SEND_STAT 1

#define IP_REGEX "[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+"


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
int regexMatcher(const char* _string, const char* _regex);

//executer
// int executeCommandAsync(char* command);

// comms
// int startServer();
// void readMessage(char *buffer, message* m);
// void writeResponse(response* resp, char* buffer);
void* ping(void* ip);
int** pingGroup(char ip[][30], int n);
int addServer(char* ip);
int connectServer(int x);
int connectServer(char* ip);
// cli
void printServers();

