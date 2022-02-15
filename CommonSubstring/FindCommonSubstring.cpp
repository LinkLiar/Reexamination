#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <time.h>

#define SIZE 5
using namespace std;

typedef struct
{
	string pairStr;
	vector<pair<int, vector<pair<int, string> > > >odds;
}MergeFrameResult;

vector<pair<int, int> > GetIntersectionOfMatrix(const string str1, const string str2, pair<int, int> tlPoint, pair<int, int> brPoint, vector<pair<int, vector<pair<int, string> > > >mainOdds, vector<pair<int, vector<pair<int, string> > > >tempOdds)    // 求区域内匹配字数最多的子串集合
{
	if (str1.empty() || str2.empty())
		return {};

	const int length1 = static_cast<int>(str1.size());
	const int length2 = static_cast<int>(str2.size());

	if (tlPoint.first > brPoint.first || tlPoint.second > brPoint.second || tlPoint.first < -1 || tlPoint.second < -1 || brPoint.first >= length2 || brPoint.second >= length1)
		return {};

	vector<vector<int> > dp(length2, vector<int>(length1, 0));

	//cout << "   ";
	//for (int j = 0; j < length1; j++)
	//{
	//	cout << setw(3) << setiosflags(ios::left) << str1[j];
	//}
	//cout << "\n";
	//for (int i = 0; i < length2; i++)
	//{
	//	cout << setw(3) << setiosflags(ios::left) << str2[i];
	//	for (int j = 0; j < length1; j++)
	//	{
	//		if (str2[i] == str1[j])
	//			dp[i][j] = 1;
	//		else
	//			dp[i][j] = 0;
	//		cout << setw(3) << setiosflags(ios::left) << dp[i][j];
	//	}
	//	cout << "\n";
	//}

	for (int i = 0; i < length2; i++)
	{
		for (int j = 0; j < length1; j++)
		{
			if (str2[i] == str1[j])
				dp[i][j] = 1;
			else
				dp[i][j] = 0;
		}
	}

	int rows = brPoint.first + 1;
	int cols = brPoint.second + 1;
	int pointX = tlPoint.first;
	int pointY = tlPoint.second;
	int missCount = 1;
	int missCountMax = 1;
	vector<pair<int, int> >result;

	while (true)
	{
		if (pointX < rows && pointY < cols && dp[pointX][pointY])
		{
			missCount = 1;
			result.push_back(make_pair(pointX, pointY));
			int probeX = pointX + 1;
			int probeY = pointY + 1;
			int probeLength = 1;

			if (probeX < rows && probeY < cols && dp[probeX][probeY])
			{
				while ((probeX < rows && probeY < cols) && dp[probeX][probeY])
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
							breakFlag = 1;
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
							breakFlag = 1;
						for (; rightLength > 0; --rightLength, i++, j++)
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
							breakFlag = 1;
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
							breakFlag = 1;
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
					int i, j, bottomScore = 0, rightScore = 0;

					for (int rx = rightprobeX - rightLength, ry = rightprobeY - rightLength; rx < rightprobeX; ++rx)
					{
						rightScore += mainOdds[rx + 1].first;
						rightScore += tempOdds[ry + 1].first;
					}
					for (int bx = bottomprobeX - bottomLength, by = bottomprobeY - bottomLength; bx < bottomprobeX; ++bx)
					{
						bottomScore += mainOdds[bx + 1].first;
						bottomScore += tempOdds[by + 1].first;
					}
					if ((rightScore > bottomScore) || ((rightScore > bottomScore) && (str1[bottomprobeX] > str2[bottomprobeX])))
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
					missCountMax = missCount;
					if (missCount > min(brPoint.first - tlPoint.first, brPoint.second - tlPoint.second) / 2)
						return {};
					if (!(pointX + missCount < rows || pointY + missCount < cols))
						break;
					int bottomMax = 0;
					int bottomMaxID = 0;
					int rightMax = 0;
					int rightMaxID = 0;
					if (pointX + missCount < rows)
					{
						for (int i = 0; i <= missCount; i++)
						{
							if (pointY + i < cols && dp[pointX + missCount][pointY + i])
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
					}
					if (pointY + missCount < cols)
					{
						for (int i = 0; i <= missCount; i++)
						{
							if (pointX + i < rows && dp[pointX + i][pointY + missCount])
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
					}

					if (rightMax == bottomMax && bottomMax == 0)
						continue;
					else if (rightMax == bottomMax && bottomMax == 1)
					{
						int bottomMax = 0;
						int bottomMaxID = 0;
						int rightMax = 0;
						int rightMaxID = 0;
						for (int i = 0; i <= missCount; i++)
						{
							if (dp[pointX + missCount][pointY + i])
							{
								int tempLength = 1;

								while (pointX + missCount + tempLength + 2 < rows && pointY + i + tempLength + 2 < cols && dp[pointX + missCount + tempLength + 2][pointY + i + tempLength + 2])
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
							if (dp[pointX + i][pointY + missCount])
							{
								int tempLength = 1;
								while (pointX + i + tempLength + 2 < rows && pointY + missCount + tempLength + 2 < cols && dp[pointX + i + tempLength + 2][pointY + missCount + tempLength + 2])
									tempLength++;
								if (rightMax < tempLength)
								{
									rightMax = tempLength;
									rightMaxID = pointX + i;
								}
							}
						}
						if (bottomMax > rightMax)
						{
							pointX = pointX + missCount;
							pointY = bottomMaxID;
						}
						else
						{
							pointX = rightMaxID;
							pointY = pointY + missCount;
						}
					}
					else
					{
						if (bottomMax > rightMax)
						{
							pointX = pointX + missCount;
							pointY = bottomMaxID;
						}
						else
						{
							pointX = rightMaxID;
							pointY = pointY + missCount;
						}
					}
				}
			}
		}
	}
	return result;
}

MergeFrameResult GetUnionOfStrings(MergeFrameResult mergedResult1, MergeFrameResult mergedResult2)
{
	MergeFrameResult fusionResult;
	if (mergedResult1.pairStr.empty() || mergedResult2.pairStr.empty())
		return fusionResult;

	string str1 = mergedResult1.pairStr;
	string str2 = mergedResult2.pairStr;

	vector<pair<int, vector<pair<int, string> > > >mainOdds = mergedResult1.odds;
	vector<pair<int, vector<pair<int, string> > > >tempOdds = mergedResult2.odds;

	if (str1.size() < str2.size())
	{
		mainOdds = mergedResult2.odds;
		tempOdds = mergedResult1.odds;
		str1 = mergedResult2.pairStr;
		str2 = mergedResult1.pairStr;
	}
	int length1 = static_cast<int>(str1.size());
	int length2 = static_cast<int>(str2.size());

	string revise(1, '*');
	string add(1, '+');
	string str;
	str.reserve(2 * str1.size());

	vector<pair<int, int> >result = GetIntersectionOfMatrix(str1, str2, make_pair(0, 0), make_pair(length2 - 1, length1 - 1), mainOdds, tempOdds);

	vector<pair<int, vector<pair<int, string> > > >vote;
	vector<pair<int, string> > dummyOdds;
	vote.insert(vote.end(), (max(str1.size(), str2.size()) + 1), make_pair(0, dummyOdds));

	for (int i = 0, x = 1; i < static_cast<int>(result.size()); ++i, ++x)
	{
		if (i != 0 && (result[i].first == result[i - 1].first + 1 && result[i].second == result[i - 1].second + 1))
		{
			str.push_back(str1[result[i].second]);
			vote[x].first = mainOdds[result[i].second + 1].first + tempOdds[result[i].first + 1].first;
			vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second + 1].second.begin(), mainOdds[result[i].second + 1].second.end());
			vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
		else if (i == 0)
		{
			int headGap = result[0].first > result[0].second ? result[0].second : result[0].first;
			int headBiasGap = result[0].first < result[0].second ? result[0].second : result[0].first;
			headBiasGap -= headGap;
			vector<pair<int, string> >tempString;
			string count;
			for (int j = 0; j < headBiasGap; ++j)
			{
				if (result[0].first > result[0].second)
				{
					if (j == 0)
						vote[0].second.push_back(make_pair(0, add));
					vote[0].second.back().second.push_back(str2[j]);
					count.push_back(tempOdds[result[0].first - headBiasGap + j + 1].first + '0');
				}
				else
				{
					vote[x].first = mainOdds[j + 1].first;
					vote[x].second = mainOdds[j + 1].second;
					str.push_back(str1[j]);
					x++;
				}
			}
			if (result[0].first > result[0].second)
			{
				vote[0].second.back().first = atoi(count.c_str());
			}

			for (int j = 0; j < headGap; ++j, ++x)
			{
				str.push_back('*');
				string char1(1, str1[result[i].second - headGap + j]);
				string char2(1, str2[result[i].first - headGap + j]);
				if (str1[result[i].second - headGap + j] == '*' || str2[result[i].second - headGap + j] == '*')
				{
					if (str1[result[i].second - headGap + j] == '*')
						vote[x].second.push_back(make_pair(tempOdds[result[i].first - headGap + j + 1].first, revise + char2));
					else if (str2[result[i].first - headGap + j] == '*')
						vote[x].second.push_back(make_pair(mainOdds[result[i].first - headGap + j + 1].first, revise + char1));
					vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second - headGap + j + 1].second.begin(), mainOdds[result[i].second - headGap + j + 1].second.end());
					vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first - headGap + j + 1].second.begin(), tempOdds[result[i].first - headGap + j + 1].second.end());
				}
				else
				{
					vote[x].second.push_back(make_pair(mainOdds[result[i].second - headGap + j + 1].first, revise + char1));
					vote[x].second.push_back(make_pair(tempOdds[result[i].first - headGap + j + 1].first, revise + char2));
					vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second - headGap + j + 1].second.begin(), mainOdds[result[i].second - headGap + j + 1].second.end());
					vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first - headGap + j + 1].second.begin(), tempOdds[result[i].first - headGap + j + 1].second.end());
				}
			}

			if (result[i].second - 1 >= 0 && result[i].first - 1 >= 0 && !(str1[result[i].second - 1] == '*' || str2[result[i].second - 1] == '*') || (result[i].first > result[i].second))
			{
				vote[0].second.insert(vote[0].second.end(), mainOdds[result[0].second].second.begin(), mainOdds[result[0].second].second.end());
				vote[0].second.insert(vote[0].second.end(), tempOdds[result[0].first].second.begin(), tempOdds[result[0].first].second.end());
			}

			if (result[0].first > result[0].second)
				str.push_back(str2[result[i].first]);
			else
				str.push_back(str1[result[i].second]);
			vote[x].first = mainOdds[result[i].second + 1].first + tempOdds[result[i].first + 1].first;
			vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second + 1].second.begin(), mainOdds[result[i].second + 1].second.end());
			vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
		}
		else
		{
			int middleGap = result[i].first - result[i - 1].first > result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			int middleBiasGap = result[i].first - result[i - 1].first < result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
			middleBiasGap -= middleGap;
			for (int j = 0; j < (middleGap - 1); ++j, ++x)
			{
				str.push_back('*');
				string char1(1, str1[result[i - 1].second + j + 1]);
				string char2(1, str2[result[i - 1].first + j + 1]);
				if (char1[0] == '*' || char2[0] == '*')
				{
					if (char1[0] == '*')
						vote[x].second.push_back(make_pair(tempOdds[result[i - 1].first + j + 2].first, revise + char2));
					else if (char2[0] == '*')
						vote[x].second.push_back(make_pair(mainOdds[result[i - 1].second + j + 2].first, revise + char1));
				}
				else
				{
					vote[x].second.push_back(make_pair(mainOdds[result[i - 1].second + j + 2].first, revise + char1));
					vote[x].second.push_back(make_pair(tempOdds[result[i - 1].first + j + 2].first, revise + char2));
				}
				vote[x].second.insert(vote[x].second.end(), mainOdds[result[i - 1].second + j + 2].second.begin(), mainOdds[result[i - 1].second + j + 2].second.end());
				vote[x].second.insert(vote[x].second.end(), tempOdds[result[i - 1].first + j + 2].second.begin(), tempOdds[result[i - 1].first + j + 2].second.end());
			}
			string count;
			for (int j = 0; j < middleBiasGap; j++)
			{
				if (result[i].first - result[i - 1].first > result[i].second - result[i - 1].second)
				{
					if (j == 0)
						vote[x - 1].second.push_back(make_pair(0, add));
					vote[x - 1].second.back().second.push_back(str2[result[i].first - middleBiasGap + j]);
					count.push_back(tempOdds[result[i - 1].first + j + middleGap].first + '0');
					if (j == middleBiasGap - 1)
					{
						vote[x - 1].second.back().first = atoi(count.c_str());
					}
				}
				else
				{
					vote[x].first = mainOdds[result[i].second + j - result[i].second + result[i - 1].second + 1 + middleGap].first;
					vote[x].second = mainOdds[result[i].second + j - result[i].second + result[i - 1].second + 1 + middleGap].second;
					str.push_back(str1[result[i].second - middleBiasGap + j]);
					++x;
				}
			}
			str.push_back(str1[result[i].second]);
			vote[x].first = mainOdds[result[i].second + 1].first + tempOdds[result[i].first + 1].first;
			vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first + 1].second.begin(), tempOdds[result[i].first + 1].second.end());
			vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second + 1].second.begin(), mainOdds[result[i].second + 1].second.end());
		}
		if (i == static_cast<int>(result.size()) - 1 && (length2 - result[i].first > 0 || length1 - result[i].second > 0))
		{
			++x;
			int lastGap = length2 - result[i].first > length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			int lastBiasGap = length2 - result[i].first < length1 - result[i].second ? length1 - result[i].second : length2 - result[i].first;
			lastBiasGap -= lastGap;

			for (int j = 0; j < (lastGap - 1); ++j, ++x)
			{
				str.push_back('*');
				string char1(1, str1[result[i].second + j + 1]);
				string char2(1, str2[result[i].first + j + 1]);
				if (str1[result[i].second + j + 1] == '*' || str2[result[i].first + j + 1] == '*')
				{
					if (str1[result[i].second + j + 1] == '*')
						vote[x].second.push_back(make_pair(tempOdds[result[i].first + j + 2].first, revise + char2));
					else if (str2[result[i].first + j + 1] == '*')
						vote[x].second.push_back(make_pair(mainOdds[result[i].second + j + 2].first, revise + char1));
				}
				else
				{
					vote[x].second.push_back(make_pair(mainOdds[result[i].second + j + 2].first, revise + char1));
					vote[x].second.push_back(make_pair(tempOdds[result[i].first + j + 2].first, revise + char2));
				}
				vote[x].second.insert(vote[x].second.end(), mainOdds[result[i].second + j + 2].second.begin(), mainOdds[result[i].second + j + 2].second.end());
				vote[x].second.insert(vote[x].second.end(), tempOdds[result[i].first + j + 2].second.begin(), tempOdds[result[i].first + j + 2].second.end());
			}

			if (x == str1.size() + 1)
			{
				--x;
			}
			string count;
			for (int j = 0; j < lastBiasGap; j++)
			{
				if (length2 - result[i].first > length1 - result[i].second)
				{
					if (j == 0)
						vote[x].second.push_back(make_pair(0, add));
					vote[x].second.back().second.push_back(str2[result[i].first + j + 1]);
					count.push_back(tempOdds[result[i].first + j + 2].first + '0');
				}
				else
				{
					vote[x].first = mainOdds[result[i].second + j + lastGap + 1].first;
					vote[x].second = mainOdds[result[i].second + j + lastGap + 1].second;
					str.push_back(str1[result[i].second + j + lastGap]);
					++x;
				}
			}
			if (length2 - result[i].first > length1 - result[i].second)
			{
				vote[x].second.back().first = atoi(count.c_str());
			}

		}
	}

	int matchTime = 0;
	for (int i = 1; i < vote.size(); i++)
	{
		if (matchTime < vote[i].first)
			matchTime = vote[i].first;
	}
	vote[0].first = matchTime;
	string::iterator iterStr = str.begin();
	auto iterOdds = vote.begin();

	for (; iterOdds != vote.end(); ++iterOdds)
	{
		int a = iterOdds - vote.begin();
		if (!iterOdds->second.empty())
		{
			vector<pair<int, string> >& oddPairs = iterOdds->second;
			for (auto subIter = oddPairs.begin(); subIter != oddPairs.end(); ++subIter)    //统计合并相同项
			{
				pair<int, string>& temp = *subIter;
				for (auto next = subIter + 1; next != oddPairs.end(); )
				{
					pair<int, string> nextPair = *next;
					if (temp.second == nextPair.second)
					{
						temp.first += nextPair.first;
						next = oddPairs.erase(next);
					}
					else
						++next;
				}
			}

			for (auto subIter = oddPairs.begin(); subIter != oddPairs.end(); )
			{
				if (subIter->first > (matchTime / 2) && subIter->first < matchTime + 1)
				{
					if (subIter->second[0] == '*')
					{
						*iterStr = subIter->second[1];
						iterOdds->first = subIter->first;
						subIter = oddPairs.erase(subIter);
					}
					else
						++subIter;
				}
				else
					++subIter;
			}

			vector<pair<int, string> >adds;
			int addTime = 0;
			int firstFlag = 0;
			for (auto subIter = oddPairs.begin(); subIter != oddPairs.end(); )
			{
				pair<int, string>& temp = *subIter;
				if (temp.second[0] == '+')
				{
					adds.emplace_back(temp);
					subIter = oddPairs.erase(subIter);
				}
				else
				{
					++subIter;
				}
			}
			if (adds.size() >= 1)
			{
				pair<string, string>final;
				int max = 0;
				pair<int, string> main;
				vector<pair<int, string> >::iterator maxposition;
				for (auto subAdd = adds.begin(); subAdd != adds.end(); ++subAdd)
				{
					if (subAdd->first > max)
					{
						main = *subAdd;
						maxposition = subAdd;
						max = subAdd->first;
					}
				}
				adds.erase(maxposition);
				vector<pair<int, vector<pair<int, string> > > >mainOdd;
				string mainFirst = to_string(main.first);
				mainOdd.push_back(make_pair(0, dummyOdds));
				for (int i = 0; i < mainFirst.size(); ++i)
				{
					mainOdd.push_back(make_pair(mainFirst[i], dummyOdds));
				}
				if (adds.size() != 0)
				{
					bool hasAdded = 0;
					for (auto subAdd = adds.begin(); subAdd != adds.end(); )
					{
						if (subAdd->second != main.second)
						{
							vector<pair<int, vector<pair<int, string> > > >tempOdd;
							string tempFirst = to_string(subAdd->first);
							tempOdd.push_back(make_pair(0, dummyOdds));
							for (int i = 0; i < tempFirst.size(); ++i)
							{
								tempOdd.push_back(make_pair(tempFirst[i] - '0', dummyOdds));
							}

							vector<pair<int, int> >result = GetIntersectionOfMatrix(main.second, subAdd->second, make_pair(0, 0), make_pair(subAdd->second.size() - 1, main.second.size() - 1), mainOdd, tempOdd);

							if (result.size() > 1)
							{
								hasAdded = 1;
								for (int i = 1; i < result.size(); i++)
								{
									if (abs(result[i].first - result[1].second) <= result.size() && result[i].first - result[i - 1].first <= result.size() && result[i].second - result[i - 1].second <= result.size())
									{
										int gap = result[i].first - result[i - 1].first < result[i].second - result[i - 1].second ? result[i].second - result[i - 1].second : result[i].first - result[i - 1].first;
										if (gap > 1)
										{
											for (int j = result[i - 1].second + 1; j < result[i].second; j++)
											{
												final.first.push_back(mainFirst[j - 1]);
												final.second.push_back(main.second[j]);
											}
										}
										final.first.push_back(mainFirst[result[i].second - 1] + tempFirst[result[i].first - 1] - '0');
										final.second.push_back(main.second[result[i].second]);
									}
									if (i == result.size() - 1 && mainFirst.size() > result.size() - 1)
									{
										final.first.insert(final.first.size(), mainFirst, result[i].second, mainFirst.size());
										final.second.insert(final.second.size(), main.second, result[i].second + 1, main.second.size());
									}
								}
								if (result.size() == min(main.second.size(), subAdd->second.size()))
								{
									subAdd = adds.erase(subAdd);
								}
								else
								{
									++subAdd;
								}
							}
							else
							{
								++subAdd;
							}
						}
					}
					if (!hasAdded)
					{
						final.first.insert(final.first.end(), mainFirst.begin(), mainFirst.end());
						final.second.insert(final.second.end(), main.second.begin() + 1, main.second.end());
					}

				}
				else
				{
					final.first.insert(final.first.end(), mainFirst.begin(), mainFirst.end());
					final.second.insert(final.second.end(), main.second.begin() + 1, main.second.end());
				}

				iterOdds->second.insert(iterOdds->second.end(), adds.begin(), adds.end());
				bool hasCreated = 0;
				string tempFirst;

				for (int i = 0; i < final.second.size(); ++i)
				{
					if (final.first[i] - '0' > (matchTime / 2))
					{
						hasCreated = 0;
						if (tempFirst.size() != 0)
						{
							iterOdds->second.back().first = atoi(tempFirst.c_str());
							tempFirst.clear();
						}

						if (iterOdds == vote.begin())
						{
							firstFlag = 1;
							addTime++;
							str.insert(iterStr, final.second[i]);
							iterOdds = vote.insert(++iterOdds, make_pair(final.first[i] - '0', dummyOdds));
						}
						else
						{
							addTime++;
							str.insert(iterStr + 1, final.second[i]);
							if (final.second.size() != 1 && i != final.second.size() - 1)
								iterStr++;
							if (final.second.size() != 1 && i == final.second.size() - 1 && addTime != 1)
								iterStr--;
							iterOdds = vote.insert(++iterOdds, make_pair(final.first[i] - '0', dummyOdds));
						}
					}
					else
					{

						if (!hasCreated)
						{
							iterOdds->second.push_back(make_pair(0, ""));
							hasCreated = 1;
							iterOdds->second.back().second.push_back('+');
						}

						iterOdds->second.back().second.push_back(final.second[i]);
						tempFirst.push_back(final.first[i]);

					}
				}
				if (tempFirst.size() != 0)
				{
					iterOdds->second.back().first = atoi(tempFirst.c_str());
					tempFirst.clear();
				}
			}
			else
			{
				iterOdds->second.insert(iterOdds->second.end(), adds.begin(), adds.end());
			}

			if (addTime != 0)
			{
				if (firstFlag)
					iterStr = iterStr + addTime - 1;
				else
					iterStr = iterStr + addTime;
			}

		}
		if (iterOdds != vote.begin() && iterStr != str.end())
		{
			++iterStr;
		}
	}
	fusionResult.odds = vote;
	fusionResult.pairStr = str;
	return fusionResult;
}

