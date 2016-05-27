#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <string>
#include "Words.h"
using namespace std;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void update(float);
	void checkWord();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void explode(int,int);
private:
	Words words;
	LabelTTF *word[8];
	LabelTTF *showWord;
	int score;
	LabelTTF *Score;

	/*
	LabelTTF *word1;
	LabelTTF *word2;
	LabelTTF *word3;*/
	//LabelBMFont word0;

};

#endif // __HELLOWORLD_SCENE_H__
