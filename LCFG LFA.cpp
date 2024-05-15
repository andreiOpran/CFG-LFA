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
	for (int i = 0; i < sectionList.size(); i++) // extragere header variabile, reguli si alfabet prin intermediul ultimului caracter
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
	vector <string> variabile = getSectionContent(content, headerVariabile); // extragere continut variabile, reguli si alfabet
	vector <string> reguli = getSectionContent(content, headerReguli);
	vector <string> alfabet = getSectionContent(content, headerAlfabet);

	string start;
	for (int i = 1; i < variabile.size(); i++) // gasirea variabilei de start
	{
		if (variabile[i] == "*")
			start = variabile[i - 1];
	}

	random_device rd; // generare random a unui int care apartine [1, nrReguli], nrReguli este inserat in vectorul reguli pe ultima pozitie
	mt19937 gen(rd());
	int nrReguli = stoi(reguli[reguli.size() - 1]);
	uniform_int_distribution<> dis(1, nrReguli);
	reguli.pop_back(); // scoatem nrReguli din vectorul de reguli  eoarece nu mai avem nevoie de el

	vector <string> rez;
	rez.push_back(start); // adaugam variabila de start in vectorul rezultat

	bool rezEsteVar, gasitRegula;
	int random, index;

	for (int i = 0; i < rez.size(); i++)
	{
		rezEsteVar = false;
		for (int j = 0; j < variabile.size(); j++) // verficam daca rez[i] este variabila
		{
			if (rez[i] == variabile[j])
			{
				rezEsteVar = true;
				break;
			}
		}

		if (rezEsteVar) // daca rez[i] este variabila, cautam o regula random care sa aiba variabila respectiva pe partea stanga, daca regula selectata random nu are variabila pe partea stanga, cautam alta regula tot random 
		{
			gasitRegula = false;
			while (gasitRegula == false) // o regula are pe al doilea element cratima
			{
				random = dis(gen);
				index = gasireCratimaN(reguli, random); //functie care gaseste al n lea "-" dintr-un vector, unde n este repr de var random
				if (reguli[index - 1] == rez[i])
					gasitRegula = true;
			}
			index++; // indexul este mutat cu 1 pentru a nu lua in considerare cratima
			
			vector <string> aux; // vector auxiliar in care se stocheaza elementele regulei selectate random care vor inlocui variabila din vectorul rezultat

			while (reguli[index] != "-") // adaugam elementele regulei selectate random in vectorul auxiliar
			{	
				aux.push_back(reguli[index]);
				if(index == reguli.size() - 3)
					aux.push_back(reguli[index + 1]);
				index++;
				if(reguli[index + 1] == "-")
					break;
			}
			rez.erase(rez.begin() + i); // stergem variabila din vectorul rezultat
			for (int a = 0; a < aux.size(); a++) // adaugam elementele regulei selectate random in vectorul rezultat
				rez.insert(rez.begin() + i, aux[a]);

		}
		else
		{
			i = rez.size() + 2; // daca rez[i] nu este variabila, iesim din for
		}
		
		
	}

	for (int i = 0; i < rez.size(); i++) // afisare rezultat
		cout << rez[i];

	return 0;
}
