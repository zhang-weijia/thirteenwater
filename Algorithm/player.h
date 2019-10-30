#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<set>
using namespace std;

class player
{
public:
	set<int> handPokerNum;//有序集合
	string name;
	vector<string> handPoker ;
	//int winWater;
	player(string name)
	{
		this->name = name;
	}	 		
	 void lookPoker(map<int,string> hm)
	{
		cout<<this->name<<"的牌是：";		
                for (int key : handPokerNum)
                 handPoker.push_back(hm[key]);				   			
		vector<string> temp ;
		for (string s : handPoker)
		{
			temp.push_back(s);
		}
		for (size_t i = 0; i < temp.size(); i++)//去换10
		{
			 if (temp[i]=="&%") temp[i]="&10";
			 else if (temp[i] == "$%") temp[i] = "$10";
			 else if (temp[i] == "#%") temp[i] = "#10";
			 else if (temp[i] == "*%") temp[i] = "*10";
		}

		for (size_t i = 0; i < temp.size(); i++)//去换10
		{
			if(i<temp.size()-1)
			cout<<temp[i]<<" ";
			else
			cout<<temp[i]<<endl;
		}
		
	}
};


class dealer
{
public:
	void  distribute(player &player1, player &player2, player &player3, player &player4, vector<int> arr)
	{

		for (size_t x = 0; x < arr.size(); x++)//拿的只是牌的号数
		{			
			if (x % 4 == 0)      player1.handPokerNum.insert(arr[x]);
			else if (x % 4 == 1) player2.handPokerNum.insert(arr[x]);
			else if (x % 4 == 2) player3.handPokerNum.insert(arr[x]);
			else if (x % 4 == 3) player4.handPokerNum.insert(arr[x]);
		}
	}
};

