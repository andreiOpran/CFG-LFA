#include <iostream>
#include "functii.h";
using namespace std;
int main()
{
	string numeFisier = "cfgInput.txt";
	vector <string> content = loadFile(numeFisier);
	vector <string> sectionList = getSectionList(content);

	string headerVariabile;

	for (int i = 0; i < sectionList.size(); i++)
	{
		if (sectionList[i][sectionList[i].size() - 1] == 'V')
		{
			headerVariabile = sectionList[i];
			break;
		}
	}

	vector <string> variabile = getSectionContent(content, headerVariabile);
	
	/*string start;
	for (int i = 1; i < variabile.size(); i++)
	{
		if(variabile[i] == "*")
			start = variabile[i - 1];
	}

	cout << start;*/

	return 0;
}
