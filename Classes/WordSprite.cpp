#include <string>
#include "GameScene.h"
#include "WordSprite.h"
#include "Macros.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace std;

#define ORIGIN_FONT "fonts/yellow_font.fnt"
#define HIT_FONT "fonts/green_font.fnt"

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WordSpriteScene.cpp\n");
}

WordSprite* WordSprite::create(const string& s)
{
    WordSprite* p = create();
    if(p == nullptr) return p;
    p->m_Word = s;
    p->createWord();
    return p;
}

WordSprite::WordSprite():
    m_dirty(false)
{
}

WordSprite::~WordSprite(){
    removeAllChildren();
}

// on "init" you need to initialize your instance
bool WordSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }

    return true;
}


bool WordSprite::createWord(){
    if(m_Word.length() == 0){
        return false;
    }

    LabelBMFont* label;
    float width = 0, curwidth;
    for(int i = 0; i < m_Word.length(); ++i){
        label = LabelBMFont::create(m_Word.substr(i, 1), ORIGIN_FONT);

        width += label->getContentSize().width;
        curwidth = label->getContentSize().width / 2;
        label->setPosition(Vec2(width - curwidth, label->getContentSize().height / 2));
        this->addChild(label, 1, i);
    }
    this->setContentSize(Size(width, label->getContentSize().height));

    return true;
}

int WordSprite::hitWord(const string& s){
    float width = 0, curwidth;
    LabelBMFont* label;

    if(m_Word.find(s) == 0){
        for(int i = 0; i < s.length(); ++i){
            label = LabelBMFont::create(m_Word.substr(i, 1), HIT_FONT);

            removeChildByTag(i);
            width += label->getContentSize().width;
            curwidth = label->getContentSize().width / 2;
            label->setPosition(Vec2(width - curwidth, label->getContentSize().height / 2));
            this->addChild(label, 1, i);
        }
        if(s == m_Word){
            return SUCCESS;
        }

        return OKAY;
    }
    clearHitWord();

    return FAILED;
}

void WordSprite::clearHitWord(){
    float width = 0, curwidth;
    LabelBMFont* label;

    removeAllChildren();
    for(int i = 0; i < m_Word.length(); ++i){
        label = LabelBMFont::create(m_Word.substr(i, 1), ORIGIN_FONT);

        width += label->getContentSize().width;
        curwidth = label->getContentSize().width / 2;
        label->setPosition(Vec2(width - curwidth, label->getContentSize().height / 2));
        this->addChild(label, 1, i);
    }

    return;
}
