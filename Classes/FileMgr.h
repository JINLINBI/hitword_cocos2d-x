#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include "cocos2d.h"
#include <string>
using namespace std;

class CFileMgr: public cocos2d::Node
{
public:
    virtual bool init(){return true;};
    bool readfile(const string&);
    string getrandom() const;
    string getword(const size_t) const;
    size_t getwordcount() const;

    CREATE_FUNC(CFileMgr);
private:
    vector<string> m_wordlist;
};

#endif // __FILE_MANAGER_H__
