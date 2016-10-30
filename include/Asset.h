#ifndef ASSET_H
#define ASSET_H

/*Jeremy Gallant
  Class: Asset
  Usage: An abstract class to be used as
  a base for all Asset datatypes and to
  provide global searching, acces and loading of
  all types
*/

#include <string>
#include <map>

#include "Log.h"
#include "string_func.h"

using namespace std;

class Asset
{
    public:
        Asset();
        Asset(string n);
        virtual ~Asset();

        static int next_id;

        bool operator==(string &n_2) { return ((name==n_2) == 0); }
        bool operator!=(string &n_2) { return !(*this == n_2); }
        bool operator<(string &n_2) { return (name.compare(n_2) < 0); }
        bool operator>(string &n_2) { return (name.compare(n_2) > 0); }

        bool operator==(int &id_2) { return (id_2 == u_id); }
        bool operator!=(int &id_2) { return (u_id != id_2); }
        bool operator<(int &id_2) { return (u_id < id_2); }
        bool operator>(int &id_2) { return (u_id > id_2); }

        static map<string, Asset*> asset_bank;
        static map<int, string> id_table;
        static map<string, Asset*>::iterator asset_itr;
        static map<int, string>::iterator id_itr;

        static void add(Asset* a);
        static Asset* get(string n);
        static Asset* get(int id);

        static void remove(Asset* a);
        static void remove(string n);
        static void remove(int id);

        string Name() { return name; }
        void Name(string n) { name = n;}

        int uID() { return u_id;}

    protected:
    private:
        string name;
        int u_id;
        bool persistant;
};

#endif // ASSET_H
