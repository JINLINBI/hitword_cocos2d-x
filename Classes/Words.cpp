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
	//���legal
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
	bool flag = 0;//0Ϊû��ƥ�䵽�ı�־
	if (0 == count) {//����������Ϊ�յ����
		for (int i = 0; i < 4; i++) {
			if (word[i][0][0] == c) {//��������ƥ��,
				//hitWord += c;��Ӧ����ʱ�����ȥ��
				legalWord[i] = true;

				flag = true;//ƥ�䵽,��¼����
			}
		}
		if (0 == flag) {//�������,����������
			reflash();//������,ɧ��
			return false;
		}
		else{
			hitWord += c;
			return true;
		}
	}
	else //�����ǵ�һ������
	for (int i = 0; i < 4; i++){
		if (true==legalWord[i]) {//�����֮ǰ���ʵĻ�,�����ж�
			if (word[i][0][count]) {//string wordΪ�ǿյĻ�
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
				log("+1��!!");//�������һ��,����������
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
	else {//�������,����������
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