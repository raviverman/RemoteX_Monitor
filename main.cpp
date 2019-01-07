#include "def.h"
using namespace std;


bool isVerbose = false;
extern std::unordered_map<string, string> config;

int main(int argc, char const *argv[])
{
    // generateDefaultConfig();
    // isVerbose = true;
    loadConfig();
    unordered_map<string, string>::iterator it = config.begin();
    while(it!=config.end())
    {
        cout<<it->first.c_str()<<" "<<it->second.c_str()<<endl;
        it++;
    }
    return 0;
}
