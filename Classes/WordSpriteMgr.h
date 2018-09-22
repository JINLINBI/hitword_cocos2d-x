#ifndef __WORD_SPRITE_MGR_H__
#define __WORD_SPRITE_MGR_H__

#include "cocos2d.h"
#include <string>
#include <vector>
using namespace std;

class WordSprite;
class CFileMgr;
class WordSpriteMgr: public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(WordSpriteMgr);

public:
    bool createANewWord(const size_t);
    bool createANewRandomWord();
    bool addWord(WordSprite*);
    bool removeWord(WordSprite*);
    int hitWord(const string&);

protected:
    WordSpriteMgr();
    virtual ~WordSpriteMgr();

    // private data
private:
    size_t    m_size;
    CFileMgr* m_file;
};

#endif
