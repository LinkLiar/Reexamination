#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<pair<int, int> > GetMatchingString(vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint)    // 求区域内匹配字数最多的子串集合
{
	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
		return {};
	int rows = brPoint.first;
	int cols = brPoint.second;
	if (dp[tlPoint.first][tlPoint.second])
	{
		int probeX = tlPoint.first + 1;
		int probeY = tlPoint.second + 1;
		int probeLength = 1;

		if (probeX<cols&& probeY<rows&&dp[probeX][probeY])
		{
			while (dp[probeX][probeY])
			{
				probeLength++;
				probeX++;
				probeY++;
			}
		}
		else
		{
			int bottomLength = 0;
			int bottomprobeX = tlPoint.first + 1;
			int bottomprobeY = tlPoint.second;
			while (bottomprobeX < cols && probeY < rows && dp[bottomprobeY][bottomprobeY])
			{
				bottomLength++;
				bottomprobeX++;
				bottomprobeY++;
			}
			int rightLength = 0;
			int rightprobeX = tlPoint.first;
			int rightprobeY = tlPoint.second + 1;
			while (rightprobeX < cols && rightprobeY < rows && dp[rightprobeX][rightprobeY])
			{
				rightLength++;
				rightprobeX++;
				rightprobeY++;
			}


			if (bottomLength > min(dp.size() / 3, dp[0].size() / 3) || rightLength > min(dp.size() / 3, dp[0].size() / 3))
			{
				if(bottomLength> rightLength)

				return{};
			}
			else
			{

				return{};
			}




		}
	}
	else
	{
		int probeX = tlPoint.first + 1;
		int probeY = tlPoint.second + 1;
		int probeLength = 1;
		while (probeX < cols && probeY < rows && dp[probeX][probeY])
		{
			probeLength++;
			probeX++;
			probeY++;
		}
		int bottomLength = 0;
		int bottomprobeX = tlPoint.first + 1;
		int bottomprobeY = tlPoint.second;
		while (bottomprobeX < cols && bottomprobeY < rows && dp[bottomprobeX][bottomprobeY])
		{
			bottomLength++;
			bottomprobeX++;
			bottomprobeY++;
		}
		int rightLength = 0;
		int rightprobeX = tlPoint.first;
		int rightprobeY = tlPoint.second + 1;
		while (rightprobeX < cols && rightprobeY < rows && dp[rightprobeX][rightprobeY])
		{
			rightLength++;
			rightprobeX++;
			rightprobeY++;
		}
		if (probeLength > bottomLength)
		{
			if (probeLength > rightLength)
			{
				if (probeX == cols || probeY == rows)
				{

					for(int i = probeX-1,int j = probeY-1;probeLength==0;i--,j--)

					return
				}
					
			}
			else
			{

			}

		}
			
	}
}


char* GetCommonString(char* str1, char* str2)
{
	if (str1 == NULL || str2 == NULL) {
		return NULL;
	}
	int stringLen1 = strlen(str1);
	int stringLen2 = strlen(str2);
	char* strLong = str1;
	char* strShort = str2;
	int longLength = stringLen1;
	int shortLength = stringLen2;
	if (stringLen2 > stringLen1)    // 将短字符串放到字符串2
	{
		strLong = str2;
		strShort = str1;
		longLength = stringLen2;
		shortLength = stringLen1;
	}
	//寻找两个字符串中的公共子串
	vector<vector<int> > dp(shortLength, vector<int>(longLength, 0));
	cout << "   ";

	for (int j = 0; j < longLength; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << strLong[j];
	}
	cout << "\n";
	for (int i = 0; i < shortLength; i++)
	{
		cout << setw(3) << setiosflags(ios::left) << strShort[i];
		for (int j = 0; j < longLength; j++)
		{
			if (strShort[i] == strLong[j])
			{
				dp[i][j] = 1;
			}
			else
				dp[i][j] = 0;
			cout << setw(3) << setiosflags(ios::left) << dp[i][j];
		}
		cout << "\n";
	}

	vector<pair<int, int> >result = GetMatchingString(dp, make_pair(0, 0), make_pair(shortLength - 1, longLength - 1));

	cout << "StringOne: ";
	for (int j = 0; j < longLength; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << strLong[j];
	}
	cout << "\n" << "StringTwo: ";
	for (int j = 0; j < shortLength; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << strShort[j];
	}
	return NULL;
}
int main()
{
	//char str1[50]="abcnabcd";
	//char str2[50]="abcdbcd";
	//char str1[50] = "abcdabcbdeabckk";
	//char str2[50] = "kkabceabcdecabc";
	//char str1[50] = "bcddfgfhijk";
	//char str2[50] = "abcdgfgihij";
	char str1[50] = "abcdfgfgfgabab";
	char str2[50] = "abcdgfgfgfbaba";
	//cout << "Please input the first string:";
	//cin >> str1;
	//cout << "Please input the second string:";
	//cin >> str2;

	GetCommonString(str1, str2);

	return 0;
}