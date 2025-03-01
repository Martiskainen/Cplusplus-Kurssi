#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using Network = map<string, vector<string>>;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store(Network& net, const string& parent, const string& child)
{
    if (net.find(parent) == net.end())
    {
        net[parent] = {};
    }
    if (find(net[parent].begin(), net.at(parent).end(), child) != net.at(parent).end() )
    {
        return;
    }
    net[parent].push_back(child);
}

void print(const Network& net, const string& id, int indent = 0)
{

    for (int i = 0; i < indent; ++i)
    {
        cout << "..";
    }

    cout << id << endl;

    if (net.find(id) != net.end())
    {
        for (const string& child : net.at(id))
        {
            print(net, child, indent + 1);
        }
    }
}

int count(const Network& net, const string& id)
{
    int size = 0;

    if (net.find(id) != net.end())
    {
        for (const string& child : net.at(id))
        {
            ++size;
            size += count(net, child);
        }
    }
    return size;
}

int depth(const Network& net, const string& id)
{
    int max_depth = 0;
    int subnetwork_depth = 0;

    if (net.find(id) != net.end())
    {
        for (const string& child : net.at(id))
        {
            subnetwork_depth = depth(net, child);
            if (subnetwork_depth > max_depth)
            {
                max_depth = subnetwork_depth;
            }
        }
    }
    return max_depth + 1;
}

int main()
{
     std::set<std::string> valid_commands = {"S", "s", "P", "p", "C", "c",
                                             "D", "d", "Q", "q"};

    Network net;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(net, id1, id2);

        }
        // Other valid commands are not reasonable for an empty datastructure
	// TODO: complete the condition below
        else if(valid_commands.find(command) != valid_commands.end()
                and net.empty())
        {
            continue;
        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(net, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            cout << count(net, id) << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            cout << depth(net, id) << endl;

        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
