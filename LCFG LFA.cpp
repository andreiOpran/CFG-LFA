#include "functii.h";
#include <iostream>
#include <random>
#include <string>
using namespace std;

int gasireCratimaN(vector <string> vector, int n) // functie care gaseste al n lea "-" dintr-un vector
{
	
	int cont = 0;
	for(int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == "-")
			cont++;
		if(cont == n)
			return i;
	}
	return -1;
}


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

	vector <string> rez;
	rez.push_back(start);

	bool rezEsteVar, gasitRegula;
	int random, index;

	for (int i = 0; i < rez.size(); i++)
	{

		rezEsteVar = false;
		for (int j = 0; j < variabile.size(); j++)
		{
			if (rez[i] == variabile[j])
			{
				rezEsteVar = true;
				break;
			}
		}

		if (rezEsteVar)
		{
			gasitRegula = false;
			while (gasitRegula == false)
			{
				random = dis(gen);
				index = gasireCratimaN(reguli, random);
				if (reguli[index - 1] == rez[i])
					gasitRegula = true;
			}
			//cout << index;
			index++;
			//cout << "\n reguli[index] " << reguli[index] << endl;
			//cout << "\n reguli[index + 1] " << reguli[index + 1] << endl;

			while (reguli[index] != "-")
			{				
				cout << "\n" << reguli[index] << endl;
				rez.insert(rez.begin() + i, reguli[index]);
				index++;	
				if (reguli[index + 1] == "-")
					break;
			}
			
			
		}
		else
		{
			i = rez.size() + 2;
		}
		
		
	}

	

	for (int i = 0; i < rez.size(); i++)
		cout << rez[i];
;

	return 0;
}

// REGULI 
// A - 0 A 1 A - 0 1 - 