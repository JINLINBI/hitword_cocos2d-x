#ifndef _HITWORDS_H_
#define _HITWORDS_H_
#include "cocos2d.h"
#include <string>
using namespace std;
using namespace cocos2d;
class HitWords:public Layer{
public:
	//void update(int i);
	void hit(char);
	void reflash();
private:
	//string enterWord;

	string hitWord;
};
#endif