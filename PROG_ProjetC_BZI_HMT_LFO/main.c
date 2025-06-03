
//-----------------------------------------------------------------------------------//
// Nom du projet 		: Demo
// Nom du fichier 		: Projet_Test
// Date de création 	: 
// Date de modification : 
//
// Auteur 				: VolutedPenny235
//
// Version				: 0.1
//
// Description          : 
//----------------------------------------------------------------------------------//


#include "main.h"
/*

void main(void)
{
    int touche;
    static float resultat = 0;
    ptrGbl = &resultat;         //pointeur globale pointe sur resultat
    char  Forme[20];

    while (1)
    {
        //---QUESTION UTILISATEUR---//
        printf("selectionner une forme : ");        //afficher
        scanf_s("%20s", Forme, (unsigned)_countof(Forme));   //lecture du clavier et écrire une chaine de caratères dans le tableau Forme

        //---LISTE---//
        if (strcmp(Forme, "list") == 0)                 //comparer la chaine de caractère "list" au tableau Forme et si la différence vaut 0 alors dans le tableau y as le mot "list"
        {
            printf("-carre \n-rectangle \n-triangle \n-cercle");    //Affichage de la liste
        }
        //---CARRE---//
        else if (strcmp(Forme, "carre") == 0)        //comparer la chaine de caractère "carre" au tableau Forme et si la différence vaut 0 alors dans le tableau y as le mot "carre"
        {
            printf("\nentree la longueur du %s : ", Forme);
                                        //appel de la fonction pour calculer la surface du carrer
        }
        //---RECTANGLE---//
        else if (strcmp(Forme, "rectangle") == 0)    //comparer la chaine de caractère "rectangle" au tableau Forme et si la différence vaut 0 alors dans le tableau y as le mot "rectangle"
        {
            printf("\nentree la longueur et la hauteur du %s : ", Forme);
                                   //appel de la fonction pour calculer la surface du rectangle
        }
        //---TRIANGLE---//
        else if (strcmp(Forme, "triangle") == 0)     //comparer la chaine de caractère "triangle" au tableau Forme et si la différence vaut 0 alors dans le tableau y as le mot "triangle"
        {
            printf("\nentree la base et la hauteur du %s : ", Forme);
                                 //appel de la fonction pour calculer la surface du triangle
        }
        //---CERCLE---//
        else if (strcmp(Forme, "cercle") == 0)   //comparer la chaine de caractère "cercle" au tableau Forme et si la différence vaut 0 alors dans le tableau y as le mot "cercle"
        {
            printf("\nentree le rayon du %s : ", Forme);
                                       //appel de la fonction pour calculer la surface du cercle
        }
        //---ERREUR---//
        else                                        //si l'utilisateur a entree une chaine de carrctères non répertorier 
        {
            printf("la forme saisie ne correspond pas a l assortiment");    //Affichage erreur
        }

        //---RESULTAT---//
        if (resultat != 0)
            printf("\nla surface du %s est de = %f", Forme, resultat);  //afficher le résultat du calcule en fonction de la forme selctionner 

            

        //---REDO OR BREAK---//
        while (1)
        {
            if (_kbhit()) {         //fonction lier à la librairie conio.h pour lire n'importe quelle touche presser du clavier
                touche = _getch();  // Lire la touche
                if (touche != 0) {  //si une touche est presser
                    break;  // Quitter la boucle et terminer le programme
                }
            }
        }
        printf("\nta touche : %c = %d", touche, touche);
        if (touche == 27)// Si la touche est 'Échap' (Escape), code ASCII 27
            break;              //fin du programme

        //---EFFACER ECRAN---//
        CLEAR;

    }
}

/*
while (1)
{
    if (_kbhit()) {         //fonction lier à la librairie conio.h pour lire n'importe quelle touche presser du clavier
        touche = _getch();  // Lire la touche
        if (touche != 0) {  //si une touche est presser
            break;  // Quitter la boucle et terminer le programme
        }
    }
}
printf("\nta touche : %c = %d", touche, touche);
if (touche == 27)// Si la touche est 'Échap' (Escape), code ASCII 27
break;              //fin du programme
*/

void main(void) {


}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NOM_TAILLE 20
#define TAILLE_NOM_MODULE 7
#define TAILLE_NOM_BRANCHE 4
#define VALEUR_VIDE -1.0
#define CASE_LARGEUR 25

#pragma warning(disable : 4996)

typedef struct {
    char nom[NOM_TAILLE];
    float valeur;
} Note;

typedef struct {
    char nom[4];
    //Note* notes;
    int nb_notes;
} Branch;

typedef struct {
    char nom[TAILLE_NOM_MODULE];
    //Branch* branches;
    int nb_branches;
} Module;

typedef struct {
    //Module* modules;
    TbAlloc Tableau;
    int nb_modules;
} Systeme;

typedef struct {
    Note* notes;
    Branch* branches;
    Module* modules;
}TbAlloc;

