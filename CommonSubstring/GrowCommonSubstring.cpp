#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
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
	int missCount = 1;
	while (true)
	{
		if (dp[pointX][pointY])
		{
			missCount = 1;
			result.push_back(make_pair(pointX, pointY));
			int probeX = tlPoint.first + 1;
			int probeY = tlPoint.second + 1;
			int probeLength = 1;

			if (probeX < rows && probeY < cols && dp[probeX][probeY])
			{
				while (dp[probeX][probeY])
				{
					result.push_back(make_pair(probeX, probeY));
					probeLength++;
					probeX++;
					probeY++;
				}
				if (!(probeX < rows && probeY < cols))
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
			while (probeX < rows && probeY < cols && dp[probeX][probeY])
			{
				probeLength++;
				probeX++;
				probeY++;
			}
			int bottomLength = 0;
			int bottomprobeX = pointX + 1;
			int bottomprobeY = pointY;
			while (bottomprobeX < rows && bottomprobeY < cols && dp[bottomprobeX][bottomprobeY])
			{
				bottomLength++;
				bottomprobeX++;
				bottomprobeY++;
			}
			int rightLength = 0;
			int rightprobeX = pointX;
			int rightprobeY = pointY + 1;
			while (rightprobeX < rows && rightprobeY < cols && dp[rightprobeX][rightprobeY])
			{
				rightLength++;
				rightprobeX++;
				rightprobeY++;
			}
			bool breakFlag = 0;
			if (probeLength != 0 || bottomLength != rightLength)
			{
				missCount = 1;
				if (probeLength >= bottomLength)
				{
					if (probeLength >= rightLength)
					{
						int i = probeX - probeLength;
						int j = probeY - probeLength;
						if (!(probeX < rows && probeY < cols))
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
						if (!(rightprobeX < rows && rightprobeY < cols))
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
						if (!(bottomprobeX < rows && bottomprobeY < cols))
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
						if (!(rightprobeX < rows && rightprobeY < cols))
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
				missCount = 1;
				if (bottomLength > min(dp.size() / 3, dp[0].size() / 3))
				{
					int i, j;
					if (longStr[bottomprobeX] > shortStr[bottomprobeX])
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
					if (!(rightprobeX < rows && rightprobeY < cols))
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
				if (!(probeX + 1 < rows && probeY + 1 < cols))
					break;
				if (dp[pointX + 1][pointY + 1] || dp[pointX + 1][pointY] || dp[pointX][pointY + 1])
				{
					pointX += 1;
					pointY += 1;
				}
				else
				{
					missCount++;
					if (missCount > min(brPoint.first - tlPoint.first, brPoint.second - tlPoint.second) / 2)
						return {};
					if (!(probeX + missCount < rows && probeY + missCount < cols))
						break;
					int bottomMax = 0;
					int bottomMaxID = 0;
					int rightMax = 0;
					int rightMaxID = 0;
					for (int i = 0; i <= missCount; i++)
					{
						if (dp[pointX + missCount][pointY + i])
						{
							int tempLength = 1;
							while (pointX + missCount + tempLength < rows && pointY + i + tempLength < cols && dp[pointX + missCount + tempLength][pointY + i + tempLength])
								tempLength++;
							if (bottomMax < tempLength)
							{
								bottomMax = tempLength;
								bottomMaxID = pointY + i;
							}
						}

					}
					for (int i = 0; i <= missCount; i++)
					{
						if (dp[pointY + i][pointX + missCount])
						{
							int tempLength = 1;
							while (pointX + i + tempLength < rows && pointY + missCount + tempLength < cols && dp[pointX + i + tempLength][pointY + missCount + tempLength])
								tempLength++;
							if (rightMax < tempLength)
							{
								rightMax = tempLength;
								rightMaxID = pointX + i;
							}
						}
					}
					if (rightMax == bottomMax && bottomMax == 0)
						continue;
					else
					{
						if (bottomMax > rightMax)
						{
							pointX = pointX + missCount - 1;
							pointY = bottomMaxID;
						}
						else
						{
							pointX = rightMaxID;
							pointY = pointY + missCount - 1;
						}
					}
				}
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
	string pairStr;
	vector<pair<int, vector<pair<int, string> > > > odds(strlen(strLong));
	vector<pair<int, string> > temp;
	for (int i = 0; i < strlen(strLong); i++)
	{
		odds.push_back(make_pair(0, temp));
	}
	string revise(1, '*');
	string add(1, '+');
	for (int i = 0, x = 1; i < static_cast<int>(result.size()) - 1; i++, x++)
	{
		if (i != 0 && (result[i].first == result[i - 1].first + 1 && result[i].second == result[i - 1].second + 1))
		{
			cout << setw(3) << setiosflags(ios::left) << strLong[result[i].second];
			pairStr.push_back(strLong[result[i].second]);
			odds[x].first = 2;
		}
		else if (i == 0)
		{
			int headGap = result[0].first > result[0].second ? result[0].second : result[0].first;
			int headBiasGap = result[0].first < result[0].second ? result[0].second : result[0].first;
			headBiasGap -= headGap;
			vector<pair<int, string> >tempString;
			for (int j = 0; j < headGap; j++, x++)
			{
				cout << setw(3) << setiosflags(ios::left) << "*";
				odds[x].first = 1;

				string char1(1, strLong[result[i].second - j - 1]);
				string char2(1, strShort[result[i].first - j - 1]);
				odds[x].second.push_back(make_pair(1, revise + char1));
				odds[x].second.push_back(make_pair(1, revise + char2));
			}
			for (int j = 0; j < headBiasGap-headGap; j++)
			{
				if(j==0)
					odds[0].second.push_back(make_pair(1, add));
				odds[0].first = 1;
				if (result[0].first > result[0].second)
					odds[0].second[0].second.push_back(strShort[result[0].first - headBiasGap + j]);
				else
					odds[0].second[0].second.push_back(strLong[result[0].second - headBiasGap + j]);
			}
			cout << setw(3) << setiosflags(ios::left) << strLong[result[i].second];
			odds[x].first = 2;
			pairStr.push_back(strLong[result[i].second]);
		}
		else
		{
			int middleGap = result[i].first - result[i - 1].first > result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			int middleBiasGap = result[i].first - result[i - 1].first < result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			middleBiasGap -= middleGap;
			for (int j = 0; j < middleGap - 1; j++, x++)
			{
				cout << setw(3) << setiosflags(ios::left) << "*";
				odds[x].first = 1;
				string char1(1, strLong[result[i - 1].second + j + 1]);
				string char2(1, strShort[result[i - 1].first + j + 1]);
				odds[x].second.push_back(make_pair(1, revise + char1));
				odds[x].second.push_back(make_pair(1, revise + char2));
			}
			for (int j = 0; j < middleBiasGap; j++)
			{
				if (j == 0)
					odds[x-1].second.push_back(make_pair(1, add));
				if (result[i].first - result[i - 1].first > result[i].second - result[i - 1].second)
					odds[x-1].second.back().second.push_back(strShort[result[i].first - middleBiasGap + j]);
				else
					odds[x-1].second.back().second.push_back(strLong[result[i].second - middleBiasGap + j]);
			}
			cout << setw(3) << setiosflags(ios::left) << strLong[result[i].second];
			odds[x].first = 2;
			pairStr.push_back(strLong[result[i].second]);
		}
	}
	odds[0].first = 2;
	return NULL;
}
int main()
{
	//char str1[50] = "babcnabcd";
	//char str2[50] = "aabcdbcd";
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
	//char str1[128] = "abcdfgfgfgaaaa";
	//char str2[128] = "abcdgfgfgfaaaa";  //Done
	char str1[50] = "XXXabcdab";
	char str2[50] = "xxxabcdabcd";  //Done
	//cout << "Please input the first string:";
	//cin >> str1;
	//cout << "Please input the second string:";
	//cin >> str2;

	GetCommonString(str1, str2);

	return 0;
}