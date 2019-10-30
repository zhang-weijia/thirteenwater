#include"Operation.h"
#include<time.h>
#include<algorithm>
using namespace std;
map<int, string> hm;
vector<int> oldarr,newarr;

void get_rand_number(vector<int> oldarr, vector<int> &newarr)
{	
	int value;
	srand((int)time(0)); //拿当前系统时间作为种子，由于时间是变化的，种子变化，可以产生不相同的随机数。
	/* 发牌的时候对于已经分配的数据不再修改 */
	for (int index=52;index>0; index--) 
	{
		value =rand() % index;
		newarr.push_back(oldarr[value]);
		oldarr.erase(oldarr.begin() + value);		
	}
}


int main()
{
	string colors[4] = { "&", "$", "*", "#" };//♥& ,♠$ ,♣* ♦#
	string numbers[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "%", "J", "Q", "K", "A" };
	int index = 0;
	for (string number : numbers)//制作扑克
	{
		for (string color : colors)
		{
			string pocker = color + number;
			hm[index] = pocker;
			oldarr.push_back(index);
			index++;
		}
	}
	get_rand_number(oldarr,newarr);
	player player1("Player1");
	player player2("Player2");
	player player3("Player3");
	player player4("Player4");

	dealer d ;
	d.distribute(player1, player2, player3, player4,newarr);
	
	Operation op1;
	player1.lookPoker(hm);
	op1.getpoker(player1.handPoker);	
	if (!op1.specialtype())
	{
    op1.judgeCardType(5, 0);	
	op1.judgeCardType(5, 1);
	op1.judgeCardType(3, 2);
	op1.play();
	}
	
	
	Operation op2;
	player2.lookPoker(hm);
	op2.getpoker(player2.handPoker);
	if (!op2.specialtype())
	{
    op2.judgeCardType(5, 0);
	op2.judgeCardType(5, 1);
	op2.judgeCardType(3, 2);
	op2.play();
	}
	
    
	Operation op3;
	player3.lookPoker(hm);
	op3.getpoker(player3.handPoker);
	if (!op3.specialtype())
	{
    op3.judgeCardType(5, 0);
	op3.judgeCardType(5, 1);
	op3.judgeCardType(3, 2); 
	op3.play();
	}
	
   
	Operation op4;
	player4.lookPoker(hm);
	op4.getpoker(player4.handPoker);
	if (!op4.specialtype())
	{
    op4.judgeCardType(5, 0);
	op4.judgeCardType(5, 1);
	op4.judgeCardType(3, 2);
	op4.play();
	}	
	return 0;
}
