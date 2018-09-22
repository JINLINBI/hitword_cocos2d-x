#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
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

    auto clabel = Label::createWithTTF("C/C++", "fonts/Marker Felt.ttf", 24);
    auto javalabel = Label::createWithTTF("Java", "fonts/Marker Felt.ttf", 24);
    auto pythonlabel = Label::createWithTTF("Python", "fonts/Marker Felt.ttf", 24);

    if (clabel == nullptr || clabel == nullptr || clabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // create menu, it's an autorelease object
        auto menu = Menu::create();
        menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

        MenuItemLabel* item = MenuItemLabel::create(clabel, CC_CALLBACK_1(HelloWorld::menuCLabelCallback,this));
        menu->addChild(item, 1);
        item = MenuItemLabel::create(javalabel);
        menu->addChild(item, 2);
        item = MenuItemLabel::create(pythonlabel);
        menu->addChild(item, 3);
        menu->alignItemsVertically();
        this->addChild(menu, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void HelloWorld::menuCLabelCallback(Ref* pSender)
{
    Scene* gameScene = GameScene::createScene();
    CCDirector::getInstance()->pushScene(gameScene);
}
