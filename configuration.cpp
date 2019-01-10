#include "def.h"

using namespace std;

const string configFile = "configuration.conf";

extern bool isVerbose;

static FILE* file = NULL;  
unordered_map<string, string> defaultConfig;
unordered_map<string, string> config;

int validateFile()
{
    file = fopen(configFile.c_str(), "r");
    if(file != NULL )
        return true;
    return false;
}

int loadDefaultConfig()
{
    defaultConfig.insert({"ROOT","./"});
    defaultConfig.insert({"PROG","echo"});
    defaultConfig.insert({"ARGS","NO PROGRAM"});
    defaultConfig.insert({"TICK","5"});

}

int validateKey(string key)
{
    return defaultConfig.count(key);
}
/**
 * Configuration options (must be specified in default options)
 * ROOT=""
 * PROG=""
 * ARGS=""
 * TICK=""
 * */
int parseConfig()
{
    char str[512];
    ifstream ifile = ifstream(configFile);
    while(!ifile.eof())
    {
        ifile.getline(str, 256); 
        const string s = str;
        // FORMAT : key="value"
        regex rgx("\\s*(\\w+)\\s*=\\s*\"(.*)\"");

        smatch match;
        if (regex_search(s.begin(), s.end(), match, rgx))
            if(validateKey(match[1]))
                config.insert({match[1], match[2]});
            else if(isVerbose)
                cout<<"Invalid Key : "<<match[1]<<endl;
        
    }
}

int loadConfig()
{
    if(defaultConfig.size() < 4)
        loadDefaultConfig();
    if(!validateFile())
        return -1;
    parseConfig();
}

string getConfig(string configKey)
{
    if(config.count(configKey) <=0)
        return defaultConfig[configKey];
    else
        return config[configKey];
}

int generateDefaultConfig()
{
    loadDefaultConfig();
    ofstream ofile = ofstream(configFile, ios::out | ios::trunc);

    unordered_map<string, string>::iterator it = defaultConfig.begin();
    while(it!=defaultConfig.end())
    {
        // fprintf(file, "%s=\"%s\"\n", it->first, it->second);
        ofile<<it->first<<"=\""<<it->second<<"\""<<endl;
        it++;
    }
    ofile.close();
}

int regexMatcher(const char* _string, const char* _regex)
{
    return regex_match(_string, regex(_regex));
}