void initialiserSysteme(Systeme* s) {

    int i;
    int j;
    int k;

    printf("Nombre de modules : ");
    scanf_s("%d", &s->nb_modules);
    getchar();//vider le tampon

    s->Tableau.modules = malloc(s->nb_modules * sizeof(Module));

    for (i = 0; i < s->nb_modules; i++) {
        printf("Nom du module %d : ", i + 1);
        fgets(s->modules[i].nom, TAILLE_NOM_MODULE, stdin);
        s->modules[i].nom[strcspn(s->modules[i].nom, "\n")] = '\0';

        printf("Nombre de branches pour %s : ", s->modules[i].nom);
        scanf_s("%d", &s->modules[i].nb_branches);
        getchar();

        s->modules[i].branches = malloc(s->modules[i].nb_branches * sizeof(Branch));

        for (j = 0; j < s->modules[i].nb_branches; j++) {
            printf("Nom de la branche %d de %s : ", j + 1, s->modules[i].nom);
            fgets(s->modules[i].branches[j].nom, TAILLE_NOM_BRANCHE, stdin);
            s->modules[i].branches[j].nom[strcspn(s->modules[i].branches[j].nom, "\n")] = '\0';

            printf("Nombre de notes pour la branche %s : ", s->modules[i].branches[j].nom);
            scanf("%d", &s->modules[i].branches[j].nb_notes);
            getchar();

            s->modules[i].branches[j].notes = malloc(s->modules[i].branches[j].nb_notes * sizeof(Note));

            for (k = 0; k < s->modules[i].branches[j].nb_notes; k++) {
                s->modules[i].branches[j].notes[k].nom[0] = '\0';
                s->modules[i].branches[j].notes[k].valeur = VALEUR_VIDE;
            }
        }
    }
}

Module* trouverModule(Systeme* s, const char* nom_module) {
    int i;
    for (i = 0; i < s->nb_modules; i++) {
        if (strcmp(s->modules[i].nom, nom_module) == 0)
            return &s->modules[i];
    }
    return NULL;
}

Branch* trouverBranche(Module* m, const char* nom_branche) {
    int i;
    for (i = 0; i < m->nb_branches; i++) {
        if (strcmp(m->branches[i].nom, nom_branche) == 0)
            return &m->branches[i];
    }
    return NULL;
}

void ajouterNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur) {
    int i;
    uint8_t note_utiliser = 0;
    uint8_t note_ajouter = 0;

    Module* m = trouverModule(s, nom_module);
    Branch* b = trouverBranche(m, nom_branche);

    if (!m) {
        printf("Module introuvable.\n");
    }
    else if (!b) {
        printf("Branche introuvable.\n");
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("pour rappel :\n la note doit etre entre 1.00 et 6.00\n");
    }
    else {
        for (i = 0; i < b->nb_notes; i++) {
            if (strcmp(b->notes[i].nom, nom_note) == 0) {
                printf("Nom de note déjà utilisé.\n");
                note_utiliser = 1;
            }
        }
    }

    if (note_utiliser == 0)
        for (i = 0; i < b->nb_notes; i++) {
            if (b->notes[i].valeur == VALEUR_VIDE && note_ajouter == 0) {
                strcpy(b->notes[i].nom, nom_note);
                b->notes[i].valeur = valeur;
                printf("Note ajoutée avec succès.\n");
                note_ajouter = 1;
            }
        }
    if (note_ajouter == 0) {
        printf("Aucune case vide pour ajouter la note.\n");
    }
}

void modifierNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur) {
    int i;
    uint8_t note_modifier = 0;
    Module* m = trouverModule(s, nom_module);

    Branch* b = trouverBranche(m, nom_branche);
    if (!m) {
        printf("Module introuvable.\n");
    }
    else if (!b) {
        printf("Branche introuvable.\n");
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("pour rappel :\n la note doit etre entre 1.00 et 6.00\n");
    }
    else {
        for (i = 0; i < b->nb_notes; i++) {
            if (strcmp(b->notes[i].nom, nom_note) == 0) {
                strcpy(b->notes[i].nom, nom_note);
                b->notes[i].valeur = valeur;
                note_modifier = 1;
                printf("Note modifier avec succès.\n");
            }
        }
    }
    if (note_modifier == 0) {
        printf("Note introuvable.\n");
        printf("Verifiez l'orthographe du nom de la note.\n");
    }
}

void supprimerNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note) {
    int i;
    uint8_t note_supprimer = 0;
    Module* m = trouverModule(s, nom_module);
    Branch* b = trouverBranche(m, nom_branche);

    if (!m) {
        printf("Module introuvable.\n");
    }
    else if (!b) {
        printf("Branche introuvable.\n");
    }
    else {
        for (i = 0; i < b->nb_notes; i++) {
            if (strcmp(b->notes[i].nom, nom_note) == 0) {
                b->notes[i].nom[0] = '\0';
                b->notes[i].valeur = VALEUR_VIDE;
                printf("Note supprimée avec succès.\n");
                note_supprimer = 1;
            }
        }
    }
    if (note_supprimer == 0) {
        printf("Note introuvable.\n");
        printf("Verifiez l'orthographe du nom de la note.\n");
    }
}