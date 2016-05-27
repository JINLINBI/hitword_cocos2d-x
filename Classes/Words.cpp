#include "Words.h"
#include "cocos2d.h"
#include<fstream>
#include<string>
using namespace std;
USING_NS_CC;
bool Words::init() {
	if (!Layer::init()) {
		return 0;
	}
	readFile();
	//scheduleOnce(schedule_selector(Words::hit),0.2f);
	for (int i = 0; i < 4; i++)
		updateWord(i);
	return true;
}

bool Words::updateWord(int i)
{
	srand((unsigned)time(NULL)*rand());
	auto size = Director::getInstance()->getVisibleSize();
	//清空legal
	int count = 0;
	for (int k = 0; k < 4; k++) {
		if (legalWord[k]) {
			count++;
		}
	}
	if (count < 2 && legalWord[i]) {
		reflash();
	}
	legalWord[i] = false;

	
	//
	word[i][0] = sbuf[rand() % sbuf.size()];
	word[i][1] = word[i][0].substr(word[i][0].find(" "), word[i][0].length());
	word[i][0] = word[i][0].substr(0, word[i][0].find(" "));
	randomS[i] = rand() % 3 + 1;
	x[i] = size.width;

	return true;
}

bool Words::readFile()
{
	char buf[80];
	ifstream fin("c:\\words.txt");
	while (fin.getline(buf, 80))
	{
	string str = buf;
	sbuf.push_back(str);
	}
	fin.close();
	return true;
}

bool Words::isFull(int i){
	bool r = false;
	auto size = Director::getInstance()->getVisibleSize();
	//
	log("%d", word[0][i].length());
	int length = word[0][i].length();
	if (x[i] <-40*length)
		r = true;

	return r;
}
bool Words::resetX(int i) {

	return 0;
}
int  Words::isHit(float dt) {

	log("fuckyou");
	return 0;
}

string Words::getWord(int i)
{

	return word[i][0];
}

void Words::hit(int i)
{
	//int i=0;
	randomS[i] = 0;
	word[i][0]=chinese(i);// = chinese(i);
	//scheduleOnce(schedule_selector(Words::updateWord,this,i), 0.1f);
	//scheduleUpdate();
}

void Words::reflash()
{
	hitWord.clear();
}
bool Words::isLegal(char c) {
	int count = hitWord.length();
	bool flag = 0;//0为没有匹配到的标志
	if (0 == count) {//遍历缓冲区为空的情况
		for (int i = 0; i < 4; i++) {
			if (word[i][0][0] == c) {//遍历输入匹配,
				//hitWord += c;不应该这时候加上去的
				legalWord[i] = true;

				flag = true;//匹配到,记录下来
			}
		}
		if (0 == flag) {//输入错误,做该做的事
			reflash();//重来吧,骚年
			return false;
		}
		else{
			hitWord += c;
			return true;
		}
	}
	else //遍历非第一次输入
	for (int i = 0; i < 4; i++){
		if (true==legalWord[i]) {//如果是之前合适的话,就再判断
			if (word[i][0][count]) {//string word为非空的话
				if (c == word[i][0][count]) {
					//hitWord += c;
					flag = true;

				}
				else {
					legalWord[i] = false;
				}
			}
		}
	}
	if (true == flag) {
		hitWord += c;
		for (int j = 0; j < 4; j++) {
			if (hitWord == word[j][0]) {
				log("+1分!!");//输入对了一个,做该做的事
				bomb(j);
				//hit(j);
				score++;
				showWord = chinese(j);
				updateWord(j);
				//updateWord(j);
				reflash();
				for (int k = 0; k < 4; k++) {
					legalWord[k] = false;
				}
			}
		}
		
		return true;
	}
	else {//输入错误,做该做的事
		for (int k = 0; k < 4; k++) {
			legalWord[k] = false;
		}
		reflash();
		return false;
	}
}

string Words::getHitWord()
{
	return hitWord;
}
bool Words::getLegalWord(int i)
{
	return legalWord[i];
}
string Words::chinese(int i)
{
	return word[i][1];
}
int Words::getScore()
{
	return score;
}
int Words::bomb(int i)
{
	bombX = x[i];
	bombNum = i;
	return 0;
}
long Words::getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}