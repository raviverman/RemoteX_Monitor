#include "def.h"

extern std::vector<servers*> serverList;
extern bool isVerbose;


//Not so good way of implementing cli--Will update "soon"
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
    else if(regexMatcher(command, COMMAND_CLEAR))
    {
        system("clear");
    }
    else if(regexMatcher(command, COMMAND_EXIT))
    {
        printMessage("Exiting...");
        kill(getpid(), SIGINT);
    }
    else if(regexMatcher(command, COMMAND_CONNECT_REGEX))
    {
        std::regex reg(COMMAND_CONNECT_GROUP);
        std::smatch match;
        const std::string s = command;

        if(std::regex_search(s.begin(),s.end(), match, reg))
        {
            int sid = atoi(match[1].str().c_str());
            if(sid < serverList.size())
                connectServer(sid);
            else
                printMessage("No such server exists.");
        }
        else
            printMessage("FORMAT: connect <server_node> ",true);
    }
    else if(regexMatcher(command, COMMAND_HELP))
    {
        printHelp();
    }
    else
    {
        printMessage("Error : Command not found");
    }
}


void printServers()
{
    for(int i=0;i<serverList.size();i++)
    {
        char buffer[256]={0};
        if(i==0)
        {
            sprintf(buffer,"%3s %21s %15s %15s","ID", "IP ADDRESS", "CONN. STATE", "COMMAND RUN" );
            std::cout<<buffer<<std::endl;
        }            

        sprintf(buffer,"%3d %15s:%5d %15s %15s",i+1, serverList[i]->ip, serverList[i]->port, CONN_STATE_STR(serverList[i]->conn_state), serverList[i]->cmd );
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

void printHelp()
{
    std::cout<<std::setw(20)<<"connect : "<<"establish connection to server."<<std::endl;
    std::cout<<std::setw(20)<<"exec : "<<"execute command on server."<<std::endl;
    std::cout<<std::setw(20)<<"exit : "<<"Exit and terminate server."<<std::endl;

    std::cout<<std::setw(20)<<"clr : "<<"clear screen"<<std::endl;

    std::cout<<std::setw(20)<<"show : "<<"status - shows servers connection status."<<std::endl;
    std::cout<<std::setw(20)<<""<<"config - shows servers configs."<<std::endl;


}