#ifndef __WORD_SPRITE_H__
#define __WORD_SPRITE_H__

#include "cocos2d.h"
#include <string>
using namespace std;

class WordSprite : public cocos2d::Sprite
{
public:
    WordSprite();
    ~WordSprite();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(WordSprite);

    static WordSprite* create(const string&);

    int hitWord(const string&);
    void clearHitWord();

private:
    bool createWord();
    bool   m_dirty;
    string m_Word;
};

#endif // __WORD_SPRITE_H__
