#include "def.h"
using namespace std;


bool isVerbose = false;
extern std::unordered_map<string, string> config;

int main(int argc, char const *argv[])
{
    // (\w+)\s+([\w -]+)\s+"(.*)"  
    char s[]= "192.168.137.7";
    if(addServer(s) < 0)
        cout<<"ADD FAILED";
    addServer("192.168.137.1");
    printServers();
    cout<<endl;
    connectServer(0);
    connectServer(1);
    printServers();

    return 0;
}
