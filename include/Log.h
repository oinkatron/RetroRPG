#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class Log
{
    public:
        Log();
        Log(string filename);
        virtual ~Log();

        void logToFile(bool val) { log_to_file = val; }
        void logToConsole(bool val) { log_to_console = val; }

        void pushError(string err);
        void pushLog(string log);

        void setFile(string f_name);

        static Log *game_log;

    protected:
    private:
        string log_filename;
        ofstream log_file;

        bool log_to_file;
        bool log_to_console;
        bool log_to_gfx;
};

#endif // LOG_H
