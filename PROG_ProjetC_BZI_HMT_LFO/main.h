//-----------------------------------------------------------------------------------//
// Nom du projet 		: 
// Nom du fichier 		: 
// Date de création 	: 30.09.2015
// Date de modification : 07.01.2016
//
// Auteur 				: Philou (Ph. Bovey)
//
// Version				: x.x
//
// Description          : 
//
//
// Remarques :            lien pour la table ASCII :
// 						  -> http://www.asciitable.com/
// 						  lien pour la saisie de clavier avec getc & getchar pour ne pas
//                        avoir des erreurs d'interprétation
// 						  -> http://fr.openclassrooms.com/informatique/cours/utiliser-les-bonnes-fonctions-d-entree
// 						  lien vers différents
// 						  -> http://fr.wikipedia.org/wiki/String.h
//----------------------------------------------------------------------------------//

#ifndef MAIN_H
#define MAIN_H

//--- librairie standart ---//


#define NOM_TAILLE 20
#define TAILLE_NOM_MODULE 7
#define TAILLE_NOM_BRANCHE 4
#define VALEUR_VIDE -1.0
#define CASE_LARGEUR 25

#define CLEAR system("cls"),resultat = 0 // Effacer l'écran et reset resultat

#pragma warning(disable : 4996)

typedef struct {
    char nom[NOM_TAILLE];
    float valeur;
} Note;

typedef struct {
    char nom[TAILLE_NOM_BRANCHE];
    Note* notes;
    int nb_notes;
} Branch;

typedef struct {
    char nom[TAILLE_NOM_MODULE];
    Branch* branches;
    int nb_branches;
} Module;

typedef struct {
    Module* modules;
    int nb_modules;
} Systeme;

int initialiserSysteme(Systeme* s);
void libererSysteme(Systeme* s);

#endif