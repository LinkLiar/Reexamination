#include "CombineResults.h"
#include <fstream>
#include <time.h>

int main()
{
	fstream  f("C:\\Users\\Link\\Desktop\\SampleTEST.txt");

	string answer;
	string line;
	int successCount = 0;
	int failCount = 0;
	clock_t start, end;

	SetQueueSize(5);
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

		const char* result = CombineString(line.c_str());
		// cout << result << endl;

		if (c == 5)
		{
			if (strcmp(result, answer.c_str())!=0)
			{
				failCount++;
				//cout <<":" << result << endl;
				//cout << answer << endl;
			}
			else
				successCount++;
			c = 0;
		}
	}
	FreeQueue();
	end = clock();
	cout << end - start << endl;
	cout << successCount << " : " << failCount << endl;

	return 0;
}