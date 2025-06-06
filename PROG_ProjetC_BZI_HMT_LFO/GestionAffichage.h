#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>  // nécessaire pour FILE *
//define 
#define FILE_NAME "notes.txt"
#define MAX_BRANCHES 10
#define MAX_NOTES 10
#define MAX_MODULES 3
//structure global  
typedef struct {
    int notes[MAX_NOTES];
    int nb_notes;
    char nom_branche[50];
} Branche;
//structure global  
typedef struct {
    Branche branches[MAX_BRANCHES];
    int nb_branches;
    char nom_module; // 'A', 'B', 'C'
} ModuleData;
//prototype de fonction 
void ajouterNote();
void afficherTableau(ModuleData modules[], int nb_modules);
void afficherTableauFichier(ModuleData modules[], int nb_modules, FILE* f);
void chargerDonnees(ModuleData modules[], int* nb_modules);
void supprimerNotes();


#endif
