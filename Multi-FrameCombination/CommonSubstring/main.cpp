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

	void* pCombineTextResultsInstance = NULL;
	CreateCombineResultsInstance(&pCombineTextResultsInstance, 5);

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

		int score;
		char* re = NULL;
		CombineResults(pCombineTextResultsInstance, line.c_str(), &re, score);

		if (c == 5)
		{
			if (strcmp(re, answer.c_str()))
			{
				failCount++;
				//cout <<":" << result << endl;
				//cout << answer << endl;
			}
			else
				successCount++;
			c = 0;
		}
		FreeCombinedResults(&re);
	}
	end = clock();
	cout << end - start << endl;
	cout << successCount << " : " << failCount << endl;
	DestroyCombineResultsInstance(&pCombineTextResultsInstance);
	return 0;
}