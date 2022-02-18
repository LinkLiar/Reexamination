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

class CombineTextResult
{
public:
	int SetQueueSize(int size);    // 设置缓存队列大小
	string CombineString(string input);    // 多帧结果校验
	int FreeQueue();    // 删除缓存队列

private:
	int m_queueSize = 0;
	string* m_pResultQueue = NULL;
	int m_QueueFront = 0;
	int m_QueueRear = -1;
	MergeFrameResult m_tempResult;

	string GetResult(MergeFrameResult& frame);
	MergeFrameResult GetUnionOfStrings(MergeFrameResult mergedResult1, MergeFrameResult mergedResult2);
	vector<pair<int, int> > GetIntersectionOfMatrix(const string str1, const string str2, pair<int, int> tlPoint, pair<int, int> brPoint, vector<pair<int, vector<pair<int, string> > > >mainOdds, vector<pair<int, vector<pair<int, string> > > >tempOdds);
};