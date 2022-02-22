#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

typedef struct
{
	string pairStr;
	vector<pair<int, vector<pair<int, string> > > >odds;
}MergeFrameResult;

class CombineTextResults
{
public:
	CombineTextResults(int size);
	~CombineTextResults();
	void CombineString(const string inputStr, int* score);    // 多帧结果校验
	const string GetCombineResult() { return m_combineResult; }
	string m_combineResult;

private:
	int m_queueSize = 0;
	vector<string> m_resultQueue;
	int m_QueueFront = 0;
	int m_QueueRear = -1;
	int m_hadCheckFrame = 1;
	MergeFrameResult m_tempResult;

	string GetResult(MergeFrameResult& frame);
	MergeFrameResult GetUnionOfStrings(MergeFrameResult mergedResult1, MergeFrameResult mergedResult2);
	vector<pair<int, int> > GetIntersectionOfMatrix(const string str1, const string str2, pair<int, int> tlPoint, pair<int, int> brPoint, vector<pair<int, vector<pair<int, string> > > >mainOdds, vector<pair<int, vector<pair<int, string> > > >tempOdds);
};

const char* CombineResults(void* CombineTextResultsInstance, const char* input, int* score);