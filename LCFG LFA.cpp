#include "functii.h";
#include <iostream>
#include <random>
#include <string>
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
		if (variabile[i] == "*")
			start = variabile[i - 1];
	}

	random_device rd;
	mt19937 gen(rd());
	int nrReguli = stoi(reguli[reguli.size() - 1]);
	uniform_int_distribution<> dis(1, nrReguli);
	reguli.pop_back();

	int random1, random2, contorReguli1, contorReguli2, nrVariante;

	vector <string> rez;
	rez.push_back(start);

	bool aplicatRegula;
	
	bool ok = false;
	while (ok == false)
	{
		bool gasitVariabila = false;
		for (int i = 0; i < rez.size(); i++)
		{
			for (int j = 0; j < variabile.size(); j++)
			{
				if (rez[i] == variabile[j])
				{
					gasitVariabila = true;
					break;
				}
			}
		}
		if (gasitVariabila == false)
			ok = true;

		if (ok == false)
		{
			

			for (int i = 0; i < rez.size(); i++)
			{
				for (int j = 0; j < variabile.size(); j++)
				{
				
					cout << endl << endl;
					for (int x = 0; x < rez.size(); x++)
						cout << rez[x];
					cout << endl << endl;

					aplicatRegula = false;
					contorReguli1 = 0;
					if (rez[i] == variabile[j])
					{
						while (aplicatRegula == false)
						{
							random1 = dis(gen);
							for (int k = 1; k < reguli.size(); k++)
							{
								if (reguli[k] == "-")
									contorReguli1++;
								if (contorReguli1 == random1 && reguli[k - 1] == rez[i])
								{
									int l = k + 1;
									while (reguli[l] != "-" && l < reguli.size())
									{
										rez.insert(rez.begin() + i + 1, reguli[l]);
										l++;
										aplicatRegula = true;
										if (l == reguli.size() || reguli[l] == "-")
										{
											aplicatRegula = true;
											ok = true;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
	}
	
	for (int i = 0; i < rez.size(); i++)
		cout << rez[i];

	return 0;
}

