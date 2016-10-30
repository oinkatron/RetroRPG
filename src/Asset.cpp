#include "../include/Asset.h"

map<string, Asset*> Asset::asset_bank;
map<int, string> Asset::id_table;
map<string, Asset*>::iterator Asset::asset_itr;
map<int, string>::iterator Asset::id_itr;
int Asset::next_id = 0;

Asset::Asset()
{
    u_id = next_id++;
    name = "Asset_" + toString(u_id);
    persistant = false;

}

Asset::Asset(string n)
{
    name = n;
    u_id = next_id++;
}

Asset::~Asset()
{

}

void Asset::add(Asset *a)
{
    //Log::game_log->pushLog("Added asset with id: " + toString(a->uID()));
    asset_bank.insert(pair<string, Asset*>(a->Name(), a));
}

Asset* Asset::get(string n)
{
    asset_itr = asset_bank.find(n);
    if (asset_itr == asset_bank.end())
    {
        Log::game_log->pushError("Could not find Asset: " + n);
        return NULL;
    }

    return asset_itr->second;
}

Asset* Asset::get(int id)
{
    id_itr = id_table.find(id);
    if (id_itr == id_table.end())
    {
        Log::game_log->pushError("Could not find Asset with ID: " + toString(id));
        return NULL;
    }

    asset_itr = asset_bank.find(id_itr->second);
    if (asset_itr == asset_bank.end())
    {
        Log::game_log->pushError("Could not find Asset: " + id_itr->second);
        return NULL;
    }

    return asset_itr->second;
}

void Asset::remove(Asset* a)
{
    for (asset_itr = asset_bank.begin(); asset_itr != asset_bank.end(); asset_itr++)
    {
        if (asset_itr->second == a && !a->persistant)
        {
            id_itr = id_table.find(a->u_id);
            if (id_itr != id_table.end())
            {
                id_table.erase(id_itr);
            }
            asset_bank.erase(asset_itr);

            return;
        }
    }

    Log::game_log->pushError("Could not find object with that ref");
    return;
}

void Asset::remove(string n)
{
    asset_itr = asset_bank.find(n);
    if (asset_itr == asset_bank.end())
    {
        Log::game_log->pushError("Could not find Asset: " + n + " could not delete");
        return;
    }
    else if (asset_itr->second->persistant)
    {
        Log::game_log->pushError("Cannot remove persistant Asset: " + n);
        return;
    }

    id_itr = id_table.find(asset_itr->second->u_id);
    if (id_itr != id_table.end())
    {
        id_table.erase(id_itr);
    }

    delete asset_itr->second;
    asset_bank.erase(asset_itr);
}

void Asset::remove(int id)
{
    id_itr = id_table.find(id);
    if (id_itr == id_table.end())
    {
        Log::game_log->pushError("Could not find Asset with ID: " + toString(id) + " could not delete");
        return;
    }

    asset_itr = asset_bank.find(id_itr->second);
    if (asset_itr == asset_bank.end())
    {
        Log::game_log->pushError("Could not find Asset with Name: " + id_itr->second + " could not delete");
        id_table.erase(id_itr);
        return;
    }

    if (asset_itr->second->persistant)
    {
        Log::game_log->pushError("Cannot Remove persistant Asset: " + id_itr->second);
        return;
    }

    delete asset_itr->second;
    id_table.erase(id_itr);
    asset_bank.erase(asset_itr);
}