string GetResult(MergeFrameResult& frame)
{
	string& pairStr = frame.pairStr;
	vector<pair<int, vector<pair<int, string> > > >& odds = frame.odds;
	string result;

	for (int i = 0; i < pairStr.size(); i++)
	{
		if (pairStr[i] == '*')
		{
			int maxID = -1;
			int max = 0;
			for (int j = 0; j < odds[i + 1].second.size(); j++)
			{
				if (odds[i + 1].second[j].second[0] == '*')
				{
					if (maxID == -1 || odds[i + 1].second[j].first > max)
					{
						maxID = j;
						max = odds[i + 1].second[j].first;
					}
				}
			}
			pairStr[i] = odds[i + 1].second[maxID].second[1];
			odds[i + 1].first = odds[i + 1].second[maxID].first;
			odds[i + 1].second.erase(odds[i + 1].second.begin() + maxID);
		}
		if (float(odds[i + 1].first) < odds[0].first / 2.0)
		{
			int breakFlag = 0;
			for (auto start = odds[i].second.begin(); start != odds[i].second.end(); )
			{
				if (start->second[1] == pairStr[i] && (odds[i + 1].first + start->first) > odds[0].first / 2.0)
				{
					breakFlag = 1;
					odds[i + 1].first = odds[i + 1].first + start->first;
					start = odds[i].second.erase(start);
					result.push_back(pairStr[i]);
				}
				else
					++start;
			}
			if (!breakFlag && i + 2 < odds.size())
			{
				for (auto start = odds[i + 2].second.begin(); start != odds[i + 2].second.end(); )
				{
					if (start->second[1] == pairStr[i] && (odds[i + 1].first + start->first) > odds[0].first / 2.0)
					{
						breakFlag = 1;
						odds[i + 2].first = odds[i + 2].first + start->first;
						start = odds[i + 2].second.erase(start);
						result.push_back(pairStr[i]);
					}
					else
						++start;
				}
			}
			if (!breakFlag)
			{
				for (auto start = odds[i + 1].second.begin(); start != odds[i + 1].second.end(); )
				{
					if (start->second[1] == pairStr[i] && (odds[i + 1].first + start->first) > odds[0].first / 2.0 && start->second[0] == '+')
					{
						breakFlag = 1;
						odds[i + 1].first = odds[i + 1].first + start->first;
						start = odds[i + 1].second.erase(start);
						result.push_back(pairStr[i]);
					}
					else
						++start;
				}
			}
		}
		else
		{
			result.push_back(pairStr[i]);
		}
		odds[i + 1].second.reserve(2 * odds[i + 1].second.size());
		for (auto start = odds[i + 1].second.begin(); start != odds[i + 1].second.end(); ++start)
		{
			if (start->second[0] == '+' && start->first == odds[0].first / 2)
			{
				vector<int> erasePositionLast;
				vector<int> erasePositionNow;
				vector<int> erasePositionNext;
				int tempVoteNum = start->first;
				for (int j = 0; j < odds[i].second.size(); j++)
				{
					if (odds[i].second[j].second[1] == start->second[1])
					{
						erasePositionLast.push_back(j);
						tempVoteNum += odds[i].second[j].first;
					}
				}
				for (int k = 0; k < odds[i + 1].second.size(); k++)
				{
					if (odds[i + 1].second[k].second[1] == start->second[1] && odds[i + 1].second[k].second[0] == '*')
					{
						erasePositionNow.push_back(k);
						tempVoteNum += odds[i + 1].second[k].first;
					}
				}
				if (i + 2 < odds.size())
				{
					for (int l = 0; l < odds[i + 2].second.size(); l++)
					{
						if (odds[i + 2].second[l].second[1] == start->second[1])
						{
							erasePositionNext.push_back(l);
							tempVoteNum += odds[i + 2].second[l].first;
						}
					}
				}
				if (tempVoteNum > odds[0].first / 2)
				{
					pairStr.insert(pairStr.begin() + i + 1, start->second[1]);
					erasePositionNow.push_back(start - odds[i + 1].second.begin());
					for (int e1 = 0; e1 < erasePositionLast.size(); e1++)
					{
						odds[i].second.erase(odds[i].second.begin() + erasePositionLast[erasePositionLast.size() - e1 - 1]);
					}
					for (int e2 = 0; e2 < erasePositionNow.size(); e2++)
					{
						odds[i + 1].second.erase(odds[i + 1].second.begin() + erasePositionNow[erasePositionNow.size() - e2 - 1]);
					}
					if (i + 2 < odds.size())
					{
						for (int e3 = 0; e3 < erasePositionNext.size(); e3++)
						{
							odds[i + 2].second.erase(odds[i + 2].second.begin() + erasePositionNext[erasePositionNext.size() - e3 - 1]);
						}
					}
					vector<pair<int, string> > dummyOdds;
					odds.insert(odds.begin() + i + 2, make_pair(tempVoteNum, dummyOdds));
					break;
				}
			}
			else if (start->second[0] == '+' && start->first > odds[0].first / 2)
			{
				vector<int> erasePositionLast;
				vector<int> erasePositionNow;
				vector<int> erasePositionNext;

				string firstStr = to_string(start->first);
				int position = -1;
				for (int p = 0; p < firstStr.size(); p++)
				{
					if (firstStr[p] - '0' == odds[0].first / 2)
					{
						position = p;
						break;
					}
				}
				if (position == -1)
					break;

				int tempVoteNum = firstStr[position] - '0';
				for (int j = 0; j < odds[i].second.size(); j++)
				{
					if (odds[i].second[j].second[1] == start->second[position + 1])
					{
						erasePositionLast.push_back(j);
						tempVoteNum += odds[i].second[j].first;
					}
				}
				for (int k = 0; k < odds[i + 1].second.size(); k++)
				{
					if (odds[i + 1].second[k].second[1] == start->second[position + 1] && odds[i + 1].second[k].second[0] == '*')
					{
						erasePositionNow.push_back(k);
						tempVoteNum += odds[i + 1].second[k].first;
					}
				}
				if (i + 2 < odds.size())
				{
					for (int l = 0; l < odds[i + 2].second.size(); l++)
					{
						if (odds[i + 2].second[l].second[1] == start->second[position + 1])
						{
							erasePositionNext.push_back(l);
							tempVoteNum += odds[i + 2].second[l].first;
						}
					}
				}
				if (tempVoteNum > odds[0].first / 2)
				{
					pairStr.insert(pairStr.begin() + i + 1, start->second[position + 1]);
					string countLast;
					string countNow;
					pair<int, string> dummyPair;
					for (int p = 0; p < firstStr.size(); p++)
					{
						if (p < position)
						{
							if (p == 0)
							{
								odds[i + 1].second.push_back(dummyPair);
								odds[i + 1].second.back().second.push_back('+');
							}
							countLast.push_back(firstStr[p]);
							odds[i + 1].second.back().second.push_back(start->second[p + 1]);
						}
						else if (p == position)
						{
							odds[i + 1].second.back().first = atoi(countLast.c_str());
						}
						else if (p > position)
						{
							if (p == position + 1)
							{
								dummyPair.second.push_back('+');
							}
							countNow.push_back(firstStr[p]);
							dummyPair.second.push_back(start->second[p + 1]);
							if (p == firstStr.size() - 1)
							{
								dummyPair.first = atoi(countNow.c_str());
							}
						}
					}

					erasePositionNow.push_back(start - odds[i + 1].second.begin());
					for (int e1 = 0; e1 < erasePositionLast.size(); e1++)
					{
						odds[i].second.erase(odds[i].second.begin() + erasePositionLast[erasePositionLast.size() - e1 - 1]);
					}
					for (int e2 = 0; e2 < erasePositionNow.size(); e2++)
					{
						odds[i + 1].second.erase(odds[i + 1].second.begin() + erasePositionNow[erasePositionNow.size() - e2 - 1]);
					}
					if (i + 2 < odds.size())
					{
						for (int e3 = 0; e3 < erasePositionNext.size(); e3++)
						{
							odds[i + 2].second.erase(odds[i + 2].second.begin() + erasePositionNext[erasePositionNext.size() - e3 - 1]);
						}
					}
					vector<pair<int, string> > dummyOdds;
					if (dummyPair.first != 0)
						dummyOdds.push_back(dummyPair);
					odds.insert(odds.begin() + i + 2, make_pair(tempVoteNum, dummyOdds));

					break;
				}
			}
		}
	}
	return result;
}

