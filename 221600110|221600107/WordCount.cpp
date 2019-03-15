#define LOCAL
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <vector>
#include <map>
#include <bitset>
#include <sstream>
#include <map>

using namespace std;

class words
{
public:
	string GetWord()
	{
		return this->word;
	}
	int GetCount()
	{
		return this->count;
	}
	void SetWord(string word)
	{
		this->word = word;
	}
	void CountPlus()
	{
		(this->count)++; 
	}
private:
    string word = "a";
    int count = 0;
};
void CharCount();  //字符统计函数
void WordCount();  //单词统计函数
void LineCount();  //行数统计函数
void Transform();

int main(int argc,char *argv[])
{
    if (strcmp(argv[1], "input.txt") == 0)
    {
        CharCount();
        WordCount();
        LineCount();
    	Transform();
    }
    return 0;


}

void CharCount() //字符数统计函数
{
    FILE *fp;
    int c = 0;
    char ch;
    if((fp = fopen("input.txt","r")) == NULL)
    {
        printf("file read failure.");
    }
    ch = fgetc(fp);
    while(ch != EOF)
    {
            c++;
            ch = fgetc(fp);
    }
    freopen("result.txt","a",stdout);
    printf("characters：%d.\n",c);
    fclose(fp);
}

void WordCount() //单词数统计函数
{
    FILE *fp;
    int w = 0;
	int a = 0;
    char ch;
    if((fp = fopen("input.txt","r")) == NULL)
    {
        printf("file read failure.");
    }
    ch = fgetc(fp);
    while(ch != EOF)
    {
        if ((ch >= 'a'&&ch <= 'z')||(ch >= 'A'&&ch <='Z'))
        {
            while ((ch >= 'a'&&ch <= 'z')||(ch >= 'A'&&ch <= 'Z'))
            {
            	a++;
                ch = fgetc(fp);
            }
			if (a >= 4)
			{
				w++;
				while (ch >= '0'&&ch <= '9')
				{
					ch = fgetc(fp);
				}
				a = 0; 
			}
			else
			{
				while (ch >= '0'&&ch <= '9')
				{
					ch = fgetc(fp);
				}
				a = 0; 
			}
        }
        else if ((ch >= '0'&&ch <= '9'))
        {
        	while ((ch >= 'a'&&ch <= 'z')||(ch >= 'A'&&ch <= 'Z')||(ch >= '0'&&ch <= '9'))
        	{
        		ch = fgetc(fp);
			}
		}
        else 
        {
            ch = fgetc(fp);
        }
    }
    freopen("result.txt","a",stdout);
    printf("words：%d.\n",w);
    fclose(fp);

}

void LineCount() //行数统计函数
{
    FILE *fp;
    int l = 1;
    char ch;
    if((fp = fopen("input.txt","r")) == NULL)
    {
        printf("file read failure.");
    }
    ch = fgetc(fp);
    while(ch != EOF)
    {
        if (ch == '\n')
        {
            l++;
            ch = fgetc(fp);
        }
        else
        {
            ch = fgetc(fp);
        }
    }
    freopen("result.txt","a",stdout);
    printf("lines：%d.\n",l);
    fclose(fp);
}

typedef pair<string, int> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
{
    return lhs.second > rhs.second;
}

struct CmpByValue
{
    bool operator()(const PAIR& lhs, const PAIR& rhs)
    {
        return lhs.second > rhs.second;
    }
};

map<string,int> words;
void Transform()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin); // 将路径中"\"转义
    freopen("result.txt", "a", stdout);
#endif // LOCAL
    string s;
    words.clear();
    while(cin>>s)
    {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if(!words.count(s)) words[s]=0;
        words[s]++;
    }

    //把 map 中元素转存到 vector 中
    vector<PAIR> words_vec(words.begin(), words.end());
    sort(words_vec.begin(), words_vec.end(), CmpByValue());
// sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value);
    int top10=0;
    for (int i = 0; i != words_vec.size(); ++i)
    {
    	if(top10!=10)
    	{
    		
				if(words_vec[i].first.length()>=4)
    	if(isalpha(words_vec[i].first.at(0)))
    	{
    		 cout <<"<"<< words_vec[i].first<<">"<<" "<<words_vec[i].second << endl;
    		 top10++;
		}
		}
    
		else break;
       
    }

} 
