
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


#include <stdio.h>	// pour usage printf et scanf_s
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdint.h>

#include "main.h"
#include "GestionNotes.h"


int initialiserSysteme(Systeme* s) {

    int IndiceModules;
    int IndiceBranches;
    int IndiceNotes;

    //demander à user le nb de modules
    printf("Nombre de modules : ");
    scanf_s("%d", &s->nb_modules);

    // Allocation de pointeur de structure Module
    s->modules = calloc(s->nb_modules , sizeof(Module));

    if (!s->modules) {  //contôle sécurité de l'allocation de module
        perror("\nErreur alloc modules");
        return 1;
    }

    for (IndiceModules = 0; IndiceModules < s->nb_modules; IndiceModules++) {
        //nommé le module actuel
        printf("\nNom du module %d : ", IndiceModules + 1);
        scanf_s(" %7s", s->modules[IndiceModules].nom, (unsigned)_countof(s->modules[IndiceModules].nom));//l'espace avant le %7s fait sauter les éventuels caractères restants dans stdint(ex : \n)
             //fgets(s->modules[IndiceModules].nom, TAILLE_NOM_MODULE, stdin);
             //s->modules[IndiceModules].nom[strcspn(s->modules[IndiceModules].nom, "\n")] = '\0';// allocation du nom

        //demander à user le nb de branches dans le module actuel
        printf("\nNombre de branches pour %s : ", s->modules[IndiceModules].nom);
        scanf_s("%d", &s->modules[IndiceModules].nb_branches);

        // Allocation de pointeur de structure branche
        s->modules[IndiceModules].branches = malloc(s->modules[IndiceModules].nb_branches * sizeof(Branch));
        if (!s->modules[IndiceModules].branches) {  //contôle sécurité de l'allocation de branche
            perror("\nErreur alloc Branches");
            return 1;
        }

        for (IndiceBranches = 0; IndiceBranches < s->modules[IndiceModules].nb_branches; IndiceBranches++) {
            //nommé la branche actuel
            printf("\nNom de la branche %d du module %s : ", IndiceBranches + 1, s->modules[IndiceModules].nom);
            scanf_s(" %4s", s->modules[IndiceModules].branches[IndiceBranches].nom, (unsigned)_countof(s->modules[IndiceModules].branches[IndiceBranches].nom));
                // fgets(s->modules[IndiceModules].branches[IndiceBranches].nom, TAILLE_NOM_BRANCHE, stdin);
                // s->modules[IndiceModules].branches[IndiceBranches].nom[strcspn(s->modules[IndiceModules].branches[IndiceBranches].nom, "\n")] = '\0';

            //demander à user le nb de notes dans la branche actuel
            printf("\nNombre de notes pour la branche %s : ", s->modules[IndiceModules].branches[IndiceBranches].nom);
            scanf_s("%d", &s->modules[IndiceModules].branches[IndiceBranches].nb_notes);

            // Allocation de pointeur de structure Notes
            s->modules[IndiceModules].branches[IndiceBranches].notes = malloc(s->modules[IndiceModules].branches[IndiceBranches].nb_notes * sizeof(Note));
            if (!s->modules[IndiceModules].branches[IndiceBranches].notes) {  //contôle sécurité de l'allocation de Notes
                perror("\nErreur alloc notes");
                return 1;
            }

            for (IndiceNotes = 0; IndiceNotes < s->modules[IndiceModules].branches[IndiceBranches].nb_notes; IndiceNotes++) {
                //nommé la note actuel
                printf("\nNom de la note %d de la branche %s appartenant au module %s : ", IndiceNotes + 1, s->modules[IndiceModules].branches[IndiceBranches].nom,s->modules[IndiceModules].nom);
                scanf_s(" %20s", s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom, (unsigned)_countof(s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom));
                     // fgets(s->modules[IndiceModules].branches[IndiceBranches].nom, NOM_TAILLE, stdin);
                     // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom[strcspn(s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom, "\n")] = '\0'; //pour mettre le nom de la note
               // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom[0] = '\0';                  //pour pas mettre de nom et laisser vide
               // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].valeur = VALEUR_VIDE;           //pour pas mettre de note
                printf("\nNom donnee a la note %d de la branche %s appartenant au module %s est %s:", IndiceNotes + 1, s->modules[IndiceModules].branches[IndiceBranches].nom, s->modules[IndiceModules].nom, s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom);
            }
            printf("\nNom donnee a la branche %d du module %s : %s ", IndiceBranches + 1, s->modules[IndiceModules].nom, s->modules[IndiceModules].branches[IndiceBranches].nom);
        }
        printf("\nNom donnee au module %d : %s ", IndiceModules + 1, s->modules[IndiceModules].nom);
    }
}



/*************************************************************************************************************************/


void libererSysteme(Systeme* s) {
    int i;
    int j;
    int k;
    for (i = 0; i < s->nb_modules; i++) {
        for (j = 0; j < s->modules[i].nb_branches; j++) {   
            free(s->modules[i].branches[j].notes);
        }
        free(s->modules[i].branches);
    }
    free(s->modules);
}

