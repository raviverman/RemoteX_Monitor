#include "def.h"

std::vector<servers*> serverList;

void* ping(void* args)
{
    const char* ip = ((char*)args);
    char cmd[256] = {0};
    sprintf(cmd, "ping -c 1 %s > /dev/null", ip);
    int* exitStatus =  ((int*)malloc(sizeof(int)));
    *exitStatus = WEXITSTATUS(system(cmd));
    return exitStatus;
}

int** pingGroup(char ip[][30], int n)
{
    pthread_t thread_id[n+1];
    int **exitStat = ((int**)malloc((n+1)* sizeof(int*)));
    for(int i=0;i<n;i++)
    {
        pthread_create(&thread_id[i], NULL, ping, &ip[i]);
    }
    for(int i=0;i<n;i++)
    {
        void* ret;
        pthread_join(thread_id[i], &ret);
        exitStat[i] = ((int*)ret);
    }
    return exitStat;
}

int connectServer(char* ip, int port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(4020);
    server.sin_family = PF_INET;

    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // int flags = fcntl(serverSocket, F_GETFL);
    // fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
    if(connect(serverSocket, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        return -1;
    }
    // successfully connected
    
    return serverSocket;
} 

int connectServer(int x)
{
    int ret;
    if((ret = connectServer(serverList[x]->ip, serverList[x]->port)) > 0)
        serverList[x]->conn_state = CONN_STATE_CON;
    else
        serverList[x]->conn_state = CONN_STATE_ERR;
    serverList[x]->socket = ret;
    return ret;
}

int addServer(const char ip[], int port)
{
    if(regexMatcher(ip, IP_REGEX)!=1)
        return -1;
    else
    {
        servers* s = ((servers*)malloc(sizeof(servers)));
        sprintf(s->ip,"%s", ip);
        s->port = port;
        s->conn_state = CONN_STATE_NOT;
        sprintf(s->cmd, "-");
        s->socket = -1;
        serverList.push_back(s);
    }
}

message* createMessage(int type, const char command[], bool isShellCmd, bool respond)
{
    message* m = ((message*)malloc(sizeof(message)));
    sprintf(m->command,"%s", command);
    m->isshellcmd = isShellCmd;
    m->respond = respond;
    m->type = type;
    return m;
}

int sendMessage(int serverNode, message* m)
{
    int _socket = serverList[serverNode]->socket;
    if(_socket < 0)
    {
        free(m);
        return -1;
    }
    // save last command run on server
    sprintf(serverList[serverNode]->cmd, "%s", m->command);
    char buffer[sizeof(message)];
    memcpy(buffer, m, sizeof(message));
    int s =  send(_socket, buffer, sizeof(message), 0);
    free(m);
    return s;
}