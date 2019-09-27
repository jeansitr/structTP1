#pragma once
#include <string>

class DossierProfesseur
{
	struct Cours {
		char* sigle;
		int NbreEtud;
		Cours* suivant;

		Cours(char* _sigle, int _nbreEtud) {
			sigle = _sigle;
			NbreEtud = _nbreEtud;
			suivant = nullptr;
		};

		Cours() {
			sigle = nullptr;
			NbreEtud = NULL;
			suivant = nullptr;
		};

		//Ajout un cour existant dans la iste
		void AjoutCours(Cours* cour) {
			Cours* current = this;
			while (current) {
				if (!current->suivant)
					current = current->suivant = cour;
				
				current = current->suivant;
			}
		};

		//Ajout un nouveau cour dans la liste
		void AjoutCoursNewCours(char* _sigle, int _nbreEtu) {
			Cours* current = this;
			while (current) {
				if (!current->suivant)
					current = current->suivant = new Cours(_sigle, _nbreEtu);

				current = current->suivant;
			}
		};

		//Vérifie si le sigle existe dans la lise
		bool IncludesSigle(char* sigle) {
			Cours* current = this;
			while (current) 
			{
				char* currentSigle = current->sigle;
				if (currentSigle) {
					if (strcmp(current->sigle, sigle) == 0) {
						return true;
					}	
				}

				current = current->suivant;
			} 

			return false;
		};
	};

	struct Professeur {
		char* nom;
		int anciennete;
		Cours* listeCours;
		Professeur* suivant;

		//Ajout un professeur dans la liste
		void AjoutProfesseur(Professeur* prof) {
			Professeur* current = this;
			while (current) {
				if (!current->suivant)
					current = current->suivant = prof;
				
				current = current->suivant;
			}
		}
	};
	
private:
	// début de la liste chaînée.
	Professeur* tete; 
public:
	// construit la liste chaînée en mémoire à partir du fichier FP.
	DossierProfesseur(char* FP); 
	
	// détruit la liste chaînée existant en mémoire.
	~DossierProfesseur(); 

	// supprime de la liste chaînée le professeur NOM.
	void Supprimer(char* NOM); 
	
	// affiche le nombre de cours en commun entre les profs X et Y.
	int Commun(char* X, char* Y); 
	
	// affiche le cours le plus demandé de la liste chaînée. En
	//cas de solutions multiples, prendre celui ayant le plus d’étudiants.
	char* LecoursLeplusDemande() const; 

	// affiche le nom du professeur le plus ancien.
	char* ProfeseurLeplusAncien() const; 
	
	// recopie à partir de la liste chaînée le nom, ancienneté et le nombre
	//de cours demandés pour chaque professeur dans le fichier texte Nouveau.
	void Recopier(char *Nouveau); 
};

