#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <sstream>
#include <fstream>


typedef std::deque<std::string> Prefix;
std::map<Prefix, std::vector<std::string> > statetab;

enum{
    NPREF = 2,
    NHASH = 5,
    MAXGEN = 1000
};

std::string NONWORD = "\n";

void add(Prefix & prefix, const std::string & s)
{
    if(prefix.size() == NPREF)
    {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

void build(Prefix & prefix, std::istream & in){
    std::string buf;
    while(in >> buf)
    {
         add(prefix, buf);
    }
}

void generate(int nwords, std::ostream & out)
{
    Prefix prefix;
    int i;
    for(i = 0; i < NPREF; i++)
    {
        add(prefix, NONWORD);
    }
    for(i = 0; i < nwords; i++)
    {
        std::vector<std::string> & suf = statetab[prefix];
        const std::string & w = suf[rand() % suf.size()];
        if(w == NONWORD)
            break;
        out << w <<" ";
        prefix.pop_front();
        prefix.push_back(w);
    }
}

int main(){
    int nwords = MAXGEN;
    Prefix prefix;
    for(int i = 0; i < NPREF; i++)
    {
        add(prefix, NONWORD);
    }
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");
    build(prefix, infile);
    add(prefix, NONWORD);
    generate(nwords, outfile);
    return 0;
}
