#include "def.h"
using namespace std;


bool isVerbose = true;
extern std::unordered_map<string, string> config;

int main(int argc, char const *argv[])
{
    readServerConfig();
    while(1)
    {
        cout<<CLI_PROMPT;
        char buffer[512];
        cin.getline(buffer, 511);
        commandParser(buffer);
    }
    return 0;
}
