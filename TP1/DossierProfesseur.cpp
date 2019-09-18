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
	Professeur* prof1;
	Professeur* prof2;

	Professeur* current = tete;
	bool foundProf = false;

	while (!foundProf && current->suivant) {
		if (strcmp(current->nom, X) == 0) {
			prof1 = current;
		}
		else if (strcmp(current->nom, Y) == 0){
			prof2 = current;
		}

		if(prof1 && prof2)
			foundProf = true;
		
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
		currentCoursProf1 = currentCoursProf1->suivant;
	}

	return coursCommun;
}

char* DossierProfesseur::LecoursLeplusDemande() const {	
	return (char *)"Not implemented";
}


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

void DossierProfesseur::Recopier(char* Nouveau) {

}

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