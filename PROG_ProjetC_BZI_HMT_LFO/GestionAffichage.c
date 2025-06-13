#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "GestionAffichage.h"

// fonction pour ajouter des notes
void ajouterNoteDeFichier() {
    FILE* fichier = fopen(FILE_NAME, "a"); // ouverture du fichier mode : Ouvre un fichier pour ajouter des donn�es � la fin. Si le fichier n'existe pas, il est cr��.
    if (!fichier) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    //d�claration de variable local
    char module;
    char branche[50];
    int note;

    do {
        printf("Entrez le module (A, B, C) : ");
        scanf(" %c", &module); //recup�re la choix du module
        module = toupper(module); //converti quoi qu'il arrive le caract�re en majuscule 
    } while (module != 'A' && module != 'B' && module != 'C');

    printf("Entrez le nom de la branche : ");
    scanf("%s", branche);

    do {
        printf("Entrez la note (1 a 6) : ");

        scanf("%d", &note);
    } while (note < 1 || note > 6); // note entre 1 et 6

    fprintf(fichier, "%c;%s;%d\n", module, branche, note); //print sur txt un chiffre, une chaine de carat�re, un nombre
    fclose(fichier);

    printf("Note ajoutee avec succes !\n");
}
// fonction permettant de charger des donn�es
void chargerDonnees(Systeme* s) {
    FILE* fichier = fopen(FILE_NAME, "r");
    if (!fichier) {
        printf("Aucune note trouvee.\n");
        s->nb_modules = 0;
    }

    s->nb_modules = 0;
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char module[TAILLE_NOM_MODULE];
        char branche[50];
        float note;

        if (sscanf(ligne, "%7s;%49[^;];%f", &module, branche, &note) == 3) {
            int i, j;
            // Chercher module
            for (i = 0; i < s->nb_modules; i++) {
                if (!strcmp(s->modules[i].nom_module, module))
                {
                    // Chercher branche
                    for (j = 0; j < s->modules[i].nb_branches; j++) {
                        if (!strcmp(s->modules[i].branches[j].nom_branche, branche)) {
                            // Ajouter la note
                            int k = s->modules[i].branches[j].nb_notes;
                            if (k < MAX_NOTES) {
                                s->modules[i].branches[j].notes[k].valeur = note;
                                k++;
                            }

                        }
                    }
                }  
            }
            

        }
    }
    fclose(fichier);
}

// Affiche le tableau complet a la console
void afficherTableau(Systeme* s) {
    for (int i = 0; i < s->nb_modules; i++) {
        printf("--------------------------------------------------------------------------------\n");
        printf("|-- Module %c\n", (char)s->modules[i].nom_module);
        printf("--------------------------------------------------------------------------------\n");

        // Afficher noms des branches
        printf("|");
        for (int j = 0; j < s->modules[i].nb_branches; j++) {
            printf("  %-20s |", s->modules[i].branches[j].nom_branche);
        }
        printf("\n--------------------------------------------------------------------------------\n");

        // Afficher notes par ligne
        int max_notes = 0;
        for (int j = 0; j < s->modules[i].nb_branches; j++) {
            if (s->modules[i].branches[j].nb_notes > max_notes)
                max_notes = s->modules[i].branches[j].nb_notes;
        }

        for (int l = 0; l < max_notes; l++) {
            printf("|");
            for (int j = 0; j < s->modules[i].nb_branches; j++) {
                if (l < s->modules[i].branches[j].nb_notes) {
                    printf("------------");
                    printf("  Note: %.2f|", s->modules[i].branches[j].notes[l].valeur);
                }
                else
                    printf("                |");
            }
            printf("\n");
        }

        printf("--------------------------------------------------------------------------------\n");
    }
}
//Affiche le tableau sur le dans le fichier
void afficherTableauFichier(Systeme* s, FILE* f) {
    for (int i = 0; i < s->nb_modules; i++) {
        fprintf(f, "--------------------------------------------------------------------------------\n");
        fprintf(f, "|-- Module %c\n", (char)s->modules[i].nom_module);
        fprintf(f, "--------------------------------------------------------------------------------\n");

        // Affichage des noms des branches
        fprintf(f, "|");
        for (int j = 0; j < s->modules[i].nb_branches; j++) {
            fprintf(f, "  %-20s |", s->modules[i].branches[j].nom_branche);
        }
        fprintf(f, "\n--------------------------------------------------------------------------------\n");

        // Affichage des notes par ligne
        int max_notes = 0;
        for (int j = 0; j < s->modules[i].nb_branches; j++) {
            if (s->modules[i].branches[j].nb_notes > max_notes)
                max_notes = s->modules[i].branches[j].nb_notes;
        }

        for (int l = 0; l < max_notes; l++) {
            fprintf(f, "|");
            for (int j = 0; j < s->modules[i].nb_branches; j++) {
                if (l < s->modules[i].branches[j].nb_notes) {
                    fprintf(f, "------------");
                    fprintf(f, "  Note: %.2f|", s->modules[i].branches[j].notes[l].valeur);
                }
                else
                    fprintf(f, "                |");
            }
            fprintf(f, "\n");
        }

        fprintf(f, "--------------------------------------------------------------------------------\n");
    }
}
// supprime toute les notes dans le fichier 
void supprimerNotes() {
    FILE* fichier = fopen(FILE_NAME, "w");
    if (fichier) {
        fclose(fichier);
        printf("Toutes les notes ont ete supprimees.\n");
    }
    else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

