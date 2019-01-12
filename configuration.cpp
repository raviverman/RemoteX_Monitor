#include "def.h"

using namespace std;

const string configFile = CONFIG_FILE;
static bool defaultConfigLoaded = false;

extern bool isVerbose;

static FILE* file = NULL;  
unordered_map<string, string> defaultConfig;
unordered_map<string, string> config;

int validateFile(const char *fileName)
{
    file = fopen(fileName, "r");
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
    defaultConfigLoaded = true;
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
    printMessage("Loading Configuration..", true);
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


int readServerConfig()
{
    char str[512];
    printMessage("Loading Server details..", true);
    if(!validateFile(SERVERS_FILE))
    {
        printMessage("Server config not present <server.conf>.");
        return -1;   
    }
    ifstream ifile = ifstream(SERVERS_FILE);
    while(!ifile.eof())
    {
        ifile.getline(str, 256); 
        const string s = str;
        if(regexMatcher(str, IP_PORT_REGEX))
        {
            regex reg(IP_PORT_GROUP);
            smatch match;
            if(regex_search(s.begin(), s.end(), match, reg))
            {
                addServer(match[1].str().c_str(), atoi(match[2].str().c_str()));
            }
        }    
        else
        {
            printMessage("IP read fail");
        }    
    }
}

int loadConfig()
{
    loadDefaultConfig();
    if(!validateFile(CONFIG_FILE))
        return -1;
    parseConfig();
}

string getConfig(string configKey)
{
    if(config.count(configKey) <=0)
        {
            if(!defaultConfigLoaded)
                loadDefaultConfig();
            return defaultConfig[configKey];
        }
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