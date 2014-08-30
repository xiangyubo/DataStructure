#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string preProcess(string s)
{
	int len = s.length();
	string ans;
	if(len != 0)
	{
		ans = "#";
		for(int i = 0; i < len; ++i)
		{
			ans += s[i];
			ans += "#";
		}
	}
	return ans;
}

string longestPalindrome(string s)
{
	string str = preProcess(s);
	int len = str.length();
	int *p = new int[len];
	int c = 0, r = 0;
	for(int i = 1; i < len; ++i)
	{
		p[i] = r > i ? min(p[2*c - i], r - i) : 0;
		while(str[i + p[i] + 1] == str[i - p[i] - 1])
		{
			++p[i];
			if(i - p[i] - 1 < 0 || i + p[i] + 1 >= len)
			{
				break;
			}
		}
		if(p[i] + i > r)
		{
			c = i;
			r = p[i] + i;
		}
	}
	int bra = 0, mirror = 0;
	for(int i = 0; i < len; ++i)
	{
		if(p[i] > bra)
		{
			bra = p[i];
			mirror = i;
		}
	}
	delete[] p;
	return s.substr((mirror - bra)/2, bra);
}

int main()
{
	string text = "xybabaababyx";
	string ans = longestPalindrome(text);
	cout<<ans<<endl;
	return 0;
}