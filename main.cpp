#include "def.h"
using namespace std;


bool isVerbose = true;
extern std::unordered_map<string, string> config;

int main(int argc, char const *argv[])
{
    // // (\w+)\s+([\w -]+)\s+"(.*)"  
    // char s[]= "127.0.0.1";
    readServerConfig();
    // // if(addServer(s, 4020) < 0)
    // //     cout<<"ADD FAILED";
    // // addServer("192.168.137.1", 4020);
    // // printServers();
    // // cout<<endl;
    // printServers();
    connectServer(0);
    // // connectServer(1);

    // message *m = createMessage(MESS_EXEC_COMM, "sudo apt update", true, false);
    // sendMessage(0, m);
    // printServers();
    
    while(1)
    {
        cout<<CLI_PROMPT;
        char buffer[512];
        cin.getline(buffer, 511);
        commandParser(buffer);
    }
    return 0;
}
