#include <ctime>
#include <iostream>
#include <string>
#include "Macros.h"
#include "FileMgr.h"
using namespace std;

USING_NS_CC;


bool CFileMgr::readfile(const string& filename){
    auto shareFile = FileUtils::getInstance();
    if(shareFile->isFileExist(filename)){
        string data = shareFile->getStringFromFile(filename), word;
        size_t index = 0, pos, done = 0;
        do{
            pos = data.find('\n', index);
            word = data.substr(index, pos - index);
            index = pos + 1;
            if(word.length()){
                done = 0;
                m_wordlist.push_back(word);
            }
            else{
                done = 1;
            }
        }while(!done);
    }

    return false;
}

size_t CFileMgr::getwordcount() const{

    return m_wordlist.size();
}

string CFileMgr::getrandom() const{
    timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_usec);

    return m_wordlist.at(rand() % m_wordlist.size());
}

string CFileMgr::getword(const size_t n) const{
    return m_wordlist.at(n);
}
