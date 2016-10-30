#include "../include/Log.h"

Log* Log::game_log = new Log("out.log");

Log::Log()
{
    log_filename = "output.log";
    log_file.open(log_filename.c_str());

    log_to_console = false;
    log_to_file = false;
    log_to_gfx = false;
}

Log::Log(string filename)
{
    log_filename = filename;
    log_file.open(log_filename.c_str());

    log_to_console = false;
    log_to_file = false;
    log_to_gfx = false;
}

void Log::setFile(string f_name)
{
    if (log_file.is_open())
    {
        if (f_name == log_filename)
        {
            return;
        }

        log_file.close();
    }

    log_filename = f_name;
    log_file.open(log_filename.c_str());
}

void Log::pushError(string err)
{
    err = "[ERROR]::>" + err;

    if (log_to_console)
    {
        cout << err << endl;
    }

    if (log_to_file)
    {
        log_file << err << endl;
    }

}

void Log::pushLog(string log)
{
    log = "[LOG]::>" + log;

    if (log_to_console)
    {
        cout << log << endl;
    }

    if (log_to_file)
    {
        log_file << log << endl;
    }

    if (log_to_gfx)
    {

    }
}

Log::~Log()
{
    log_file.flush();
    log_file.close();
}
