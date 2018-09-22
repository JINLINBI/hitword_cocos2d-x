#include "Macros.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "FileMgr.h"
#include "WordSprite.h"
#include "WordSpriteMgr.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

GameScene::GameScene():
    m_wordmgr(nullptr)
{
    m_wordmgr = WordSpriteMgr::create();
    if(m_wordmgr == nullptr)
        return;
    m_wordmgr->setPosition(Vec2::ZERO);
    addChild(m_wordmgr);
}

GameScene::~GameScene(){
    removeChild(m_wordmgr, true);
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }



    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    auto closeMenu = Menu::create(closeItem, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu, 2);

    //LabelBMFont* label1 = LabelBMFont::create("shanzhu", "fonts/yellow_font.fnt");
    //label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2));

    //MoveBy* moveby = MoveBy::create(2.0f, Vec2(-(visibleSize.width + label1->getContentSize().width) / 2, 0));
    //label1->runAction(moveby);
    //addChild(label1, 3);

    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->popScene();
}

void GameScene::onEnter(){
    Node::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_wordmgr->createANewRandomWord();
    m_wordmgr->createANewRandomWord();
    m_wordmgr->createANewRandomWord();
}