int main() {
    Systeme s;
    initialiserSysteme(&s);

    int choix;
    char mod[NOM_TAILLE], br[NOM_TAILLE], note[NOM_TAILLE];
    float val;

    do {
        printf("\n1. Ajouter note\n2. Supprimer note\n3. Afficher\n0. Quitter\nChoix : ");
        scanf("%d", &choix); getchar();

        switch (choix) {
        case 1:
            printf("Nom module : ");
            fgets(mod, NOM_TAILLE, stdin);
            mod[strcspn(mod, "\n")] = '\0';
            printf("Nom branche : ");
            fgets(br, NOM_TAILLE, stdin);
            br[strcspn(br, "\n")] = '\0';
            printf("Nom note : ");
            fgets(note, NOM_TAILLE, stdin);
            note[strcspn(note, "\n")] = '\0';
            printf("Valeur : ");
            scanf("%f", &val);
            getchar();
            ajouterNote(&s, mod, br, note, val);
            break;
        case 2:
            printf("Nom module : ");
            fgets(mod, NOM_TAILLE, stdin);
            mod[strcspn(mod, "\n")] = '\0';
            printf("Nom branche : ");
            fgets(br, NOM_TAILLE, stdin);
            br[strcspn(br, "\n")] = '\0';
            printf("Nom note : ");
            fgets(note, NOM_TAILLE, stdin);
            note[strcspn(note, "\n")] = '\0';
            supprimerNote(&s, mod, br, note);
            break;
        case 3:
            afficherSysteme(&s);
            break;
        case 5:
            printf("Nom module : ");
            fgets(mod, NOM_TAILLE, stdin);
            mod[strcspn(mod, "\n")] = '\0';
            printf("Nom branche : ");
            fgets(br, NOM_TAILLE, stdin);
            br[strcspn(br, "\n")] = '\0';
            printf("Nom note : ");
            fgets(note, NOM_TAILLE, stdin);
            note[strcspn(note, "\n")] = '\0';
            printf("Valeur : ");
            scanf("%f", &val);
            getchar();
            modifierNote(&s, mod, br, note, val);
            break;
        }
    } while (choix != 0);
    afficherTableauDansFichier(&s, "test");
    libererSysteme(&s);

    return 0;
}


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



/*
void initialiserSysteme(Systeme* s) {

    int i;
    int j;
    int k;

    printf("Nombre de modules : ");
    scanf_s("%d", &s->nb_modules);
    getchar();//vider le tampon

    s->modules = malloc(s->nb_modules * sizeof(Module));
    // ce qu'il faudrait plustôt faire c'est l'inverse de Benji, c'est à dire de dabord faire un malloc du nb de notes pour 1 branches,
    //puis faire un malloc pour cette branche ci avec ce nb de note là en prenant ce nom de branche donnée par user ou .txt,
    //refaire ces actions autant de foit qu'il y'a de branches donnée par user ou .txt
    //, et encore faire un malloc pour ce module ci avec ce nb de branches là en prenant ce nom de module donnée par user ou .txt
    //refaire ces actions autant de foit qu'il y'a de modules donnée par user ou .txt

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
*/


/*************************************************************************************************************************/

/*
void initialiserSysteme(Systeme* s) {

    int i;
    int j;
    int k;

    printf("Nombre de modules : ");
    scanf_s("%d", &s->nb_modules);
    getchar();//vider le tampon

    s->modules = malloc(s->nb_modules * sizeof(Module));

    // ce qu'il faudrait plustôt faire c'est l'inverse de Benji, c'est à dire de dabord faire un malloc du nb de notes pour 1 branches,
    //puis faire un malloc pour cette branche ci avec ce nb de note là en prenant ce nom de branche donnée par user ou .txt,
    //refaire ces actions autant de foit qu'il y'a de branches donnée par user ou .txt
    //, et encore faire un malloc pour ce module ci avec ce nb de branches là en prenant ce nom de module donnée par user ou .txt
    //refaire ces actions autant de foit qu'il y'a de modules donnée par user ou .txt

    for (i = 0; i < s->nb_modules; i++) {
        printf("Nom du module %d : ", i + 1);
        //enregistrer ube chaine de caractères

        //fgets(s->modules[i].nom, TAILLE_NOM_MODULE, stdin);
        //s->modules[i].nom[strcspn(s->modules[i].nom, "\n")] = '\0';

        int Nb_branches;
        printf("Nombre de branches pour ce module : ");
        scanf_s("%d", &Nb_branches);
        getchar();//vider le tampon

       // s->modules[i].branches = malloc(s->modules[i].nb_branches * sizeof(Branch));

        for (j = 0; j < Nb_branches; j++) {
            printf("Nom de la branche %d : ", j + 1);

         //   fgets(s->modules->branches->nom, TAILLE_NOM_BRANCHE, stdin);
         //   s->modules->branches->nom[strcspn(s->modules->branches->nom, "\n")] = '\0';

            int Nb_notes;
            printf("Nombre de notes pour cette branche : ");
            scanf_s("%d", &Nb_notes);
            getchar();//vider le tampon

            s->modules[i].branches[j].notes = malloc(Nb_notes * sizeof(Note));

            for (k = 0; k < s->modules->branches->nb_notes; k++) {

               // printf("Nom de la note %d de la branche %4s : ", j + 1, s->modules->branches->nom);
               // scanf_s("%20s", &s->modules->branches->notes[k].nom, (unsigned)_countof(s->modules->branches->notes->nom));
                getchar();

                s->modules->branches->notes[k].valeur = VALEUR_VIDE;
            }

            s->modules->branches = malloc(s->modules->branches->notes);
        }
        printf("\ntaille branche 1 : %d ", (unsigned) sizeof(s->modules->branches[0]));
        printf("\ntaille branche 2 : %d ", (unsigned) sizeof(s->modules->branches[1]));
    }
}
*/
