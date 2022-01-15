#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

vector<pair<int, int> > GetIntersectionOfMatrix(const string str1, const string str2, pair<int, int> tlPoint, pair<int, int> brPoint)    // 求区域内匹配字数最多的子串集合
{
	if (str1.empty() || str2.empty())
	{
		return {};
	}
	const int length1 = static_cast<int>(str1.size());
	const int length2 = static_cast<int>(str2.size());

	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= length2 || brPoint.second >= length1)
		return {};

	//寻找两个字符串中的公共子串
	vector<vector<int> > dp(length2, vector<int>(length1, 0));
	cout << "   ";

	for (int j = 0; j < length1; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << str1[j];
	}
	cout << "\n";
	for (int i = 0; i < length2; i++)
	{
		cout << setw(3) << setiosflags(ios::left) << str2[i];
		for (int j = 0; j < length1; j++)
		{
			if (str2[i] == str1[j])
			{
				dp[i][j] = 1;
			}
			else
				dp[i][j] = 0;
			cout << setw(3) << setiosflags(ios::left) << dp[i][j];
		}
		cout << "\n";
	}

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
			else
			{
				pointX += 1;
				pointY += 1;
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
							//rightLength++;
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
							//rightLength++;
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
					if (str1[bottomprobeX] > str2[bottomprobeX])
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
typedef struct
{
	string pairStr;
	vector<pair<int, vector<pair<int, string> > > >  odds;
}MergeFrameResult;

MergeFrameResult GetUnionOfStrings(MergeFrameResult mergedResult1, MergeFrameResult mergedResult2)
{
	MergeFrameResult fusionResult;
	if (mergedResult1.pairStr.empty() || mergedResult2.pairStr.empty())
	{
		return fusionResult;
	}
	const string str1 = mergedResult1.pairStr;
	const string str2 = mergedResult2.pairStr;
	const int length1 = static_cast<int>(str1.size());
	const int length2 = static_cast<int>(str2.size());
	string revise(1, '*');
	string add(1, '+');
	vector<pair<int, int> >result = GetIntersectionOfMatrix(str1, str2, make_pair(0, 0), make_pair(length2 - 1, length1 - 1));

	vector<pair<int, vector<pair<int, string> > > >& mainOdds = mergedResult1.odds;
	vector<pair<int, vector<pair<int, string> > > >& tempOdds = mergedResult2.odds;

	if (mergedResult1.odds[0].first < mergedResult2.odds[0].first)
	{
		mainOdds = mergedResult2.odds;
		tempOdds = mergedResult1.odds;
	}
	for (int i = 0, x = 1; i < static_cast<int>(result.size()); i++, x++) //假设横大
	{
		if (i != 0 && (result[i].first == result[i - 1].first + 1 && result[i].second == result[i - 1].second + 1))
		{
			mainOdds[result[i].second + 1].first += tempOdds[result[i].first + 1].first;
			mainOdds[result[i].second + 1].second.insert(mainOdds[result[i].second + 1].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
		else if (i == 0)
		{
			int headGap = result[0].first > result[0].second ? result[0].second : result[0].first;
			int headBiasGap = result[0].first < result[0].second ? result[0].second : result[0].first;
			headBiasGap -= headGap;
			vector<pair<int, string> >tempString;
			for (int j = 0; j < headGap; j++, x++)
			{
				string char1(1, str1[result[i].second - j - 1]);
				string char2(1, str2[result[i].first - j - 1]);
				if (str1[result[i].second - j - 1] == '*' || str2[result[i].second - j - 1] == '*')
				{
					if (str1[result[i].second - j - 1] == '*')
						mainOdds[result[i].second - j].second.push_back(make_pair(tempOdds[result[i].first - j].first, revise + char2));
					else if (str2[result[i].second - j - 1] == '*')
						mainOdds[result[i].second - j].second.push_back(make_pair(tempOdds[result[i].second - j].first, revise + char1));
				}
				else
				{
					mainOdds[result[i].second + 1].second.push_back(make_pair(1, revise + char1));
					mainOdds[result[i].second + 1].second.push_back(make_pair(1, revise + char2));
				}
				mainOdds[result[i].second - j].second.insert(mainOdds[result[i].second - j].second.end(), tempOdds[result[i].first - j].second.begin(), tempOdds[result[i].first - j].second.end());
			}
			for (int j = 0; j < (headBiasGap - headGap); j++)
			{
				if (j == 0)
					mainOdds[0].second.push_back(make_pair(tempOdds[0].first, add));
				if (result[0].first > result[0].second)
					mainOdds[0].second[0].second.push_back(str2[result[0].first - headBiasGap + j]);
				else
					mainOdds[0].second[0].second.push_back(str1[result[0].second - headBiasGap + j]);
			}
			mainOdds[result[i].second + 1].first += tempOdds[result[i].first + 1].first;
			mainOdds[result[i].second + 1].second.insert(mainOdds[result[i].second + 1].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
		else
		{
			int middleGap = result[i].first - result[i - 1].first > result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			int middleBiasGap = result[i].first - result[i - 1].first < result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			middleBiasGap -= middleGap;
			for (int j = 0; j < (middleGap - 1); j++, x++)
			{
				string char1(1, str1[result[i].second - j - 1]);
				string char2(1, str2[result[i].first - j - 1]);
				if (str1[result[i].second - j - 1] == '*' || str2[result[i].second - j - 1] == '*')
				{
					if (str1[result[i].second - j - 1] == '*')
						mainOdds[result[i].second - j].second.push_back(make_pair(tempOdds[result[i].first - j].first, revise + char2));
					else if (str2[result[i].second - j - 1] == '*')
						mainOdds[result[i].second - j].second.push_back(make_pair(tempOdds[result[i].second - j].first, revise + char1));
				}
				else
				{
					mainOdds[result[i].second + 1].second.push_back(make_pair(1, revise + char1));
					mainOdds[result[i].second + 1].second.push_back(make_pair(1, revise + char2));
				}
			}
			for (int j = 0; j < middleBiasGap; j++)
			{
				if (j == 0)
					mainOdds[x - 1].second.push_back(make_pair(1, add));
				if (result[i].first - result[i - 1].first > result[i].second - result[i - 1].second)
					mainOdds[x - 1].second.back().second.push_back(str2[result[i].first - middleBiasGap + j]);
				else
					mainOdds[x - 1].second.back().second.push_back(str1[result[i].second - middleBiasGap + j]);
			}
			mainOdds[result[i].second + 1].first += tempOdds[result[i].first + 1].first;
			mainOdds[result[i].second + 1].second.insert(mainOdds[result[i].second + 1].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
		if (i == static_cast<int>(result.size()) - 1 && (length2 - result[i].first > 0 || length1 - result[i].second > 0))
		{
			int lastGap = length2 - result[i].first > length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			int lastBiasGap = length2 - result[i].first < length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			lastBiasGap -= lastGap;

			for (int j = 0; j < (lastGap - 1); j++, x++)
			{
				string char1(1, str1[result[i].second + j + 1]);
				string char2(1, str2[result[i].first + j + 1]);
				if (str1[result[i].second + j + 1] == '*' || str2[result[i].second + j + 1] == '*')
				{
					if (str1[result[i].second + j + 1] == '*')
						mainOdds[result[i].second + j + 2].second.push_back(make_pair(tempOdds[result[i].first + j + 2].first, revise + char2));
					else if (str2[result[i].first + j + 1] == '*')
						mainOdds[result[i].second + j + 2].second.push_back(make_pair(mainOdds[result[i].second + j + 2].first, revise + char1));
				}
				else
				{
					mainOdds[result[i].second + 1].second.push_back(make_pair(mainOdds[result[i].second + 1].first, revise + char1));
					mainOdds[result[i].second + 1].second.push_back(make_pair(tempOdds[result[i].first + 1].first, revise + char2));
				}
			}
			for (int j = 0; j <= lastBiasGap; j++)
			{
				if (j == 0)
					mainOdds[x].second.push_back(make_pair(tempOdds[result[i].first + 1].first, add));
				if (length2 - result[i].first > length1 - result[i].second)
					mainOdds[x].second.back().second.push_back(str2[result[i].first + j + 1]);
				else
					mainOdds[x].second.back().second.push_back(str1[result[i].second + j + 1]);
			}
			//mainOdds[result[i].second + 1].first += tempOdds[result[i].first + 1].first;
			//mainOdds[result[i].second + 1].second.insert(mainOdds[result[i].second + 1].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
	}

	return fusionResult;
}

MergeFrameResult GetIntersectionOfStrings(const string str1, const string str2)
{
	MergeFrameResult fusionResult;
	if (str1.empty() || str2.empty())
	{
		return fusionResult;
	}
	const int length1 = static_cast<int>(str1.size());
	const int length2 = static_cast<int>(str2.size());

	vector<pair<int, int> >result = GetIntersectionOfMatrix(str1, str2, make_pair(0, 0), make_pair(length2 - 1, length1 - 1));

	cout << "StringOne: ";
	for (int j = 0; j < length1; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << str1[j];
	}
	cout << "\n" << "StringTwo: ";
	for (int j = 0; j < length2; j++)
	{
		cout << setw(3) << setiosflags(ios::left) << str2[j];
	}
	cout << "\n" << "StringMix: ";
	string pairStr;
	vector<pair<int, vector<pair<int, string> > > > odds(max(str1.size(), str2.size()) + 1);
	vector<pair<int, string> > temp;
	for (int i = 0; i < str1.size(); i++)
	{
		odds.push_back(make_pair(0, temp));
	}
	string revise(1, '*');
	string add(1, '+');

	for (int i = 0, x = 1; i < static_cast<int>(result.size()); i++, x++)
	{
		if (i != 0 && (result[i].first == result[i - 1].first + 1 && result[i].second == result[i - 1].second + 1))
		{
			cout << setw(3) << setiosflags(ios::left) << str1[result[i].second];
			pairStr.push_back(str1[result[i].second]);
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
				pairStr.push_back('*');
				string char1(1, str1[result[i].second - j - 1]);
				string char2(1, str2[result[i].first - j - 1]);
				odds[x].second.push_back(make_pair(1, revise + char1));
				odds[x].second.push_back(make_pair(1, revise + char2));
			}
			for (int j = 0; j < headBiasGap - headGap; j++)
			{
				if (j == 0)
					odds[0].second.push_back(make_pair(1, add));
				odds[0].first = 1;
				if (result[0].first > result[0].second)
					odds[0].second[0].second.push_back(str2[result[0].first - headBiasGap + j]);
				else
					odds[0].second[0].second.push_back(str1[result[0].second - headBiasGap + j]);
			}
			cout << setw(3) << setiosflags(ios::left) << str1[result[i].second];
			odds[x].first = 2;
			pairStr.push_back(str1[result[i].second]);
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
				pairStr.push_back('*');
				string char1(1, str1[result[i - 1].second + j + 1]);
				string char2(1, str2[result[i - 1].first + j + 1]);
				odds[x].second.push_back(make_pair(1, revise + char1));
				odds[x].second.push_back(make_pair(1, revise + char2));
			}
			for (int j = 0; j < middleBiasGap; j++)
			{
				if (j == 0)
					odds[x - 1].second.push_back(make_pair(1, add));
				if (result[i].first - result[i - 1].first > result[i].second - result[i - 1].second)
					odds[x - 1].second.back().second.push_back(str2[result[i].first - middleBiasGap + j]);
				else
					odds[x - 1].second.back().second.push_back(str1[result[i].second - middleBiasGap + j]);
			}
			cout << setw(3) << setiosflags(ios::left) << str1[result[i].second];
			odds[x].first = 2;
			pairStr.push_back(str1[result[i].second]);
		}
		if (i == static_cast<int>(result.size()) - 1 && (length2 - result[i].first > 0 || length1 - result[i].second > 0))
		{
			int lastGap = length2 - result[i].first > length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			int lastBiasGap = length2 - result[i].first < length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			lastBiasGap -= lastGap;
			x++;
			for (int j = 0; j < lastGap - 1; j++, x++)
			{
				cout << setw(3) << setiosflags(ios::left) << "*";
				odds[x].first = 1;
				pairStr.push_back('*');
				string char1(1, str1[result[i].second + j + 1]);
				string char2(1, str2[result[i].first + j + 1]);
				odds[x].second.push_back(make_pair(1, revise + char1));
				odds[x].second.push_back(make_pair(1, revise + char2));
			}
			for (int j = 0; j <= lastBiasGap; j++)
			{
				if (j == 0)
					odds[x].second.push_back(make_pair(1, add));
				else
				{
					if (length2 - result[i].first > length1 - result[i].second)
						odds[x].second.back().second.push_back(str2[result[i].first + j + 1]);
					else
						odds[x].second.back().second.push_back(str1[result[i].second + j + 1]);
				}
			}
		}
	}
	cout << "\n";
	odds[0].first = 2;
	fusionResult.pairStr = pairStr;
	fusionResult.odds = odds;
	return fusionResult;
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
	//char str1[50] = "abcdfgfgfgabab";
	//char str2[50] = "abcdgfgfgfbaba";  
	//char str1[50] = "abcdeabc";
	//char str2[50] = "abcedabc";  
	//char str1[128] = "abcdfgfgfgaaaa";
	//char str2[128] = "abcdgfgfgfaaaa";  
	char str1[50] = "XXXabadabg";
	char str2[50] = "xxxabcdabcd";
	//char str1[50] = "XXXXXXXabcdab";
	//char str2[50] = "xxxabcdabcd";  

	char str3[50] = "xXXabcdabcd";

	GetUnionOfStrings(GetIntersectionOfStrings(str1, str2), GetIntersectionOfStrings(str2, str3));

	return 0;
}