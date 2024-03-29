// TP1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "DossierProfesseur.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

string toAscii(char tab[]) {
	char buffer[256];
	CharToOemA(tab, buffer);
	string str(buffer);
	return str;
}

int main()
{
	int length;
	ifstream FP ("FP.txt");

	//va chercher la longeur du fichier FP.txt
	FP.seekg(0, ios::end);
	length = (int)FP.tellg();
	FP.seekg(0, ios::beg);

	//li le fichier jusqua la fin
	char* document = new char[length];
	FP.read(document, length);
	FP.close();

	DossierProfesseur* prof = new DossierProfesseur(document);

	//li le fichier Opération.txt ligne par ligne et fait les opération demmander selon l'entrée dans le fichier Opération.txt
	ifstream operations("Opération.txt");
	for (std::string line; getline(operations, line); )
	{ 
		char op = line[0];
		switch (op) {
			case '&':
			{
				//Chercher les espaces séparant les noms
				string tokens = line.substr(2, line.size());
				size_t firstSpace = tokens.find(" ");
				size_t secondSpace = tokens.find(" ", firstSpace + 1);

				//divise la ligne dépendament des espaces pour retrouver les noms
				string name1 = tokens.substr(0, secondSpace);
				string name2 = tokens.substr(secondSpace + 1, tokens.size());
				char* chName1 = new char[name1.length()];
				char* chName2 = new char[name2.length()];
				
				strcpy_s(chName1, name1.length() + 1, name1.c_str());
				strcpy_s(chName2, name2.length() + 1, name2.c_str());
				cout << "Les professeur " << chName1 << " et " << chName2 << " ont " << prof->Commun(chName1, chName2) << " en commun." << endl;
				break;
			}
			case '+':
			{
				cout << "Le cour le plus demmander est: " << prof->LecoursLeplusDemande() << endl;
				break;
			}

			case '*':
			{
				cout << "le professeur le plus ancien est: " << toAscii(prof->ProfeseurLeplusAncien()) << endl;
				break;
			}

			case '%':
			{
				string toDelete = line.substr(2, line.size());
				char* chToDelete = new char[toDelete.length()];
				strcpy_s(chToDelete, toDelete.length() + 1, toDelete.c_str());

				prof->Supprimer(chToDelete);
				cout << "Le professeur " << toAscii(chToDelete) << toAscii((char*)" à été supprimer") << endl;
				break;
			}

			case '$':
			{
				string outputFileName = line.substr(2, line.size());
				char* chOutputFileName = new char[outputFileName.length()];
				strcpy_s(chOutputFileName, outputFileName.length() + 1, outputFileName.c_str());

				prof->Recopier(chOutputFileName);
				cout << toAscii((char*)"la structure a été recopier dans le ficher: ") << toAscii(chOutputFileName) << endl;
				break;
			}
			default:
				cout << toAscii((char*)"Opération: ") << op << " n'existe pas." << endl;
				break;
		}
	}

	cin >> document;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
