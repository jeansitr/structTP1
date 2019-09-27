#include "pch.h"
#include "DossierProfesseur.h"
#include <iostream>
#include <fstream>

DossierProfesseur::DossierProfesseur(char* FP)
{
	char* profSuivant;
	char* chaineProfesseur = strtok_s(FP, "&", &profSuivant);

	//Ajoute les professeur et les cours dans des liste selon la structure demmander.
	while (chaineProfesseur) {
		char* tokenSuivant;
		Professeur* newProf = new Professeur();

		newProf->nom = strtok_s(chaineProfesseur, "\n", &tokenSuivant);
		newProf->anciennete = std::stoi(strtok_s(tokenSuivant, "\n", &tokenSuivant));

		while (tokenSuivant && tokenSuivant[0]) {
			Cours* newCour = new Cours();

			newCour->sigle = strtok_s(tokenSuivant, "\n", &tokenSuivant);
			newCour->NbreEtud = std::stoi(strtok_s(tokenSuivant, "\n", &tokenSuivant));

			if (newProf->listeCours) 
				newProf->listeCours->AjoutCours(newCour);
			else 
				newProf->listeCours = newCour;
		}
		
		if (tete) {
			tete->AjoutProfesseur(newProf);
		}
		else {
			tete = newProf;
		}

		chaineProfesseur = strtok_s(profSuivant, "&", &profSuivant);
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
	Professeur* prof1 = nullptr;
	Professeur* prof2 = nullptr;

	Professeur* current = tete;
	bool foundProf = false;
	int coursCommun = 0;

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

	if (foundProf) {
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
	}
	return coursCommun;
}

char* DossierProfesseur::LecoursLeplusDemande() const {
	char* mostWantedSigle = (char*)"";
	int mostWantedNbr = -1;
	int mostWantedNbrEtu = -1;
	Cours* coursVérifier = new Cours();
	Professeur* iProf = tete;
	//Vérifie pour chaque cours de chaque professeur si le cour existe dans la liste de cours des autres professeur
	while (iProf) {
		Cours* iCour = iProf->listeCours;
		while (iCour) {
			char* currentWantedSigle = iCour->sigle;
			int currentWantedNbrEtu = iCour->NbreEtud;
					
			//vérifie si le cour à déja été vérifier.
			if (!coursVérifier->IncludesSigle(currentWantedSigle)) {
				if (!coursVérifier->sigle) {
					coursVérifier = new Cours(currentWantedSigle, currentWantedNbrEtu);
				}
				else {
					coursVérifier->AjoutCoursNewCours(currentWantedSigle, currentWantedNbrEtu);
				}

				int currentWantedNbr = 1;

				Professeur* eProf = tete;
				while (eProf) {
					if (iProf != eProf) {
						Cours* eCour = eProf->listeCours;
						while (eCour)
						{
							if (strcmp(currentWantedSigle, eCour->sigle) == 0) {
								currentWantedNbr++;
								currentWantedNbrEtu += eCour->NbreEtud;
							}

							eCour = eCour->suivant;
						}
					}

					eProf = eProf->suivant;
				}

				if (currentWantedNbr >= mostWantedNbr) {
					if ((currentWantedNbr == mostWantedNbr && currentWantedNbrEtu > mostWantedNbrEtu) || currentWantedNbr != mostWantedNbr) {
						mostWantedSigle = currentWantedSigle;
						mostWantedNbr = currentWantedNbr;
						mostWantedNbrEtu = currentWantedNbrEtu;
					}
				}
			}

			iCour = iCour->suivant;
		}

		iProf = iProf->suivant;
	}

	return mostWantedSigle;
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
	std::ofstream ofs (Nouveau, std::ofstream::out);

	Professeur* current = tete;

	while (current) {
		if (current != tete) {
			ofs << "&\n";
		}

		ofs << current->nom << "\n";
		ofs << current->anciennete << "\n";
		
		Cours* coursCurrent = current->listeCours;
		int cpt = 0;

		while (coursCurrent) {
			//ofs << coursCurrent->sigle << "\n";
			//ofs << coursCurrent->NbreEtud << "\n";
			cpt++;
			coursCurrent = coursCurrent->suivant;
		}

		ofs << "Nombre de cours demander: " << cpt << "\n";
		current = current->suivant;
	}

	ofs.close();
}