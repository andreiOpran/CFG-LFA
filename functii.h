#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;



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
		if (fisier[i][fisier[i].size() - 1] == ':')
		{
			gasitRegula = false;
			gasitVars = false;
			iHeader = i;
			reluareI = i;
			while (fisier[i] != "End")
			{
				i++;
				if (fisier[i].find("*") != string::npos)
					gasitVars = true;
			}
			if (gasitVars)
			{
				fisier[iHeader] += "V";
			}
			else
			{
				while (fisier[reluareI] != "End")
				{
					reluareI++;
					if (fisier[reluareI].find(",") != string::npos)
					{
						gasitRegula = true;
						fisier[iHeader] += "R";
						break;
					}
				}
			}
			if (gasitVars == false && gasitRegula == false)
				fisier[iHeader] += "A";
		}
	}
	return fisier;
}



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



vector<string> getSectionContent(vector<string> content, string sectionName)
{
	int nrReguli = 0;
	bool inserareNrReguli = false;

	vector<string> sectionContent;
	bool variabile = false, regula = false, alfabet = false;
	
	sectionName = sectionName.substr(0, sectionName.size() - 1);
	
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i] == sectionName + "V")
			variabile = true;
		if (content[i] == sectionName + "R")
			regula = true;
		if (content[i] == sectionName + "A")
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
						if (content[i].find("*") != string::npos)
						{
							content[i].resize(content[i].length() - 2);
							gasitSteluta = true;
						}
						sectionContent.push_back(content[i]);
						if(gasitSteluta)
							sectionContent.push_back("*");
						else
							sectionContent.push_back("0");
					}
				}
				if (regula)
				{
					istringstream ss(content[i]);
					string aux;
					
					if (content[i] != "End")
					{
						bool primulAux = false;
						while (getline(ss, aux, ','))
						{
							if (primulAux == false)
							{
								sectionContent.push_back(aux);
								sectionContent.push_back("-");
								
								nrReguli++;
								inserareNrReguli = true;
								
								primulAux = true;
							}
							else
							{
								sectionContent.push_back(aux);
							}
						}
					}
				}
				if (alfabet)
				{
					if (content[i] != "End")
						sectionContent.push_back(content[i]);
				}
			}
		}
	}
	if (inserareNrReguli)
	{
		sectionContent.push_back("-");
		sectionContent.push_back(to_string(nrReguli));
	}

	return sectionContent;
}
