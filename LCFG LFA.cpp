#include <iostream>
#include <string>
#include <random>
#include "functii.h";
using namespace std;
int main()
{
	string numeFisier = "cfgInput.txt";
	vector <string> content = loadFile(numeFisier);
	vector <string> sectionList = getSectionList(content);

	string headerVariabile, headerReguli, headerAlfabet;
	for (int i = 0; i < sectionList.size(); i++)
	{
		if (sectionList[i][sectionList[i].size() - 1] == 'V')
		{
			headerVariabile = sectionList[i];
			break;
		}
	}
	for (int i = 0; i < sectionList.size(); i++)
	{
		if (sectionList[i][sectionList[i].size() - 1] == 'R')
		{
			headerReguli = sectionList[i];
			break;
		}
	}
	for (int i = 0; i < sectionList.size(); i++)
	{
		if (sectionList[i][sectionList[i].size() - 1] == 'A')
		{
			headerAlfabet = sectionList[i];
			break;
		}
	}
	vector <string> variabile = getSectionContent(content, headerVariabile);
	vector <string> reguli = getSectionContent(content, headerReguli);
	vector <string> alfabet = getSectionContent(content, headerAlfabet);
	
	string start;
	for (int i = 1; i < variabile.size(); i++)
	{
		if(variabile[i] == "*")
			start = variabile[i - 1];
	}

	random_device rd;
	mt19937 gen(rd());
	int nrReguli = stoi(reguli[reguli.size() - 1]);
	uniform_int_distribution<> dis(1, nrReguli);

	int random = dis(gen);
	cout << random;

	vector <string> rez;
	rez.push_back(start);

	for (int i = 0; i < rez.size(); i++)
	{
		for (int j = 0; j < variabile.size(); j++)
		{
			if (rez[i] == variabile[j])
			{
				for (int k = 0; k < reguli.size(); k++)
				{
					if (reguli[k][0] == variabile[j][0])
					{
						//rez.push_back(reguli[k].substr(3, reguli[k].size() - 3));
					}
				}
			}
		}
	}
	// de continuat randoim ul

	return 0;
}
