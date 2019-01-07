#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
#include<string>
#include<unordered_map>

#include "configuration.cpp"

bool isVerbose = false;


using namespace std;

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
