#pragma once
class DossierProfesseur
{
	struct Cours {
		char* sigle;
		int NbreEtud;
		Cours* suivant;
	};

	struct Professeur {
		char* nom;
		int anciennete;
		Cours* listeCours;
		Professeur* suivant;
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

