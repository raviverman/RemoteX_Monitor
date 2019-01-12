#include "def.h"

extern std::vector<servers*> serverList;
extern bool isVerbose;


//Not so good way of implementing cli--Will update soon
int commandParser(char command[])
{
    if(regexMatcher(command, COMMAND_EXEC_REGEX))
    {
        std::regex reg(COMMAND_EXEC_GROUP);
        std::smatch match;
        const std::string s = command;

        if(std::regex_search(s.begin(),s.end(), match, reg))
        {
            message *m = createMessage(MESS_EXEC_COMM, match[2].str().c_str(), true, false);
            sendMessage(atoi(match[1].str().c_str()), m);
        }
        else
            printMessage("FORMAT: exec <server_node> \"<command>\"",true);
    }
    else if(regexMatcher(command, COMMAND_SHOW_STATUS))
    {
        printServers();
    }
    else
    {
        printMessage("Command Error.");
    }
}


void printServers()
{
    for(int i=0;i<serverList.size();i++)
    {
        char buffer[256]={0};
        if(i==0)
        {
            sprintf(buffer,"%21s %15s %15s","IP ADDRESS", "CONN. STATE", "COMMAND RUN" );
            std::cout<<buffer<<std::endl;
        }            

        sprintf(buffer,"%15s:%5d %15s %15s",serverList[i]->ip, serverList[i]->port, CONN_STATE_STR(serverList[i]->conn_state), serverList[i]->cmd );
        std::cout<<buffer<<std::endl;
    }
}

void printMessage(char* message, bool onVerbose)
{
    if(isVerbose || onVerbose)
    {
        std::cout<<message<<std::endl;
    }
}