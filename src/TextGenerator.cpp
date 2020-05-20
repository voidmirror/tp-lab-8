#include "TextGenerator.h"

TextGenerator::TextGenerator()
{
    this->stateTable[this->start] = {};
}

TextGenerator::~TextGenerator()
{
}

void TextGenerator::analysis(std::string text)
{
    std::regex regex{R"([()«»;:!?\s,]+)"};
    std::sregex_token_iterator it{text.begin(), text.end(), regex, -1};
    std::vector<std::string> words{it, {}};
    
    this->stateTable[this->start].push_back(words[0]);
    
    prefix word = this->start;
    for (auto it = words.begin(); it != words.begin() + this->NPREF-1; ++it)
    {   
        word.push_back(*it);
        this->stateTable[word] = {*(it+1)};
        //std::cout << *it << std::endl;
    }
    for (auto it = words.begin() + this->NPREF-1; it != words.end()-1; ++it)
    {   
        word.erase(word.begin());
        word.push_back(*it);
        if ((*(it-1)).find('.') != std::string::npos)
        {
            prefix word = this->start;
            this->stateTable[this->start].push_back(*it);
            for (auto i = it+1; i != it + this->NPREF; ++i)
            {   
                word.push_back(*it);
                this->stateTable[word] = {*(it+1)};
                //std::cout << *it << std::endl;
            }
            it+=NPREF-2;
        }
        else
        {
            this->stateTable[word].push_back(*(it+1));
        }
        //std::cout << *it << std::endl;
    }

}

std::string TextGenerator::findRandomWord(prefix pr)
{
    std::string word;
    size_t index = rand() % this->stateTable[pr].size();
    word = this->stateTable[pr][index];
    this->stateTable[pr].erase(this->stateTable[pr].begin()+index);
    return word;
}

std::string TextGenerator::generateStr()
{
    std::string res = "";

    int count = 0;
    prefix pr = {"START"};
    std::string word;
    
    word = this->findRandomWord(pr);
    res += " " + word;

    while (pr.size() != this->NPREF)
    {
        pr.push_back(word);
        word = this->findRandomWord(pr);
        res += " " + word;
        //std::cout << word << std::endl;
    }
    count+=this->NPREF-1;
    
    while (count < this->MAXGEN)
    {
        if (word.find('.') != std::string::npos)
        {
            if (this->stateTable[this->start].size() == 0)
            {
                break;
            } 
            pr = {"START"};
            word = this->findRandomWord(pr);
            res += " " + word;
            while (pr.size() != this->NPREF)
            {
                pr.push_back(word);
                word = this->findRandomWord(pr);
                res += " " + word;
            }
            count+=this->NPREF-1;
        }
        else   
        {
            pr.erase(pr.begin());
            pr.push_back(word);
            if (this->stateTable[pr].size() == 0)
            {
                break;
            } 

            word = this->findRandomWord(pr);
            res += " " + word;
            count+=1;
        }
    }
    return res;
}

void TextGenerator::printTable() const
{
    for(auto& item : this->stateTable)
    {
        for (auto it = item.first.begin(); it!= item.first.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << " = [ ";
        for (auto it = item.second.begin(); it!= item.second.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << " ] " << std::endl;
    }
}

std::map < prefix, suffix > TextGenerator::getStateTable() const
{
    return this->stateTable;
}

std::string TextGenerator::readFileAndGenerateText(std::string fname)
{
    std::string text = "";
    std::string res;
    std::string tmp;
    std::ifstream F(fname);

    while (!F.eof())
    {
        std::getline(F, tmp);
        text+=tmp;
    }
    
    this->analysis(text);
    res = this->generateStr();

    std::ofstream out("res.txt", std::ios::app);
    if (out.is_open())
    {
        out << res << std::endl;
    }
    out.close(); 

    return res;
}