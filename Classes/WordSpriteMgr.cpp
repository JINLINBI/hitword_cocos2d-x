#include <vector>
#include <algorithm>
#include "Macros.h"
#include "WordSprite.h"
#include "WordSpriteMgr.h"
#include "FileMgr.h"
USING_NS_CC;
using namespace std;

WordSpriteMgr::WordSpriteMgr():
    m_file(nullptr),
    m_size(0)
{
    m_file = CFileMgr::create();
    CC_SAFE_RETAIN(m_file);
    if(m_file)
        m_file->readfile(WORD_FILENAME);
}

WordSpriteMgr::~WordSpriteMgr(){
    removeAllChildren();
    CC_SAFE_RELEASE(m_file);
}

bool WordSpriteMgr::init(){
    if(Sprite::init()){
        return true;
    }

    return false;
}

bool WordSpriteMgr::createANewWord(const size_t n){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //CCLOG("random word: %s", m_file.getrandom().c_str());
    WordSprite* word = WordSprite::create(m_file->getword(n));
    word->setPosition(Vec2(origin.x + visibleSize.width + word->getContentSize().width / 2, origin.y + visibleSize.height / 2));
    MoveBy* move = MoveBy::create(MOVEBY_TIME, Vec2(-visibleSize.width - word->getContentSize().width, 0));
    word->runAction(move);
    //CCLOG("positionX: %f, positionY: %f", word->getAnchorPoint().x, word->getAnchorPoint().y);
    //CCLOG("widht: %f, height: %f", word->getContentSize().width, word->getContentSize().height);
    addWord(word);

    return false;
}

bool WordSpriteMgr::createANewRandomWord(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //CCLOG("random word: %s", m_file.getrandom().c_str());
    timeval t;
    gettimeofday(&t, NULL);
    srand(t.tv_usec);
    WordSprite* word = WordSprite::create(m_file->getrandom());
    word->setPosition(Vec2(origin.x + visibleSize.width + word->getContentSize().width / 2,
                        origin.y + LOW_EDGE + rand() % (int)(visibleSize.height - HIGH_EDGE - LOW_EDGE)));
    MoveBy* move = MoveBy::create(MOVEBY_TIME + DELTA_TIME - rand() % RANDOM_TIME, Vec2(-visibleSize.width - word->getContentSize().width, 0));
    Sequence* seq = Sequence::create(DelayTime::create( rand() % DELAY_TIME ), move,
            CallFuncN::create(CC_CALLBACK_1(WordSpriteMgr::hitWordCallback, this)), nullptr);
    word->runAction(seq);
    //CCLOG("positionX: %f, positionY: %f", word->getAnchorPoint().x, word->getAnchorPoint().y);
    //CCLOG("widht: %f, height: %f", word->getContentSize().width, word->getContentSize().height);
    addWord(word);

    return false;
}

void WordSpriteMgr::hitWordCallback(Ref* pSender){
    CCLOG("word gone!");
}

int WordSpriteMgr::hitWord(const string& word){
    int hit = FAILED;
    const auto& arrayNode = getChildren();
    for(auto& child: arrayNode){
        WordSprite* _word = dynamic_cast<WordSprite*>(child);
        if(_word){
            int res = _word->hitWord(word);
            if(res == FAILED){
                continue;
            }
            else if(res == SUCCESS){
                removeWord(_word);
                return SUCCESS;
            }
            else if(res == OKAY){
                if(hit == FAILED)
                    hit = SUCCESS;
                ++hit;
            }
        }
    }

    return hit;
}

bool WordSpriteMgr::addWord(WordSprite* word){
    addChild(word);
    ++m_size;

    return OKAY;
}

bool WordSpriteMgr::removeWord(WordSprite* word){
    removeChild(word, true);
    --m_size;

    return OKAY;
}
