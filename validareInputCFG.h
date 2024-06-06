#pragma once

bool stringInVector(string x, vector <string> vector) // o functie care verifica daca un string se afla intr-un vector de stringuri
{
	bool rez = false;
	for (string s : vector)
	{
		if (x == s)
			rez = true;
	}
	return rez;
}

bool validareFisier(string numeFisier)
{

	cout << "\nValidare fisier " << numeFisier << "\n";
	cout << "Doriti afisarea erorilor si oprirea programului in caz de gasire a unei erori ? \n1.Da\n2.Nu\n";
	cout << "\n> ";
	string raspuns;
	cin >> raspuns;
	if (raspuns == "2")
	{
		return true;
	}

	bool ok;
	int cont;

	vector<string> content, sectionList, variabile, sigma, reguli;
	content = loadFile(numeFisier); // incarcam continutul fisierului in vectorul content
	sectionList = getSectionList(content); // obtinem lista cu sectiunile din fisier

	if (sectionList.size() != 3) // verificam daca fisierul are 3 sectiuni
	{
		cout << "\nFisierul " << numeFisier << " nu are 3 sectiuni.\n";
		return false;
	}

	variabile = getSectionContent(content, sectionList[0]); // obtinem continutul sectiunii cu variabile
	sigma = getSectionContent(content, sectionList[1]); // obtinem continutul sectiunii cu alfabet
	reguli = getSectionContent(content, sectionList[2]); // obtinem continutul sectiunii cu reguli

	for (string s : variabile
		)
		cout << s << ' ';

	// verificare existenta variabila start sau daca exista mai multe variabile de start
	ok = false;
	cont = 0;
	for (string variabila : variabile)
	{
		if (variabila == "*") // contorizam cate variabile de start avem
			++cont;
	}
	if (cont == 0)
	{
		cout << "\nNu ati introdus variabila de start in fisierul " << numeFisier << ".\n";
		return false;
	}
	else
		if (cont != 1)
		{
			cout << "\nAti introdus " << cont << " variabile de start in fisierul " << numeFisier << ".\n";
			return false;
		}

	// verificare daca exista o variabila care este egala cu o litera din alfabet
	for (int i = 0; i < variabile.size(); i++)
	{
		if (variabile[i] != "*" && variabile[i] != "0") // nu verificam simbolul *, sau 0 care apare in dreptul fiecarei variabile care nu este de start
		{
			for (int j = 0; j < sigma.size(); j++)
			{
				if (variabile[i] == sigma[j])
				{
					cout << "\nVariabila " << variabile[i] << " este egala cu simbolul " << sigma[j] << " din alfabet.\n"; 
					return false;
				}
			}
		}
	}

	// verificare dubluri in variabile
	for (int i = 0; i < variabile.size() - 1; i++)
	{
		for (int j = i + 1; j < variabile.size(); j++)
		{
			if (variabile[i] == variabile[j])
			{
				cout << "\nVariabila " << variabile[i] << " apare de doua ori.\n";
				return false;
			}
		}
	}

	// verificare dubluri in sigma
	for (int i = 0; i < sigma.size() - 1; i++)
	{
		for (int j = i + 1; j < sigma.size(); j++)
		{
			if (sigma[i] == sigma[j])
			{
				cout << "\nSimbolul " << sigma[i] << " apare de doua ori.\n";
				return false;
			}
		}
	}

	// verificare daca fiecare element din reguli exista in variabile sau in sigma, ultimul element nu il verificam deoarece este ocupat de contorul de reguli	
	for (int i = 0; i < reguli.size() - 1; i++)
	{
		if (reguli[i] != "-")
		{
			if (!stringInVector(reguli[i], variabile) && !(stringInVector(reguli[i], sigma))) // verificam daca elementul din reguli exista in variabile sau in sigma
			{
				cout << "\nElementul " << reguli[i] << " din reguli nu exista in variabile sau in alfabet.\n";
				return false;
			}
		}
	}

	// verificare daca pentru fiecare variabila exista o regula aplicata acesteia care contine doar elemente din sigma 
	// ca sa nu avem loop infinit
	// aceasta verificare o vom face in emularea propriu zisa a CFG ului in cpp-ul principal
	// prin a contoriza numarul de reguli aplicate, iar daca aplicam reguli
	// de mai mult de 10.000 de ori se va termina programul si se va afisa un mesaj corespunzator
	// iar daca se aplica 3000 de reguli se afiseaza un measaj de procesare
	// astfel avem o limita de 10.000 de reguli care se pot aplica.
	// pe calculatorul meu dureaza in jur de 15 secunde sa aplice 10.000 de reguli
	
	// verificare daca exista reguli care nu incep cu o variabila
	
	// tratam cazul primei reguli separat deoarece prima regula nu are "-" in fata, la fel ca celelalte reguli
	// elementele "-" din fata regulilor sunt folosite pentru a separa regulile si sunt introduse automat in prelucrarea fisierului
	if (!stringInVector(reguli[0], variabile)) 
	{
		cout << "\nPrima regula nu incepe cu o variabila.\n";
		return false;
	}
	for (int i = 2; i < reguli.size() - 1; i++)
	{
		if (reguli[i] == "-" && reguli[i-2] == "-")
		{
			if (!stringInVector(reguli[i - 1], variabile))
			{
				cout << endl << reguli[i - 1] << endl;
				cout << "\nO regula nu incepe cu o variabila.\n";
				return false;
			}
		}
	}

	cout << "\nFisierul " << numeFisier << " este valid.\n\n";
	return true;
}