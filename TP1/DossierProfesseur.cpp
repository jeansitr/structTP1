#include "pch.h"
#include "DossierProfesseur.h"
#include <string>
#include <iostream>

DossierProfesseur::DossierProfesseur(char* FP)
{
	char* profSuivant;
	char* teacher = strtok_s(FP, "&", &profSuivant);
	while (teacher) {
		char* tokenSuivant;
		Professeur* newProf = new Professeur();

		newProf->nom = strtok_s(teacher, "\n", &tokenSuivant);
		newProf->anciennete = std::stoi(strtok_s(tokenSuivant, "\n", &tokenSuivant));

		while (tokenSuivant && tokenSuivant[0]) {
			Cours* newCour = new Cours();

			newCour->sigle = strtok_s(tokenSuivant, "\n", &tokenSuivant);
			newCour->NbreEtud = std::stoi(strtok_s(tokenSuivant, "\n", &tokenSuivant));

			AjoutCours(newProf, newCour);
		}

		AjoutProfesseur(newProf);
		teacher = strtok_s(profSuivant, "&", &profSuivant);
	}
}

DossierProfesseur::~DossierProfesseur() {
	while (tete != NULL) {
		Professeur* profCourant = tete;

		while (profCourant->listeCours != NULL) {
			Cours* courCourant = profCourant->listeCours;
			profCourant->listeCours = profCourant->listeCours->suivant;
			delete courCourant;
		}
		tete = tete->suivant;
		delete profCourant;
	}
}

void DossierProfesseur::Supprimer(char* NOM) {
	if (tete->nom == NOM)
		tete = tete->suivant;
	else {
		Professeur* current = tete;
		bool deleted = false;
	
		while (!deleted && current->suivant) {
			if (strcmp(current->suivant->nom,NOM) == 0) {
				current->suivant = current->suivant->suivant;
				deleted = true;
			}
			else {
				current = current->suivant;
			}
		}
	}
}


int DossierProfesseur::Commun(char* X, char* Y) {
	Professeur* prof1 = tete;
	Professeur* prof2 = tete;

	Professeur* current = tete;
	bool foundProf = false;

	while (!foundProf && current->suivant) {
		if (strcmp(current->nom,X) == 0) {
			foundProf = true;
			prof1 = current;
		}

		current = current->suivant;
	}

	current = tete;
	foundProf = false;

	while (!foundProf && current->suivant) {
		if (strcmp(current->nom, Y) == 0) {
			foundProf = true;
			prof2 = current;
		}

		current = current->suivant;
	}

	int coursCommun = 0;
	Cours* currentCoursProf1 = prof1->listeCours;

	while (currentCoursProf1) {
		Cours* currentCoursProf2 = prof2->listeCours;
		while (currentCoursProf2) {
			if (strcmp(currentCoursProf1->sigle, currentCoursProf2->sigle) == 0) {
				coursCommun++;
			}
			currentCoursProf2 = currentCoursProf2->suivant;
		}
		delete currentCoursProf2;
		currentCoursProf1 = currentCoursProf1->suivant;
	}

	delete currentCoursProf1;
	delete prof1;
	delete prof2;
	return coursCommun;
}

/*
char* DossierProfesseur::LecoursLeplusDemande() const {	
}

*/

char* DossierProfesseur::ProfeseurLeplusAncien() const {
	Professeur* current = tete;
	Professeur* oldest = tete;

	while (current) {
		if (current->anciennete > oldest->anciennete) {
			oldest = current;
		}
		current = current->suivant;
	}

	delete current;
	return oldest->nom;
}
/*
void DossierProfesseur::Recopier(char* Nouveau) {

}
*/

void DossierProfesseur::AjoutProfesseur(DossierProfesseur::Professeur* prof) {
	bool dernierTrouver = false;
	if (tete){
		Professeur* profSuivant = tete;
		do {
			if (profSuivant->suivant)
				profSuivant = profSuivant->suivant;
			else {
				profSuivant->suivant = prof;
				dernierTrouver = true;
			}
		} while (!dernierTrouver);
	}
	else {
		tete = prof;
	}
}

void DossierProfesseur::AjoutCours(DossierProfesseur::Professeur* prof, DossierProfesseur::Cours* cour) { 
	bool dernierTrouver = false;
	Cours* courSuivant = prof->listeCours;
	if (courSuivant) {
		do {
			if (courSuivant->suivant)
				courSuivant = courSuivant->suivant;
			else {
				courSuivant->suivant = cour;
				dernierTrouver = true;
			}
		} while (!dernierTrouver);
	}
	else {
		prof->listeCours = cour;
	}
}