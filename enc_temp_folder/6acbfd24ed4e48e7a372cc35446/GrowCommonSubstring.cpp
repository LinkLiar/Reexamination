#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<pair<int, int> > GetMatchingString(vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint, char* longStr, char* shortStr)    // 求区域内匹配字数最多的子串集合
{
	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
		return {};
	int rows = brPoint.first + 1;
	int cols = brPoint.second + 1;
	vector<pair<int, int> >result;
	int pointX = tlPoint.first;
	int pointY = tlPoint.second;
	while (true)
	{
		if (dp[pointX][pointY])
		{
			result.push_back(make_pair(pointX, pointY));
			int probeX = tlPoint.first + 1;
			int probeY = tlPoint.second + 1;
			int probeLength = 1;

			if (probeX < cols && probeY < rows && dp[probeX][probeY])
			{
				while (dp[probeX][probeY])
				{
					result.push_back(make_pair(probeX, probeY));
					probeLength++;
					probeX++;
					probeY++;
				}
				if (!(probeX < cols && probeY < rows))
					break;
				pointX = probeX;
				pointY = probeY;
			}
		}
		else
		{
			int probeX = pointX + 1;
			int probeY = pointY + 1;
			int probeLength = 0;
			while (probeX < cols && probeY < rows && dp[probeX][probeY])
			{
				probeLength++;
				probeX++;
				probeY++;
			}
			int bottomLength = 0;
			int bottomprobeX = pointX + 1;
			int bottomprobeY = pointY;
			while (bottomprobeX < cols && bottomprobeY < rows && dp[bottomprobeX][bottomprobeY])
			{
				bottomLength++;
				bottomprobeX++;
				bottomprobeY++;
			}
			int rightLength = 0;
			int rightprobeX = pointX;
			int rightprobeY = pointY + 1;
			while (rightprobeX < cols && rightprobeY < rows && dp[rightprobeX][rightprobeY])
			{
				rightLength++;
				rightprobeX++;
				rightprobeY++;
			}
			bool breakFlag = 0;
			if (probeLength != 0 || bottomLength != rightLength)
			{
				if (probeLength >= bottomLength)
				{
					if (probeLength >= rightLength)
					{
						int i = probeX - probeLength;
						int j = probeY - probeLength;
						if (!(probeX < cols && probeY < rows))
						{
							breakFlag = 1;

						}
						for (; probeLength > 0; probeLength--, i++, j++)
							result.push_back(make_pair(i, j));
						pointX = probeX;
						pointY = probeY;
					}
					else
					{
						int i = rightprobeX - rightLength;
						int j = rightprobeY - rightLength;
						if (!(rightprobeX < cols && rightprobeY < rows))
						{
							breakFlag = 1;
							rightLength++;
						}

						for (; rightLength > 0; rightLength--, i++, j++)
							result.push_back(make_pair(i, j));
						pointX = rightprobeX;
						pointY = rightprobeY;
					}
				}
				else
				{
					if (bottomLength > rightLength)
					{
						int i = bottomprobeX - bottomLength;
						int j = bottomprobeY - bottomLength;
						if (!(bottomprobeX < cols && bottomprobeY < rows))
						{
							breakFlag = 1;
						}
						for (; bottomLength > 0; bottomLength--, i++, j++)
							result.push_back(make_pair(i, j));
						pointX = bottomprobeX;
						pointY = bottomprobeY;
					}
					else
					{
						int i = rightprobeX - rightLength;
						int j = rightprobeY - rightLength;
						if (!(rightprobeX < cols && rightprobeY < rows))
						{
							breakFlag = 1;
							rightLength++;
						}
						for (; rightLength > 0; rightLength--, i++, j++)
							result.push_back(make_pair(i, j));
						pointX = rightprobeX;
						pointY = rightprobeY;
					}
				}
				if (breakFlag)
					break;
			}
			else if (bottomLength == rightLength && rightLength != 0)
			{
				if (bottomLength > min(dp.size() / 3, dp[0].size() / 3))
				{
					int i, j;
					if (longStr[bottomprobeX]>shortStr[bottomprobeX])
					{
						i = rightprobeX - rightLength;
						j = rightprobeY - rightLength;
						pointX = rightprobeX;
						pointY = rightprobeY;
					}
					else
					{
						i = bottomprobeX - bottomLength;
						j = bottomprobeY - bottomLength;
						pointX = bottomprobeX;
						pointY = bottomprobeY;
					}


					if (!(rightprobeX < cols && rightprobeY < rows))
					{
						breakFlag = 1;
						rightLength++;
					}
					for (; rightLength > 0; rightLength--, i++, j++)
						result.push_back(make_pair(i, j));

				}
				else
				{
					pointX += rightLength;
					pointY += rightLength;
				}
			}
			else
			{
				pointX += 1;
				pointY += 1;
			}

		}
	}
	return result;
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

	vector<pair<int, int> >result = GetMatchingString(dp, make_pair(0, 0), make_pair(shortLength - 1, longLength - 1), strLong, strShort);

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
	cout << "\n" << "StringMix: ";
	for (int i = 0; i < result.size(); i++)
	{
		if (i != 0 && (result[i].first == result[i - 1].first+1 && result[i].second == result[i - 1].second+1))
			cout << setw(3) << setiosflags(ios::left) << strLong[result[i].second];
		else if (i == 0)
		{
			int headGap = result[0].first > result[0].second ? result[0].second : result[0].first;
			for (int j = 0; j < headGap-1; j++)
				cout << setw(3) << setiosflags(ios::left) << "*";
			cout << setw(3) << setiosflags(ios::left) << strLong[0];
		}
		else
		{
			int middleGap = result[i].first - result[i - 1].first > result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			for (int j = 0; j < middleGap-1; j++)
				cout << setw(3) << setiosflags(ios::left) << "*";
	
	/*		if(result[i - 1].first- result[i - 1].second == result[i].first- result[i].second)*/
			cout << setw(3) << setiosflags(ios::left) << strLong[result[i].second];

		}
		//if (result[i].first == result[i].second && i == result[i].first)
		//	cout << setw(3) << setiosflags(ios::left) << strShort[i];
		//else
		//	return NULL;



	}

	return NULL;
}
int main()
{
	//char str1[50]="abcnabcd";
	//char str2[50]="abcdbcd";
	//char str1[50] = "aaaabaaa";
	//char str2[50] = "aaaaaaab";
	//char str1[50] = "abcdfgfhijk";
	//char str2[50] = "abcdgfghijk";
	//char str1[50] = "abcdabcbdeabckk";
	//char str2[50] = "kkabceabcdecabc";
	//char str1[50] = "bcddfgfhijk";
	//char str2[50] = "abcdgfgihij";
	//char str2[50] = "abcdfgfgfgabab";
	//char str1[50] = "abcdgfgfgfbaba";  //Done
	//char str1[50] = "abcdeabc";
	//char str2[50] = "abcedabc";  //Done
	//char str1[50] = "abcdfgfgfgaaaa";
	//char str2[50] = "abcdgfgfgfaaaa";  //Done
	char str1[50] = "abcdhfehijk";
	char str2[50] = "abcdefhijk";  //Done
	//cout << "Please input the first string:";
	//cin >> str1;
	//cout << "Please input the second string:";
	//cin >> str2;

	GetCommonString(str1, str2);

	return 0;
}