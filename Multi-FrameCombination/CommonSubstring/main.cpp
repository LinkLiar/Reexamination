#include "CombineResults.h"
#include <fstream>
#include <time.h>

int main()
{
	fstream  f("C:\\Users\\Link\\Desktop\\sample.txt");

	string answer;
	string line;
	int successCount = 0;
	int failCount = 0;
	clock_t start, end;

	CombineTextResults L(5);
	CombineTextResults* ptr = &L;

	bool recordAnswer = 0;
	int c = 0;
	getline(f, line);
	answer = line;
	start = clock();

	while (getline(f, line))
	{
		if (line.empty())
		{
			recordAnswer = 1;
			continue;
		}
		if (recordAnswer)
		{
			answer = line;
			recordAnswer = 0;
			continue;
		}

		c++;

		int* pScore = new int;
		const char* re = CombineResults(reinterpret_cast<void*>(ptr), line.c_str(), pScore);
		string result(re);

		if (c == 5)
		{
			if (result != answer)
			{
				failCount++;
				//cout <<":" << result << endl;
				//cout << answer << endl;
			}
			else
				successCount++;
			c = 0;
		}
		delete pScore;
	}

	end = clock();
	cout << end - start << endl;
	cout << successCount << " : " << failCount << endl;

	return 0;
}