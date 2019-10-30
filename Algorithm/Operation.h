#include"player.h"
int p=-1;int q=-1;int r=-1;
int s=-1; int t=-1;

class Operation
{
private :	
	 vector<string> front;
	 vector<string> middle;
	 vector<string> behind;
	 char a[5][14];
	  int y[14] = { 0 };
	  int x[5] = { 0 };
public:	
	 void getpoker(vector<string> handPoker)
	 {
		 memset(a,'0', sizeof(a));
		 for (string str : handPoker)
		 {
			 int index;
				 if (str[1] > '1' && str[1] <= '9')			 
                    index = (str[1] - '2');					 
				 else if (str[1] == '%')index = 8;					 
				 else if (str[1] == 'J' )index = 9;					
				 else if (str[1] == 'Q')index = 10;					 
				 else if (str[1] == 'K')index = 11;					 
				 else index = 12;					 
                 y[index]++;
			 if (str[0] == '&')
			 {			 
				 a[0][index] = str[1];
				 x[0]++;				 
			 }
			 else if (str[0] == '$')
			 {				 
				 a[1][index] = str[1];
				 x[1]++;				 
			 }
			 else if (str[0] == '*')
			 {				
				 a[2][index] =str[1];
				 x[2]++;
			 }
			 else
			 {				  		 			   
			    a[3][index] =str[1];
			    x[3]++;	 
			 }
		 }
	 }
	//判断普通牌型
	 void judgeCardType(int size, int flag)
	{
		 
		if (size == 3)
		{
			for(int i=0;i<4;i++)
				for(int j=0;j<13;j++)
					if (a[i][j] != '0')
					{
						out(a[i][j], i, flag);
						a[i][j] = '0';
					}
			return;
		}
		if (size == 5)
		{
			int num = 0;
			//判断同花顺
			for (int i = 0; i < 4; i++)
				if (x[i] >= 5)
				{
					for (int j = 12; j >=4; j--)
						if (a[i][j] != '0' && a[i][j -1] != '0' && a[i][j - 2] != '0' &&
							a[i][j - 3] != '0' && a[i][j - 4] != '0')
						{
							out(a[i][j], i, flag); out(a[i][j - 1], i, flag); out(a[i][j - 2], i, flag);
							out(a[i][j - 3], i, flag); out(a[i][j - 4], i, flag); a[i][j] = '0';
							a[i][j - 1] = '0'; a[i][j - 2] = '0'; a[i][j - 3] = '0'; a[i][j - 4] = '0';
							x[i] = x[i] - 5; y[j]--; y[j - 1]--; y[j - 2]--; y[j - 3]--; y[j - 4]--;
							return;
						}
				}
			//判断炸弹
			num = 0; p =-1; q = -1;
			for (int j = 12; j >=0; j--)
			 {				
				if (y[j] == 4)
				{
                   p = j;
				   break;
				}			
			 }	
			for (int j = 0; j <=12; j++)
			{				
				if (y[j] == 1 )
				{
					q = j;
					break;
				}
			}	
			if (p >= 0 && q >= 0)
			{
                    out(a[0][p], 0, flag); out(a[1][p], 1, flag); out(a[2][p], 2, flag); 
					out(a[3][p], 3, flag);a[0][p] = '0'; a[1][p] = '0'; a[2][p] = '0'; a[3][p] = '0';	
					x[0]--; x[1]--; x[2]--; x[3]--; y[p] = y[p] - 4;
					for (int i = 0; i < 4; i++)
					if (a[i][q] != '0')
					{
                          out(a[i][q], i, flag); a[i][q] = '0';
						  x[i]--; y[q]--;return; 
					} 
					                
			}
					
							
			//判断葫芦
			num = 0; p = -1; q = -1;
			for (int j = 12; j>=0; j--)
			{				
				if (y[j]==3)
				{
					    p = j;
						break;
				 }	
			}	
			for (int j = 0; j<=12; j++)
			{
				if (y[j] == 2)
				{
					q = j;
					break;
				}
			}
			if (p>=0&&q>=0)
			{
				for (int i = 0; i < 4; i++)
				{ 
				   if(a[i][p]!='0')
				   {
                        out(a[i][p], i, flag); a[i][p] = '0';
							x[i]--; y[p]--;
				    }
				
				   if (a[i][q] != '0')
				    {
                          out(a[i][q], i, flag); a[i][q] = '0';
						  x[i]--; y[q]--; 
				    }
                 }
				return;
			}															
													
			//判断同花
			num = 0;
			for(int i=0;i<4;i++)
				if (x[i] >= 5)
				{
					for(int j=12;j>=0&&num<5;j--)
						if (a[i][j] != '0')
						{
							out(a[i][j], i, flag); a[i][j] = '0';
							x[i]--; y[j]--; num++;
						}
					if (num == 5)
						return;
				}
			//判断顺子
			for(int j=12;j>=4;j--)
				if (y[j] > 0 && y[j - 1] > 0 && y[j - 2] > 0 && y[j - 3] > 0 && y[j - 4] > 0)
				{
					    for(int t=j;t>j-5;t--)
						for(int i=0;i<4;i++)
							if (a[i][t] != '0')
							{
								out(a[i][t], i, flag); a[i][t] = '0';
								x[i]--; y[t]--; break;
							}
					return;
				}
			//判断三条
			num = 0; p = -1; q = -1; r = -1;
			for (int j = 12; j >=0; j--)
			{				
				if (y[j] == 3)
				{
					p = j;
				}	break;
			}
			for (int j = 0; j <=12; j++)
			{
				if (y[j] == 1 && q < 0)
				{
					q = j;
					continue;
				}
				if (y[j] == 1 && r < 0)
				{
					r = j;
					break;
				}
			}
				
				if (p >= 0 && q >= 0 && r >= 0)
				{
					for (int i = 0; i < 4; i++)
					{ 
						if (a[i][p] != '0')
						{
							out(a[i][p], i, flag);
							a[i][p] = '0';
							x[i]--; y[p]--;						
						}					
						if (a[i][q] != '0')
						{
							out(a[i][q], i, flag);
							a[i][q] = '0';
							x[i]--; y[q]--;
						}
						if (a[i][r] != '0')
						{
							out(a[i][r], i, flag);
							a[i][r] = '0';
							x[r]--; y[r]--;
						}
					}
					return;
				}
			
			//判断二对
				num = 0; p = -1; q = -1; r = -1;
				for (int j = 12; j >= 0; j--)
				{
					if (y[j] == 2 && p < 0)
					{
						p = j;
						continue;
					}
					if (y[j] == 2 && q < 0)
					{
						q = j;
						break;
					}
				}
				for (int j = 0; j <=12; j++)
				if (y[j] == 1 && r < 0)
				{
					r = j;
					break;
				}			
			if (p >= 0 && q >= 0 && r >= 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (a[i][p] != '0')
					{
						out(a[i][p], i, flag);
						a[i][p] = '0';
						x[i]--; y[p]--;
					}
					if (a[i][q] != '0')
					{
						out(a[i][q], i, flag);
						a[i][q] = '0';
						x[i]--; y[q]--;
					}
					if (a[i][r] != '0')
					{
						out(a[i][r], i, flag);
						a[i][r] = '0';
						x[r]--; y[r]--;
					}
				}
				return;
			}
			
			//判断一对
			num = 0; p = -1; q = -1; r = -1; s = -1;
			
			for (int j = 12; j >= 0; j--)
			{
				if (y[j] == 2)
				{
					p = j;
					break;
				}
			}
			for (int j = 0; j <=12; j++)
			{
			   if (y[j] == 1 && q < 0)
				{
					q = j;
					continue;
				}
				if (y[j] == 1 && r < 0)
				{
					r = j;
					continue;
				}
				if (y[j] == 1 && s < 0)
				{
					s = j;	
					break;
				}
			}
					
			if (p >= 0 && q >= 0 && r >= 0&&s>=0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (a[i][p] != '0')
					{
						out(a[i][p], i, flag);
						a[i][p] = '0';
						x[i]--; y[p]--;
					}
					if (a[i][q] != '0')
					{
						out(a[i][q], i, flag);
						a[i][q] = '0';
						x[i]--; y[q]--;
					}
					if (a[i][r] != '0')
					{
						out(a[i][r], i, flag);
						a[i][r] = '0';
						x[r]--; y[r]--;
					}
					if (a[i][s] != '0')
					{
						out(a[i][s], i, flag);
						a[i][s] = '0';
						x[s]--; y[s]--;
					}
				}
				return;
			}
			//判断五张散牌
			num = 0;
			for (int j = 12; j >=0; j--)
				if (y[j] == 1)
				{
					for (int i = 0; i < 4; i++)
						if (a[i][j] != '0')
						{
							out(a[i][j], i, flag);
							a[i][j] = '0';
							x[i]--; y[j]--;
							num++; break;
						}
					if (num == 5)
						return;
				}
		}
	}
		
	bool  specialtype()
	{
		if (samecolordragon() || singledragon() || twelvelord() || threecolorstraight() || threeboom()
			|| allbig() || allsmall() || samecolor() || twomonster() || fourtriple() || fivepair()
			|| sixpair() || threestraight() || threesamecolor())
			return true;
		return false;
	}
	bool samecolordragon()
	{			
             if (x[0]==13||x[1]==13||x[2]==13||x[3]==13)
			  {
				 cout << "特殊牌型：至尊清龙" << endl;
				 return true;
		      }
			 return false;	 	 
	}
	bool singledragon()
	{
		for (int j = 0; j < 13; j++)
			if (y[j] == 0)
			return false;
		cout << "特殊牌型：一条龙" << endl;
		return true;
	}
	bool twelvelord()
	{
		int count = 0;
		for (int j = 0; j <= 8; j++)
			count += y[j];
		if (count == 1)
		{
			cout << "特殊牌型：十二皇族" << endl;
            return true;
		}			
		return false;
	}
	bool threecolorstraight()
	{
		int three = 0; int five = 0;
		for (int i = 0; i < 4; i++)
		{
			if (x[i] == 3)
			{
				for(int j=0;j<=10;j++)
					if (a[i][j] != '0' && a[i][j + 1] != '0' && a[i][j + 2] != '0')
					{
						three++;
						break;
					}
			}
			else if (x[i] == 5)
			{
				for (int j = 0; j <= 8; j++)
					if (a[i][j] != '0' && a[i][j + 1] != '0' && a[i][j + 2] != '0'
						&& a[i][j + 3] != '0' && a[i][j + 4] != '0')
					{
						five++;
						break;
					}
			}
			else if (x[i] == 8)
			{
				if ((a[i][0] == '0' && a[i][1] == '0' && a[i][2] == '0' &&
					a[i][3] == '0' && a[i][4] == '0') || (a[i][8] == '0' &&
						a[i][9] == '0' && a[i][10] == '0' && a[i][11] == '0' && a[i][12] == '0'))
				{
                    five++;
					three++;
				}					
			}
			else if (x[i] == 10)
			{
				if ((a[i][0] == '0' && a[i][1] == '0' && a[i][2] == '0')  ||
					( a[i][10] == '0' && a[i][11] == '0' && a[i][12] == '0'))
				{
					five+=2;	
				}
			}
		}
		if (five == 2 && three == 1)
		{
			cout << "特殊牌型：三同花顺" << endl;
            return true;
		}			
		return false;
	}
	bool threeboom()
	{
		int count = 0;
		for (int j = 0; j < 13; j++)
			if (y[j] == 4)
				count++;
		if (count == 3)
		{
			cout << "特殊牌型：三分天下" << endl;
          return true;
		}			
		return false;
	}
	bool allbig()
	{
		for (int j = 0; j <= 5; j++)
			if (y[j] > 0)
				return false;
		cout << "特殊牌型：全大" << endl;
		return true;
	}
	bool allsmall()
	{
		for (int j = 7; j <= 12; j++)
			if (y[j] > 0)
				return false;
		cout << "特殊牌型：全小" << endl;
		return true;
	}
	bool samecolor()
	{
		if ((x[1] + x[2]) == 0 || (x[1] + x[2]) == 13)
		{
			cout << "特殊牌型：凑一色" << endl;
            return true;
		}			
		return false;
	}
	bool twomonster()
	{
		int three = 0; int two = 0;
		for (int j = 0; j < 13; j++)
		{
            if (y[j] == 3)
				three++;
			else if (y[j] == 2)
				two++;
		}
		if (three == 2 && two == 3)
		{
			cout << "特殊牌型：双怪冲三" << endl;
            return true;
		}			
		return false;
	}
	bool fourtriple()
	{
		int count = 0;
		for (int j = 0; j < 13; j++)
			if (y[j] == 3)
				count++;
		if (count == 4)
		{
			cout << "特殊牌型：四套三条" << endl;
            return true;
		}			
		return false;
	}
	bool fivepair()
	{
		int two = 0; int three = 0;
		for (int j = 0; j < 13; j++)
			if (y[j] == 2)
				two++;
			else if (y[j] == 3)
				three++;

		if (two == 5 && three == 1)
		{
			cout << "特殊牌型：五对三条" << endl;
            return true;
		}		
		return false;
	}
	bool sixpair()
	{
		int two = 0;
		for (int j = 0; j < 13; j++)
			if (y[j] == 2)
				two++;
		if (two == 6)
		{
			cout << "特殊牌型：六对半" << endl;
			return true;
		}
		return false;
	}
	bool threestraight()
	{
		int compare[4][13] = { 0 };
		int cmx[4] = { 0 }; int five = 0;
		int cmy[13] = { 0 }; int three = 0;
		for (int i = 0; i < 4; i++)
			cmx[i] = x[i];
		for (int j = 0; j < 13; j++)
			cmy[j] = y[j];

		    for (int i = 0; i < 4; i++)
			for (int j = 0; j < 13; j++)
			{
				if (a[i][j] != '0')
				compare[i][j] = 1;

			}
						
			for (int j = 0; j <=8; j++)
				if (cmy[j] != 0 && cmy[j + 1] != 0 && cmy[j + 2] != 0 
					&& cmy[j + 3] != 0 && cmy[j + 4] != 0)
				{
					for (int t = j; t < j + 5; t++)
						for (int i = 0; i < 4; i++)
							if (compare[i][t] == 1)
								compare[i][t] = 0;
					five++;
				}
			for (int j = 0; j <= 10; j++)
				if (cmy[j] != 0 && cmy[j + 1] != 0 && cmy[j + 2] != 0)					
				{					
					three++;
				}
			if (five == 2 && three == 1)
			{
				cout << "特殊牌型：三顺子" << endl;
				return true;
			}
			return  false;
	}
	bool threesamecolor()
	{
		int three = 0; int five = 0;
		int eight = 0; int ten = 0;
		for (int i = 0; i < 4; i++)
			if (x[i] == 3)
				three++;
			else if (x[i] == 5)
				five++;
			else if (x[i] == 8)
				eight++;
			else if (x[i] == 10)
				ten++;
		if ((three == 1 && five == 2) || (three == 1 && ten == 1) || (five == 1 && eight == 1))
		{
			cout << "特殊牌型：三同花" << endl;
			return true;
		}
		return false;
	}
	//存牌
    void out(char c,int color,int flag)
	{
		char tmp[1];
		tmp[0] = c;
		string ss(tmp, 1);
		string col="";
		switch (color)
		{
		case 0:
			col += "&";
			break;
		case 1:
			col += "$";
			break;
		case 2:
			col += "*";
			break;
		case 3:
			col += "#";
			break;
		default:
			break;
		}
		//存后墩牌
		if (flag == 0)
		{			
			behind.push_back(col+ss);
		}
		//存中墩牌
		else if (flag == 1)
		{
			middle.push_back(col+ss);
		}
		//存前墩牌
		else if (flag == 2)
		{
			front.push_back(col+ss);
		}
	}
	//改变十的表示形式
     vector<string> changeTen(vector<string> al)
	{
		 vector<string> temp ;
		for (string s : al) 
		{
			temp.push_back(s);
		}
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] == "&%") temp[i] = "&10";
			else if (temp[i] == "$%") temp[i] = "$10";
			else if (temp[i] == "#%") temp[i] = "#10";
			else if (temp[i] == "*%") temp[i] = "*10";
		}
		return temp;
	}
	//出牌
	 void play()
	{				
				cout << "后墩是：";
				prin(changeTen(behind));
				cout << "中墩是：";
				prin(changeTen(middle));
				cout << "前墩是：";
				prin(changeTen(front));					
		
	}
	 void prin(vector<string> s)
	 {
		 vector<string> temp[13];
		 for (vector<string>::iterator it = s.begin(); it != s.end(); it++)
		 {
			 switch ((*it)[1])
			 {
			 case '2':
				 temp[0].push_back(*it);
				 break;
			 case '3':
				 temp[1].push_back(*it);
				 break;
			 case '4':
				 temp[2].push_back(*it);
				 break;
			 case '5':
				 temp[3].push_back(*it);
				 break;
			 case '6':
				 temp[4].push_back(*it);
				 break;
			 case '7':
				 temp[5].push_back(*it);
				 break;
			 case '8':
				 temp[6].push_back(*it);
				 break;
			 case '9':
				 temp[7].push_back(*it);
				 break;
			 case '1':            //存储十
				 temp[8].push_back(*it);
				 break;
			 case 'J':
				 temp[9].push_back(*it);
				 break;
			 case 'Q':
				 temp[10].push_back(*it);
				 break;
			 case 'K':
				 temp[11].push_back(*it);
				 break;
			 case 'A':
				 temp[12].push_back(*it);
				 break;
			 default:
				 break;
			 }
		 }
		 for (int i = 0; i < 13; i++)
		 {
			 for (vector<string>::iterator it = temp[i].begin(); it != temp[i].end(); it++)
			 {
				 cout << *it << " ";
			 }
		 }		
		 cout << endl;
	 }
};
