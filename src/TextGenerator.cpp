#include "TextGenerator.h"

TextGenerator::TextGenerator()
{
    prefix = *(new deque<string>());
    statetab = *(new map<deque<string>, vector<string>>);
}

void TextGenerator::readFile(string filename){
    ifstream ifs(filename);
    string textFromFile;
    string strFromFile;
    while(!ifs.eof()){
        getline(ifs, strFromFile);
        textFromFile += strFromFile;
    }
    ifs.close();
    this->fillStateTab(textFromFile);
}

void TextGenerator::fillStateTab(string text){
    statetab.clear();
    vector<string> splitedText = split(text, ' ');
    prefix.push_back("txtBeg");
    vector<string> temp = *(new vector<string>());
    for(int i = 0; i < splitedText.size(); i++){
        if(prefix.size() < 1){
            prefix.push_back(splitedText.at(i));
        }
            prefix.push_back(splitedText.at(i));
            if(i == 0){
                txtEntryPoint = prefix;
            }
            if(statetab.find(prefix) == statetab.end()){
                temp.clear();
                if(i + 1 < splitedText.size()){
                temp.push_back(splitedText.at(i + 1));
                }else{
                temp.push_back("txtEnd");
                }
                statetab[prefix] = temp;
            }else{
                if(i + 1 < splitedText.size()){
                statetab[prefix].push_back(splitedText.at(i + 1));
                }else{
                statetab[prefix].push_back("txtEnd");
                }
            }
            prefix.pop_front();

    }
    prefix.push_back("txtEnd");
    statetab[prefix] = *(new vector<string>());
}

string TextGenerator::giveWordForCurPrefix(){
    vector<string> poolOfWords = statetab[prefix];
    int randPos = rand() % poolOfWords.size();
    string res = poolOfWords.at(randPos);
    statetab[prefix].erase(statetab[prefix].begin() + randPos);
    return res;
}

string TextGenerator::genText(){
    string generatedText = "";
    prefix = txtEntryPoint;
    int wordsCount = 2;
    while(wordsCount < MAXGEN - 2){
        prefix.push_back(giveWordForCurPrefix());
        generatedText += " ";
        generatedText += prefix.front();
        prefix.pop_front();
        wordsCount++;
        if(statetab[prefix].size() == 0){
            break;
        }
    }
    generatedText += " ";
    generatedText += prefix.front();
    prefix.pop_front();
    generatedText += " ";
    generatedText += prefix.front();
    return generatedText;
}

vector<string> TextGenerator::split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


void TextGenerator::genTextIntoFile(string filename){
    if(statetab.size() != 0){
        ofstream outfs(filename);
        outfs << genText();
    }
}
