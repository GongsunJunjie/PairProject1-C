#define LOCAL
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <bitset>
#include <sstream>
#include <map>

using namespace std;

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

map<string, int> words;
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin); // 将路径中"\"转义
	freopen("result", "w", stdout);
#endif // LOCAL
	string s;
	words.clear();
	while (cin >> s)
	{
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (!words.count(s)) words[s] = 0;
		words[s]++;
	}

	//把 map 中元素转存到 vector 中
	vector<PAIR> words_vec(words.begin(), words.end());
	sort(words_vec.begin(), words_vec.end(), CmpByValue());
	// sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value);
	for (int i = 0; i != words_vec.size(); ++i)
	{
		cout << words_vec[i].first << " " << words_vec[i].second << endl;
	}
	return 0;

}
