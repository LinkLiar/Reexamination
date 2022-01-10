#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<pair<int, pair<int, int> > > GetLongCommonSubstring(const vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint)
{
	vector<vector<int> > dpLength = dp;
	int maxLength = 0;
	vector<pair<int, pair<int, int> > > maxLocation;
	if (dp.size() < 1 || dp[0].size() < 1 || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
		return {};

	for (int i = brPoint.first; i >= tlPoint.first; i--)    // 找出全部最长子串的位置
	{
		for (int j = brPoint.second; j >= tlPoint.second; j--)
		{
			if (dpLength[i][j] == 1)
			{
				int length = 1;
				int tempi = i > 0 ? i - 1 : 0;
				int tempj = j > 0 ? j - 1 : 0;
				while (tempi >= tlPoint.first && tempj >= tlPoint.second && dpLength[tempi][tempj])
				{
					length++;
					dpLength[tempi][tempj] = 0;
					tempi--;
					tempj--;
				}
				dpLength[i][j] = length;
				if (length > maxLength)
				{
					maxLength = length;
					maxLocation.clear();
					maxLocation.push_back(make_pair(length, make_pair(i, j)));
				}
				else if (length == maxLength)
					maxLocation.push_back(make_pair(length, make_pair(i, j)));
			}
		}
	}
	//cout << "\n";    // 显示最长子串所在矩阵的位置
	//for (int i = brPoint.first; i >= tlPoint.first; i--)
	//{
	//	for (int j = brPoint.second; j >= tlPoint.second; j--)
	//	{
	//		cout <<setw(3) << setiosflags(ios::left) << dpLength[i][j] ;
	//	}
	//	cout << "\n";
	//}
	return maxLocation;
}

vector<pair<int, int>> GetMatchingString(vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint)    // 求区域内匹配字数最多的子串集合
{
	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
		return {};
	vector<pair<int, pair<int, int> > >dpLength = GetLongCommonSubstring(dp, tlPoint, brPoint);
	if (dpLength.empty())
		return {};
	int maxMatchTime = 0;
	int maxID = -1;
	vector<int>isCountinueSearch;
	vector<pair<int, int> >tempResult;
	vector<pair<int, int> >maxTLArea;
	vector<pair<int, int> >maxBRArea;

	for (int i = 0; i < dpLength.size(); i++)    // 求左上区域与右下区域的匹配字数最多的子串集合
	{
		vector<pair<int, int> >tlArea = GetMatchingString(dp, tlPoint, make_pair(dpLength[i].second.first - dpLength[i].first, dpLength[i].second.second - dpLength[i].first));
		vector<pair<int, int> >brArea = GetMatchingString(dp, make_pair(dpLength[i].second.first + 1, dpLength[i].second.second + 1), brPoint);
		if (tlArea.size() + brArea.size() > maxMatchTime)
		{
			maxMatchTime = tlArea.size() + brArea.size();
			maxID = i;
			maxTLArea = tlArea;
			maxBRArea = brArea;
		}

	}
	if (maxID != -1)    // 若左上右下区域内存在子串集合
	{
		for (int i = dpLength[maxID].first; i > 0; i--)
			tempResult.push_back(make_pair(dpLength[maxID].second.first - i + 1, dpLength[maxID].second.second - i + 1));
		tempResult.insert(tempResult.begin(), maxTLArea.begin(), maxTLArea.end());
		tempResult.insert(tempResult.end(), maxBRArea.begin(), maxBRArea.end());

		int leftAreaMin = min(dpLength[maxID].second.second - dpLength[maxID].first + 1 - tlPoint.second, dpLength[maxID].first);
		int buttomAreaMin = min(brPoint.first - dpLength[maxID].second.first, dpLength[maxID].first);
		int rightAreaMin = min(brPoint.second - dpLength[maxID].second.second, dpLength[maxID].first);
		int upAreaMin = min(dpLength[maxID].second.first - tlPoint.first - dpLength[maxID].first + 1, dpLength[maxID].first);


		if (tempResult.size() != 1 && (tempResult.size() < (leftAreaMin + buttomAreaMin + 2) || tempResult.size() < (upAreaMin + rightAreaMin + 2)))    // 判断左与下区域和上与右区域是否可能有匹配字数更多的子串集合
			/*		printf("unsolve\n");*/
		{
			vector<pair<int, int> >leftArea = GetMatchingString(dp, make_pair(dpLength[maxID].second.first - dpLength[maxID].first + 1, tlPoint.second), make_pair(dpLength[maxID].second.first, dpLength[maxID].second.second - dpLength[maxID].first));
			vector<pair<int, int> >buttomArea = GetMatchingString(dp, make_pair(dpLength[maxID].second.first, dpLength[maxID].second.second - dpLength[maxID].first + 1), make_pair(brPoint.first, dpLength[maxID].second.second));

			vector<pair<int, int> >upArea = GetMatchingString(dp, make_pair(tlPoint.first, dpLength[maxID].second.second - dpLength[maxID].first + 1), make_pair(dpLength[maxID].second.first - dpLength[maxID].first + 1, dpLength[maxID].second.second));
			vector<pair<int, int> >rightArea = GetMatchingString(dp, make_pair(dpLength[maxID].second.first - dpLength[maxID].first + 1, dpLength[maxID].second.second), make_pair(dpLength[maxID].second.first, brPoint.second));

			int lbAreaLength = tempResult.size();
			int urAreaLength = lbAreaLength;
			if (leftArea.size() != 0 && buttomArea.size() != 0 && (leftArea.size() + buttomArea.size()) > tempResult.size())
			{
				if (leftArea[leftArea.size() - 1].first == buttomArea[0].first || leftArea[leftArea.size() - 1].second == buttomArea[0].second)
				{
					if (leftArea.size() >= buttomArea.size())
						buttomArea.erase(buttomArea.begin());
					else
						leftArea.pop_back();
					lbAreaLength = leftArea.size() + buttomArea.size() - 1;
				}
				if (upArea[upArea.size() - 1].first == rightArea[0].first || upArea[upArea.size() - 1].second == rightArea[0].second)
				{
					if (upArea.size() >= rightArea.size())
						rightArea.erase(rightArea.begin());
					else
						upArea.pop_back();
					urAreaLength = upArea.size() + rightArea.size() - 1;
				}

				if (lbAreaLength > urAreaLength && urAreaLength != tempResult.size())
				{
					tempResult.clear();
					tempResult.insert(tempResult.end(), leftArea.begin(), leftArea.end());
					tempResult.insert(tempResult.end(), buttomArea.begin(), buttomArea.end());
				}
				else if (lbAreaLength < urAreaLength&& lbAreaLength != tempResult.size())
				{
					tempResult.clear();
					tempResult.insert(tempResult.end(), leftArea.begin(), leftArea.end());
					tempResult.insert(tempResult.end(), buttomArea.begin(), buttomArea.end());
				}
			}
			return tempResult;
		}
		else
			return tempResult;
	}
	else    // 若左上右下区域内不存在子串集合
	{
		for (int i = dpLength[0].first; i > 0; i--)
			tempResult.push_back(make_pair(dpLength[0].second.first - i + 1, dpLength[0].second.second - i + 1));
		int leftAreaMin = min(dpLength[0].second.second - dpLength[0].first + 1 - tlPoint.second, dpLength[0].first);
		int buttomAreaMin = min(brPoint.first - dpLength[0].second.first, dpLength[0].first);
		int rightAreaMin = min(brPoint.second - dpLength[0].second.second, dpLength[0].first);
		int upAreaMin = min(dpLength[0].second.first - tlPoint.first - dpLength[0].first + 1, dpLength[0].first);


		if (tempResult.size() != 1 && (tempResult.size() < (leftAreaMin + buttomAreaMin + 2) || tempResult.size() < (upAreaMin + rightAreaMin + 2)))    // 判断左与下区域和上与右区域是否可能有匹配字数更多的子串集合
			/*		printf("unsolve\n");*/
		{
			vector<pair<int, int> >leftArea = GetMatchingString(dp, make_pair(dpLength[0].second.first - dpLength[0].first + 1, tlPoint.second), make_pair(dpLength[0].second.first, dpLength[0].second.second - dpLength[0].first));
			vector<pair<int, int> >buttomArea = GetMatchingString(dp, make_pair(dpLength[0].second.first, dpLength[0].second.second - dpLength[0].first + 1), make_pair(brPoint.first, dpLength[0].second.second));

			vector<pair<int, int> >upArea = GetMatchingString(dp, make_pair(tlPoint.first, dpLength[0].second.second - dpLength[0].first + 1), make_pair(dpLength[0].second.first - dpLength[0].first + 1, dpLength[0].second.second));
			vector<pair<int, int> >rightArea = GetMatchingString(dp, make_pair(dpLength[0].second.first - dpLength[0].first + 1, dpLength[0].second.second), make_pair(dpLength[0].second.first, brPoint.second));

			int lbAreaLength = tempResult.size();
			int urAreaLength = lbAreaLength;
			if (leftArea.size() != 0 && buttomArea.size() != 0 && (leftArea.size() + buttomArea.size()) > tempResult.size())
			{
				if (leftArea[leftArea.size() - 1].first == buttomArea[0].first || leftArea[leftArea.size() - 1].second == buttomArea[0].second)    // 左与下区域子串集合有冲突
				{
					if (leftArea.size() >= buttomArea.size())    // 删除短子串中冲突的位置，使其保留长串中
						buttomArea.erase(buttomArea.begin());
					else
						leftArea.pop_back();
					lbAreaLength = leftArea.size() + buttomArea.size() - 1;
				}
				if (upArea[upArea.size() - 1].first == rightArea[0].first || upArea[upArea.size() - 1].second == rightArea[0].second)    // 右与上区域子串集合有冲突
				{
					if (upArea.size() >= rightArea.size())    // 删除短子串中冲突的位置，使其保留长串中
						rightArea.erase(rightArea.begin());
					else
						upArea.pop_back();
					urAreaLength = upArea.size() + rightArea.size() - 1;
				}

				if (lbAreaLength > urAreaLength && urAreaLength != tempResult.size())    // 左与下区域存在匹配字数更多的子串集合
				{
					tempResult.clear();
					tempResult.insert(tempResult.end(), leftArea.begin(), leftArea.end());
					tempResult.insert(tempResult.end(), buttomArea.begin(), buttomArea.end());
				}
				else if (lbAreaLength < urAreaLength && lbAreaLength != tempResult.size())    // 右与上区域存在匹配字数更多的子串集合
				{
					tempResult.clear();
					tempResult.insert(tempResult.end(), leftArea.begin(), leftArea.end());
					tempResult.insert(tempResult.end(), buttomArea.begin(), buttomArea.end());
				}
			}
			return tempResult;
		}
		else
			return tempResult;
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
	char str1[50] = "abcdfgfgfgaaaa";
	char str2[50] = "abcdgfgfgfaaaa";
	//cout << "Please input the first string:";
	//cin >> str1;
	//cout << "Please input the second string:";
	//cin >> str2;

	GetCommonString(str1, str2);

	return 0;
}