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

int connectServer(char* ip)
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
    if((ret = connectServer(serverList[x]->ip)) > 0)
        serverList[x]->conn_state = CONN_STATE_CON;
    else
        serverList[x]->conn_state = CONN_STATE_ERR;
    return ret;
}

int addServer(char ip[])
{
    if(regexMatcher(ip, IP_REGEX)!=1)
        return -1;
    else
    {
        servers* s = ((servers*)malloc(sizeof(servers)));
        sprintf(s->ip,"%s", ip);
        s->conn_state = CONN_STATE_NOT;
        sprintf(s->cmd, "-");
        s->socket = -1;
        serverList.push_back(s);
    }
}