
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Bad Design
struct BadJurnal
{
    std::string title;
    std::vector<std::string> entries;

    explicit BadJurnal(const std::string& title)
        :title(title)
        {
        }
    void add(const std::string& entry)
    {
        entries.push_back(entry);
    }

    void save(const std::string& filename)
    {
        std::ofstream ofs(filename);
        for (auto& s:entries)
            ofs<<s<<std::endl;
    }
};


// Good Design

struct Jurnal
{
    std::string title;
    std::vector<std::string> entries;

    explicit Jurnal(const std::string& title)
        :title(title)
        {
        }
    void add(const std::string& entry)
    {
        entries.push_back(entry);
    }
};


struct PersistenceManager
{
    static void save(const Jurnal& j, const std::string& filename)
    {
        std::ofstream ofs(filename);
        for(auto& s : j.entries)
            ofs<<s<<std::endl;
    }
};
