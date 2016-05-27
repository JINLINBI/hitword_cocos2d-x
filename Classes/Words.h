#include "cocos2d.h"
#include <string>
using namespace std;
using namespace cocos2d;
class Words:public Layer {
public:
	friend class HitWords;
	CREATE_FUNC(Words);
	bool init();
	bool updateWord(int i);

	//virtual void update(float);
	bool readFile();
	bool isFull(int i);
	bool resetX(int i);
	int isHit(float);
	long getCurrentTime();
	string getWord(int i);
	void hit(int);
	void reflash();
	bool isLegal(char);
	int x[4];
	int randomS[4];
	string getHitWord();
	bool getLegalWord(int);
	string chinese(int);
	string showWord;
	int getScore();
	int bomb(int);
private:
	int score=0;
	string hitWord;
	string word[4][2];
	/*string word0[2];
	string word1[2];
	string word2[2];
	string word3[2];*/
	int needUpdate;
	bool legalWord[4];
	vector<string> sbuf;
public:
	int bombNum=-1;
	int bombX = -50;
	
};