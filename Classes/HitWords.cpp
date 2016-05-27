#include "HitWords.h"

void HitWords::hit(char c)
{
	if (0 == hitWord.length()) {
		log("hitWord is empty!");
		hitWord = c;
	}

	else
		hitWord+=c;
}

void HitWords::reflash()
{
	hitWord = "";
}
