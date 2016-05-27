#include "HelloWorldScene.h" 
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	words.init();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("baozha.wav");
	auto size = Director::getInstance()->getVisibleSize();
	// auto rootNode = CSLoader::createNode("MainScene.csb");
	for (int i = 0; i < 4; i++) {

		word[i] = LabelTTF::create(words.getWord(i), "Jackey_Egypt.ttf", 40);
		word[i]->setFontFillColor(ccColor3B(118, 77, 57));
		word[i]->setAnchorPoint(Vec2(0, 0));
		word[i]->setPosition(Vec2(words.x[i], size.height / 2 +i*65));
		this->addChild(word[i]);
	}
	for (int i = 0; i < 4; i++) {
		word[4+i] = LabelTTF::create(words.getHitWord(), "Jackey_Egypt.ttf", 40);
		word[4+i]->setFontFillColor(ccColor3B(48, 197, 207));
		word[4+i]->setAnchorPoint(Vec2(0, 0));
		word[4+i]->setPosition(Vec2(size.width, size.height /2+i*65));
		this->addChild(word[4+i]);
	}
	showWord = LabelTTF::create(words.showWord, "Jackey_Egypt.ttf", 40);
	showWord->setFontFillColor(ccColor3B(208, 107, 107));
	showWord->setAnchorPoint(Vec2(0.5, 0));
	showWord->setPosition(Vec2(size.width/2, size.height / 2-150));
	this->addChild(showWord);

	//
	score = words.getScore();
	char buf[10];
	sprintf(buf, "SCORE:%03d", score);
	Score = LabelTTF::create(buf, "Jackey_Egypt.ttf", 40);
	Score->setFontFillColor(ccColor3B(98, 107, 107));
	Score->setAnchorPoint(Vec2(0, 0));
	Score->setPosition(Vec2(size.width / 8, size.height -50));
	this->addChild(Score,0);

	//
	
	/*
	启用键盘监听
	*/
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	scheduleUpdate();
    return true;
}

void HelloWorld::update(float f)
{
	auto size = Director::getInstance()->getVisibleSize();
	////
	for (int i = 0; i < 4; i++) {
		word[i]->setString(words.getWord(i));
		word[i]->setPositionX(words.x[i]);
		words.x[i] -=  words.randomS[i];
	}
	for (int i = 0; i < 4; i++) {
		word[i + 4]->setString(words.getHitWord());
		if(words.getLegalWord(i))
		word[i+4]->setPositionX(words.x[i]);
		else {
			word[i + 4]->setPositionX(size.width);
		}
	}
	
	if (words.bombNum>-1) {
		explode(words.bombX+words.getWord(words.bombNum).length()*15/2, size.height/2+words.bombNum*65);
		words.bombNum = -1;
	}
	showWord->setString(words.showWord);

	score = words.getScore();
	char buf[10];
	sprintf(buf, "SCORE:%03d", score);
	Score->setString(buf);
	checkWord();
}

void HelloWorld::checkWord()
{
	//auto size = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 4; i++) {
		if (words.isFull(i)) {
			words.updateWord(i);
		}
	}
}
// 键位响应函数原型
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	char c;
	if (6 == (int) keyCode) {
		exit(0);
	}
	else if ((int)keyCode <= 149 || (int)keyCode >= 124) {
		//\\\\\\uxc vyadufhsdilvhgho;wer 
		c =(char) (int)keyCode-27;
		log("***********%d***********************", words.isLegal(c)==true);
	}
	else if (59 ==(int) keyCode || 164 == (int) keyCode) {

	}
	//log("Key with keycode %d pressed", keyCode);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	//log("Key with keycode %d released", keyCode);
}

void HelloWorld::explode(int x,int y)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("baozha.wav",false);
	auto size = Director::getInstance()->getVisibleSize();
	ParticleSystemQuad* psq = ParticleExplosion::create();
	this->addChild(psq);
	psq->setPosition(Vec2(x,y ));
	psq->setSpeed(140);
	psq->setLife(0.5);
	psq->setLifeVar(1);
	psq->setScale(0.8);
	psq->setColor(ccColor3B(132, 132, 94));
	psq->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	psq->setTotalParticles(464);
	

}
