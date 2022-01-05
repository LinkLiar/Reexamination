#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

vector<pair<int, pair<int, int> > > GetLongCommonSubstring(const vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint)
{
	vector<vector<int> > dpLength = dp;
	int maxLength = 0;
	vector<pair<int, pair<int, int> > > maxLocation;
	if (dp.size() < 1 || dp[0].size() < 1 || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
	{
		return {};
	}

	for (int i = brPoint.first; i >= tlPoint.first; i--)
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
	//cout << "\n";
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

vector<pair<int, int>> GetMatchingString(vector<vector<int> > dp, pair<int, int> tlPoint, pair<int, int> brPoint)
{
	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= dp.size() || brPoint.second >= dp[0].size())
		return {};
	vector<pair<int, pair<int, int> > >dpLength = GetLongCommonSubstring(dp, tlPoint, brPoint);
	if (dpLength.empty())
		return {};
	int maxMatchTime = 0;
	int maxID = -1;
	vector<pair<int, int> >result;
	vector<pair<int, int> >tempResult;
	vector<pair<int, int> >maxTLArea;
	vector<pair<int, int> >maxBRArea;

	for (int i = 0; i < dpLength.size(); i++)
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
	if (maxID != -1)
	{
		for (int i = dpLength[maxID].first; i > 0; i--)
			tempResult.push_back(make_pair(dpLength[maxID].second.first - i + 1, dpLength[maxID].second.second - i + 1));
		tempResult.insert(tempResult.begin(), maxTLArea.begin(), maxTLArea.end());
		tempResult.insert(tempResult.end(), maxBRArea.begin(), maxBRArea.end());
		return tempResult;
	}
	for (int i = dpLength[0].first; i > 0; i--)
		tempResult.push_back(make_pair(dpLength[0].second.first - i + 1, dpLength[0].second.second - i + 1));
	return tempResult;

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
	if (stringLen2 > stringLen1)
	{
		strLong = str2;
		strShort = str1;
		longLength = stringLen2;
		shortLength = stringLen1;
	}
	//寻找两个字符串中的公共子串
	//vector<vector<int> > result;
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
	//for (int i = 0; i < stringLen1; i++)
	//{
	//	for (int j = 0; j < stringLen2; j++)
	//	{
	//		if (str1[i] == str2[j])
	//		{
	//			if (j > 0 && i > 0 && dp[i - 1][j - 1] != 0)
	//				dp[i][j] = dp[i - 1][j - 1] + 1;
	//			else
	//				dp[i][j] = 1;
	//			if (dp[i][j] > maxLength)
	//			{
	//				maxLength = dp[i][j];
	//				maxLocation.clear();
	//				maxLocation.push_back(make_pair(i, j));
	//			}
	//			else if (dp[i][j] == maxLength)
	//				maxLocation.push_back(make_pair(i, j));

	//		}
	//		else
	//			dp[i][j] = 0;
	//		cout << setw(3) << setiosflags(ios::left) <<dp[i][j];
	//	}
	//	cout << "\n";
	//}
	//vector<vector<int> > dpLength = dp;
	//int maxLength = 0;
	//vector<pair<int, pair<int, int> > > maxLocation;
	//for (int i = stringLen1-1; i >-1; i--)
	//{
	//	for (int j = stringLen2-1; j >-1; j--)
	//	{
	//		if (dpLength[i][j] == 1)
	//		{
	//			int length = 1;
	//			int tempi = i > 0 ? i - 1:0;
	//			int tempj = j > 0 ? j - 1:0;
	//			while (tempi >=0 && tempj >=0 && dpLength[tempi][tempj])
	//			{
	//				length++;
	//				dpLength[tempi][tempj] = 0;
	//				tempi--;
	//				tempj--;
	//			}
	//			dpLength[i][j] = length;
	//			if (length > maxLength)
	//			{
	//				maxLength = length;
	//				maxLocation.clear();
	//				maxLocation.push_back(make_pair(length, make_pair(i, j)));
	//			}
	//			else if (dp[i][j] == maxLength)
	//				maxLocation.push_back(make_pair(length, make_pair(i, j)));
	//		}
	//	}
	//}

	//vector<pair<int, pair<int, int> > >dpLength = GetLongCommonSubstring(dp, make_pair(0, 0), make_pair(stringLen1 - 1, stringLen2 - 1));

	vector<pair<int, int> >result = GetMatchingString(dp, make_pair(0, 0), make_pair(shortLength - 1, longLength - 1));
	//cout << "\n";
	//for (int i = 0; i < stringLen1; i++)
	//{
	//	for (int j = 0; j < stringLen2; j++)
	//	{
	//		cout <<setw(3) << setiosflags(ios::left) << dp[i][j] ;
	//	}
	//	cout << "\n";
	//}
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




bool isCountinueFindString(char* str1, char* str2)
{
	return 1;
}

int main()
{
	//char str1[50]="abcmabcd";
	//char str2[50]="abcdabc";
	char str1[50] = "abcdabcbdeabckk";
	char str2[50] = "kkabceabcdecabc";
	//cout << "Please input the first string:";
	//cin >> str1;
	//cout << "Please input the second string:";
	//cin >> str2;

	GetCommonString(str1, str2);

	return 0;
}