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
	// d�but de la liste cha�n�e.
	Professeur* tete; 
public:
	// construit la liste cha�n�e en m�moire � partir du fichier FP.
	DossierProfesseur(char* FP); 
	
	// d�truit la liste cha�n�e existant en m�moire.
	~DossierProfesseur(); 

	// supprime de la liste cha�n�e le professeur NOM.
	void Supprimer(char* NOM); 
	
	// affiche le nombre de cours en commun entre les profs X et Y.
	int Commun(char* X, char* Y); 
	
	// affiche le cours le plus demand� de la liste cha�n�e. En
	//cas de solutions multiples, prendre celui ayant le plus d��tudiants.
	char* LecoursLeplusDemande() const; 

	// affiche le nom du professeur le plus ancien.
	char* ProfeseurLeplusAncien() const; 
	
	// recopie � partir de la liste cha�n�e le nom, anciennet� et le nombre
	//de cours demand�s pour chaque professeur dans le fichier texte Nouveau.
	void Recopier(char *Nouveau); 
};

