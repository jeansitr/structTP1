// TP1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "DossierProfesseur.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int length;
	ifstream FP ("FP.txt");

	FP.seekg(0, ios::end);
	length = FP.tellg();
	FP.seekg(0, ios::beg);

	char* document = new char[length];
	FP.read(document, length);
	FP.close();

	DossierProfesseur* prof = new DossierProfesseur(document);

	ifstream operations("Opération.txt");
	for (std::string line; getline(operations, line); )
	{
		char op = line[0];
		switch (op) {
			case '&':

				break;

			case '+':
				cout << "Le cour le plus demmander est: " << prof->LecoursLeplusDemande();
				break;

			case '*':
				cout << "le professeur le plus ancien est: " << prof->ProfeseurLeplusAncien();
				break;

			case '%':

				break;

			case '$':

				break;
			default:
				cout << "Opération: " << op << " n'existe pas.";
				break;
		}
	}
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
