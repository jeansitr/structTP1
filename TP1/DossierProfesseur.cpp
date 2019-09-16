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
			if (*current->suivant->nom == *NOM) {
				current->suivant = current->suivant->suivant;
				deleted = true;
			}
		}
	}
}

/*
int DossierProfesseur::Commun(char* X, char* Y) {
	
}
char* DossierProfesseur::LecoursLeplusDemande() const {

}

char* DossierProfesseur::ProfeseurLeplusAncien() const {

}
*/
void DossierProfesseur::Recopier(char *Nouveau) {

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