string CombineStringResult(string inputStr)
{
	static vector<string> words;
	words.reserve(SIZE);

	return {};
}

class CombineTextResult
{
public:
	void SetQueueSize(int size);
	string CombineString(string input);
	void FreeQueue();
private:
	int m_queueSize;
	string* m_pResultQueue = NULL;
	int m_QueueFront = 0;
	int m_QueueRear = 0;
};

void CombineTextResult::SetQueueSize(int size)
{
	m_queueSize = size;
	if (m_pResultQueue == NULL)
	{
		m_pResultQueue = new string[size];
	}
}

void CombineTextResult::FreeQueue()
{

}

string CombineTextResult::CombineString(string input)
{

}

int main()
{
	fstream  f("C:\\Users\\Link\\Desktop\\sample.txt");
	vector<string> words;
	string answer;
	string line;
	vector<pair<int, string> > dummyOdds;
	MergeFrameResult tempResult;
	string result;
	int successCount = 0;
	int failCount = 0;
	int averageCountSum = 0;
	int earlyStop = 0;
	clock_t start, end;
	double timeConsume = 0;
	start = clock();
	while (getline(f, line))
	{
		if (words.empty() && answer.empty())
			answer = line;
		else if (line.empty() )
		{
			if (answer == result )
			{
				start = clock();
				earlyStop = 0;
				tempResult.odds.clear();
				tempResult.pairStr.clear();
				//printf("Success\n");
				successCount++;
				words.clear();
				answer.clear();
			}
			else
			{
				start = clock();
				earlyStop = 0;
				tempResult.odds.clear();
				tempResult.pairStr.clear();
				//printf("fail\n");
				failCount++;
				words.clear();
				answer.clear();
			}
		}
		else
		{
			words.push_back(line);
			MergeFrameResult inputFrame;
			if (words.size() > 1)
			{
				if (words[words.size() - 1].size() > tempResult.pairStr.size())
				{
					tempResult.odds.clear();
					tempResult.pairStr.clear();
					tempResult.pairStr = words[words.size() - 1];
					tempResult.odds.insert(tempResult.odds.end(), tempResult.pairStr.size() + 1, make_pair(1, dummyOdds));
					vector<int> usedSet;
					usedSet.push_back(words.size() - 1);
					for (int i = words.size() - 1; i >= 0; i--)
					{
						auto hasfound = find(usedSet.begin(), usedSet.end(), i);
						if (hasfound != usedSet.end())
						{
							continue;
						}
						else
						{
							inputFrame.odds.clear();
							inputFrame.pairStr = words[i];
							inputFrame.odds.insert(inputFrame.odds.end(), inputFrame.pairStr.size() + 1, make_pair(1, dummyOdds));
							tempResult = GetUnionOfStrings(tempResult, inputFrame);
						}
					}
				}
				else
				{
					inputFrame.pairStr = words[words.size() - 1];
					inputFrame.odds.insert(inputFrame.odds.end(), inputFrame.pairStr.size() + 1, make_pair(1, dummyOdds));
					tempResult = GetUnionOfStrings(tempResult, inputFrame);
				}

				result = GetResult(tempResult);
				//for (int i = 0; i < tempResult.odds.size(); i++)
				//{
				//	for (int j = 0; j < tempResult.odds[i].second.size(); j++)
				//	{
				//		if (tempResult.odds[i].second[j].first)
				//			break;
				//	}
				//}
				//cout << (result == answer) << endl;
				if (result == answer && earlyStop == 0 && tempResult.odds[0].first>2)
				{
					end = clock();
					timeConsume += end - start;
					earlyStop = 1;
					/*cout << words.size() << endl;*/
					averageCountSum += words.size();
				}
				//cout << "\n" << "StringMix: ";
				//for (int j = 0; j < result.size(); j++)
				//{
				//	cout << setw(3) << setiosflags(ios::left) << result[j];
				//}
				//cout << "\n" << "AnswerStr: ";
				//for (int j = 0; j < answer.size(); j++)
				//{
				//	cout << setw(3) << setiosflags(ios::left) << answer[j];
				//}
				//cout << "\n";
			}
			else
				continue;
		}
	}
	
	cout << timeConsume << endl;
	cout << successCount << " " << failCount << endl;
	cout << averageCountSum << endl;
	return 0;
}