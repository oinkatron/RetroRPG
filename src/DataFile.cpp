#include "../include/DataFile.h"

DataFile::DataFile()
{
    name = "";
}

DataFile::DataFile(string filename)
{
    loadFile(filename);
}

bool DataFile::saveFile()
{
    ofstream file(name.c_str(), ios::out | ios::trunc);
    if (!file.is_open())
    {
        Log::game_log->pushError("Error opening file: " + name);
        return false;
    }

    for (int i = 0; i < sections.size(); i++)
    {
        file << "[" << sections[i]->name << "]\n";
        if (file.fail())
        {
            Log::game_log->pushError("Error writing to file: " + name);
            file.close();
            return false;
        }
        for (int ii = 0; ii < sections[i]->members.size(); ii++)
        {
            file << sections[i]->members[ii]->name << " = " << sections[i]->members[ii]->value << "\n";
            if (file.fail())
            {
                Log::game_log->pushError("Error writing to file: " + name);
                file.close();
                return false;
            }
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool DataFile::loadFile(string filename)
{
    string tmp_data;
    string::size_type i, found, found2;

    Section *tmp_section=NULL;
    Member *tmp_member=NULL;

    //Clear old members
    sections.clear();

    ifstream file(filename.c_str());

    if (!file.is_open())
    {
        Log::game_log->pushError("Could not open file: " + filename);
        return false;
    }

    name = filename;
    string *tmp1, *tmp2;

    while (!file.eof())
    {
        getline(file, tmp_data);

        if (!tmp_data.empty())
        {
            int i = tmp_data.find_first_not_of(" \t\n\v");
            if (i == string::npos || tmp_data[i] == '#')
                continue;

            if ((found = tmp_data.find("[")) != string::npos) //Finding new section
            {
                tmp_section = new Section;
                if ((found2 = tmp_data.find("]")) != string::npos)
                {
                    tmp_section->name = tmp_data.substr(found+1, found2-found-1);
                    sections.push_back(tmp_section);
                }
                else
                {
                    Log::game_log->pushError("Malformed section declaration");

                    if (!tmp_section)
                        delete tmp_section;

                    tmp_section = sections[sections.size()-1];
                }


            }
            else if ((found = tmp_data.find("=")) != string::npos) //found a new member
            {
                tmp_member = new Member;

                tmp1 = split(tmp_data, "=");
                deleteAllOf(tmp1[0], " ");

                tmp_member->name = tmp1[0];

                if ((found = tmp1[1].find_first_not_of(" \n\v\t")) != string::npos)
                {
                    if (tmp1[1][found] == '"')
                    {
                        found2 = tmp1[1].find("\"", found+1);
                        if (found2 != string::npos)
                        {
                            tmp_member->value = tmp1[1].substr(found+1, found2-found-1);
                            tmp_section->members.push_back(tmp_member);

                            delete [] tmp1;
                        }
                        else
                        {
                            Log::game_log->pushError("Malformed String!");

                            delete [] tmp1;
                            delete tmp_member;
                        }
                    }
                    else
                    {
                        tmp_member->value = tmp1[1].substr(found, tmp1[1].size()-found);
                        tmp_section->members.push_back(tmp_member);

                        delete [] tmp1;
                    }
                }
                else
                {
                    Log::game_log->pushError("Malformed expression");

                    delete [] tmp1;
                    delete tmp_member;
                }
            }
            else
            {
                Log::game_log->pushError("Unknown input: " + tmp_data);
            }
        }
    }
    file.close();

    return true;
}

void DataFile::createSection(string s_name)
{
    Section *s = new Section;
    s->name = s_name;

    sections.push_back(s);
}

void DataFile::addMember(string s, string m_n, string val)
{
    for (int i = 0; i < sections.size(); i++)
    {
        if (sections[i]->name == s)
        {
            for (int ii = 0; ii < sections[i]->members.size(); ii++)
            {
                if (sections[i]->members[ii]->name == m_n)
                {
                    sections[i]->members[ii]->value = val;
                    return;
                }
            }

            Member *m = new Member;
            m->name = m_n;
            m->value = val;
            sections[i]->members.push_back(m);

            return;
        }
    }

    Log::game_log->pushError("Could not find section: " + s);
    return;
}

void DataFile::addMember(int sec_num, string m_n, string val)
{
    if (sec_num < 0 || sec_num > sections.size())
    {
        Log::game_log->pushError("Member: " + toString(sec_num) + " is out of range!");
        return;
    }

    for (int i = 0; i < sections[sec_num]->members.size(); i++)
    {
        if (sections[sec_num]->members[i]->name == m_n)
        {
            sections[sec_num]->members[i]->value = val;
            return;
        }
    }

    Member *m = new Member;
    m->name = m_n;
    m->value = val;
    sections[sec_num]->members.push_back(m);
}

DataFile::~DataFile()
{
   for (int i = 0; i < sections.size(); i++)
        sections[i]->members.clear();
   sections.clear();
}
