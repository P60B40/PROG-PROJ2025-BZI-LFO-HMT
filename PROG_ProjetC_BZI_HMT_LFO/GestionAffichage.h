#ifndef GESTIONAFFICHAGE_H
#define GESTIONAFFICHAGE_H

#include "main.h"

//define 
#define FILE_NAME "logModulesNotes.txt"
#define MAX_BRANCHES 10
#define MAX_NOTES 10
#define MAX_MODULES 3


//prototype de fonction 
void ajouterNoteDeFichier();
void afficherTableau(Systeme* s);	//afficher dans la console
void afficherTableauFichier(Systeme* s, FILE* f);	//afficher dans le fichier	
void chargerDonnees(Systeme* s);	//lecture du fichier
void supprimerNotes();


#endif
