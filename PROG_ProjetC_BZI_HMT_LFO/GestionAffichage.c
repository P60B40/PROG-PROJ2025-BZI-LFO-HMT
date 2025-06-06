#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Header.h"

// fonction pour ajouter des notes
void ajouterNote() {
    FILE* fichier = fopen(FILE_NAME, "a"); // ouverture du fichier mode : Ouvre un fichier pour ajouter des données à la fin. Si le fichier n'existe pas, il est créé.
    if (!fichier) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    //déclaration de variable local
    char module;
    char branche[50];
    int note;

    do {
        printf("Entrez le module (A, B, C) : ");
        scanf(" %c", &module); //recupère la choix du module
        module = toupper(module); //converti quoi qu'il arrive le caractère en majuscule 
    } while (module != 'A' && module != 'B' && module != 'C');

    printf("Entrez le nom de la branche : ");
    scanf("%s", branche);

    do {
        printf("Entrez la note (1 a 6) : ");

        scanf("%d", &note);
    } while (note < 1 || note > 6); // note entre 1 et 6

    fprintf(fichier, "%c;%s;%d\n", module, branche, note); //print sur txt un chiffre, une chaine de caratère, un nombre
    fclose(fichier);

    printf("Note ajoutee avec succes !\n");
}
// fonction permettant de charger des données
void chargerDonnees(ModuleData modules[], int* nb_modules) {
    FILE* fichier = fopen(FILE_NAME, "r");
    if (!fichier) {
        printf("Aucune note trouvee.\n");
        *nb_modules = 0;
        return;
    }

    *nb_modules = 0;
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char module;
        char branche[50];
        int note;

        if (sscanf(ligne, "%c;%49[^;];%d", &module, branche, &note) == 3) {
            int i, j;
            // Chercher module
            for (i = 0; i < *nb_modules; i++) {
                if (modules[i].nom_module == module)
                    break;
            }
            if (i == *nb_modules) {
                modules[i].nom_module = module;
                modules[i].nb_branches = 0;
                (*nb_modules)++;
            }

            // Chercher branche
            for (j = 0; j < modules[i].nb_branches; j++) {
                if (strcmp(modules[i].branches[j].nom_branche, branche) == 0)
                    break;
            }
            if (j == modules[i].nb_branches) {
                strcpy(modules[i].branches[j].nom_branche, branche);
                modules[i].branches[j].nb_notes = 0;
                modules[i].nb_branches++;
            }

            // Ajouter la note
            int k = modules[i].branches[j].nb_notes;
            if (k < MAX_NOTES) {
                modules[i].branches[j].notes[k] = note;
                modules[i].branches[j].nb_notes++;
            }
        }
    }
    fclose(fichier);
}

// Affiche le tableau complet a la console
void afficherTableau(ModuleData modules[], int nb_modules) {
    for (int i = 0; i < nb_modules; i++) {
        printf("--------------------------------------------------------------------------------\n");
        printf("|-- Module %c\n", modules[i].nom_module);
        printf("--------------------------------------------------------------------------------\n");

        // Afficher noms des branches
        printf("|");
        for (int j = 0; j < modules[i].nb_branches; j++) {
            printf("  %-20s |", modules[i].branches[j].nom_branche);
        }
        printf("\n--------------------------------------------------------------------------------\n");

        // Afficher notes par ligne
        int max_notes = 0;
        for (int j = 0; j < modules[i].nb_branches; j++) {
            if (modules[i].branches[j].nb_notes > max_notes)
                max_notes = modules[i].branches[j].nb_notes;
        }

        for (int l = 0; l < max_notes; l++) {
            printf("|");
            for (int j = 0; j < modules[i].nb_branches; j++) {
                if (l < modules[i].branches[j].nb_notes)
                    printf("  Note: %-12d|", modules[i].branches[j].notes[l]);
                else
                    printf("                |");
            }
            printf("\n");
        }

        printf("--------------------------------------------------------------------------------\n");
    }
}
//Affiche le tableau sur le dans le fichier
void afficherTableauFichier(ModuleData modules[], int nb_modules, FILE* f) {
    for (int i = 0; i < nb_modules; i++) {
        fprintf(f, "--------------------------------------------------------------------------------\n");
        fprintf(f, "|-- Module %c\n", modules[i].nom_module);
        fprintf(f, "--------------------------------------------------------------------------------\n");

        // Affichage des noms des branches
        fprintf(f, "|");
        for (int j = 0; j < modules[i].nb_branches; j++) {
            fprintf(f, "  %-20s |", modules[i].branches[j].nom_branche);
        }
        fprintf(f, "\n--------------------------------------------------------------------------------\n");

        // Affichage des notes par ligne
        int max_notes = 0;
        for (int j = 0; j < modules[i].nb_branches; j++) {
            if (modules[i].branches[j].nb_notes > max_notes)
                max_notes = modules[i].branches[j].nb_notes;
        }

        for (int l = 0; l < max_notes; l++) {
            fprintf(f, "|");
            for (int j = 0; j < modules[i].nb_branches; j++) {
                if (l < modules[i].branches[j].nb_notes)
                    fprintf(f, "  Note: %-12d|", modules[i].branches[j].notes[l]);
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

