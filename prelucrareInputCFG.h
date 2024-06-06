#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// functie care incarca continutul fisierului in vectorul content
// se elimina liniile care incep cu #
// se adauga la fiecare sectiune un caracter care indica tipul sectiunii
// A - alfabet daca nu exista nici o virgula si nicio steluta
// V - variabile daca exista steluta
// R - reguli daca exista virgula
vector<string> loadFile(string numeFisier)
{
	ifstream fin(numeFisier);
	vector<string> fisier;
	string linie;
	while (getline(fin, linie))
	{
		if (linie[0] != '#')
			fisier.push_back(linie);
	}

	int iHeader = 0, reluareI;
	bool gasitVars = false;
	bool gasitRegula = false;
	for (int i = 0; i < fisier.size(); i++)
	{
		if (!fisier[i].empty() && fisier[i][fisier[i].size() - 1] == ':') // daca linia contine un caracter ':' la sfarsit
		{
			gasitRegula = false;
			gasitVars = false;
			iHeader = i; // retinem pozitia liniei care contine numele sectiunii
			reluareI = i; // pentru a relua cautarea de reguli in cazul in care nu gasim variabile
			while (fisier[i] != "End")
			{
				i++;
				if (fisier[i].find("*") != string::npos)
					gasitVars = true; // daca gasim steluta in linie, inseamna ca avem variabile
			}
			if (gasitVars)
			{
				fisier[iHeader] += "V"; // adaugam la numele sectiunii caracterul V
			}
			else
			{
				while (fisier[reluareI] != "End")
				{
					reluareI++; // cautam reguli
					if (fisier[reluareI].find(",") != string::npos) // daca gasim virgula in linie, inseamna ca avem reguli (in acest caz nu gasisem nici *)
					{
						gasitRegula = true;
						fisier[iHeader] += "R";
						break;
					}
				}
			}
			if (gasitVars == false && gasitRegula == false) // daca nu am gasit nici variabile, nici reguli, inseamna ca avem alfabet
				fisier[iHeader] += "A";
		}
	}
	return fisier;
}


// functie care returneaza o lista cu sectiunile din fisier
// sectiunile sunt identificate dupa caracterul ':' de la sfarsitul numelui sectiunii
vector<string> getSectionList(vector<string> content)
{
	vector<string> sectionList;
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i].size() > 1)
		{
			if (content[i][content[i].size() - 2] == ':')
			{
				/*content[i].erase(content[i].size() - 2);*/
				sectionList.push_back(content[i]);
			}
		}
	}
	return sectionList;
}


// functie care returneaza continutul unei sectiuni
// sectiunea este identificata dupa numele sectiunii
// se returneaza un vector cu continutul sectiunii
// se adauga un caracter '-' in vector pentru a separa regulile
vector<string> getSectionContent(vector<string> content, string sectionName)
{
	int nrReguli = 0;
	bool inserareNrReguli = false;

	vector<string> sectionContent;
	bool variabile = false, regula = false, alfabet = false;
	
	sectionName = sectionName.substr(0, sectionName.size() - 1);
	
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i] == sectionName + "V") // daca gasim caracterul V la sfarsitul numelui sectiunii, inseamna ca avem variabile
			variabile = true;
		if (content[i] == sectionName + "R") // daca gasim caracterul R la sfarsitul numelui sectiunii, inseamna ca avem reguli
			regula = true;
		if (content[i] == sectionName + "A") // daca gasim caracterul A la sfarsitul numelui sectiunii, inseamna ca avem alfabet
			alfabet = true;

		bool gasitSteluta = false;
		if (content[i].substr(0, sectionName.size()) == sectionName)
		{
			while (content[i] != "End")
			{
				i++;
				if (variabile)
				{
					if (content[i] != "End")
					{
						gasitSteluta = false;
						if (content[i].find("*") != string::npos) // daca gasim steluta in linie, inseamna ca avem variabila de start
						{
							content[i].resize(content[i].length() - 2); // eliminam steluta din numele variabilei
							gasitSteluta = true;
						}
						sectionContent.push_back(content[i]);
						if (gasitSteluta) // daca am gasit steluta, adaugam in vector un caracter '*' pentru a putea verifica ulterior daca avem o singura variabila de start
							sectionContent.push_back("*");
						else
							sectionContent.push_back("0"); // altfel adaugam 0 ca un fel de default
					}
				}
				if (regula)
				{
					istringstream ss(content[i]);
					string aux;
					
					if (content[i] != "End")
					{
						bool primulAux = false;
						while (getline(ss, aux, ',')) // despartim regulile in functie de virgula
						{
							if (primulAux == false) // daca este primul element al regulii, adaugam in vector un caracter '-' pentru a putea separa regulile
							{
								sectionContent.push_back(aux);
								sectionContent.push_back("-");
								
								nrReguli++;
								inserareNrReguli = true;
								
								primulAux = true;
							}
							else // altfel adaugam regulile in vector
							{
								sectionContent.push_back(aux);
							}
						}
					}
				}
				if (alfabet) // daca avem alfabet, doar adaugam elementele in vector
				{
					if (content[i] != "End")
						sectionContent.push_back(content[i]);
				}
			}
		}
	}
	if (inserareNrReguli) // daca am gasit reguli, adaugam in vector numarul de reguli care ne va ajuta la emularea CFG ului in cpp-ul principal
	{
		sectionContent.push_back("-");
		sectionContent.push_back(to_string(nrReguli));
	}

	return sectionContent;
}
