#include "def.h"

extern std::vector<servers*> serverList;

void printServers()
{
    for(int i=0;i<serverList.size();i++)
    {
        char buffer[256]={0};
        if(i==0)
        {
            sprintf(buffer,"%15s %15s %15s","IP ADDRESS", "CONN. STATE", "COMMAND RUN" );
            std::cout<<buffer<<std::endl;
        }            

        sprintf(buffer,"%15s %15s %15s",serverList[i]->ip, CONN_STATE_STR(serverList[i]->conn_state), serverList[i]->cmd );
        std::cout<<buffer<<std::endl;
    }
}