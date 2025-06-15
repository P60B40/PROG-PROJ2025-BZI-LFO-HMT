
#include <stdio.h>	// pour usage printf et scanf_s
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "main.h"
#include "GestionNotes.h"
#include "GestionAffichage.h"


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
        scanf_s(" %7s", s->modules[IndiceModules].nom_module, (unsigned)_countof(s->modules[IndiceModules].nom_module));//l'espace avant le %7s fait sauter les éventuels caractères restants dans stdint(ex : \n)
             //fgets(s->modules[IndiceModules].nom, TAILLE_NOM_MODULE, stdin);
             //s->modules[IndiceModules].nom[strcspn(s->modules[IndiceModules].nom, "\n")] = '\0';// allocation du nom

        //demander à user le nb de branches dans le module actuel
        printf("\nNombre de branches pour %s : ", s->modules[IndiceModules].nom_module);
        scanf_s("%d", &s->modules[IndiceModules].nb_branches);

        // Allocation de pointeur de structure branche
        s->modules[IndiceModules].branches = malloc(s->modules[IndiceModules].nb_branches * sizeof(Branch));
        if (!s->modules[IndiceModules].branches) {  //contôle sécurité de l'allocation de branche
            perror("\nErreur alloc Branches");
            return 1;
        }

        for (IndiceBranches = 0; IndiceBranches < s->modules[IndiceModules].nb_branches; IndiceBranches++) {
            //nommé la branche actuel
            printf("\nNom de la branche %d du module %s : ", IndiceBranches + 1, s->modules[IndiceModules].nom_module);
            scanf_s(" %4s", s->modules[IndiceModules].branches[IndiceBranches].nom_branche, (unsigned)_countof(s->modules[IndiceModules].branches[IndiceBranches].nom_branche));
                // fgets(s->modules[IndiceModules].branches[IndiceBranches].nom, TAILLE_NOM_BRANCHE, stdin);
                // s->modules[IndiceModules].branches[IndiceBranches].nom[strcspn(s->modules[IndiceModules].branches[IndiceBranches].nom, "\n")] = '\0';

            //demander à user le nb de notes dans la branche actuel
            printf("\nNombre de notes pour la branche %s : ", s->modules[IndiceModules].branches[IndiceBranches].nom_branche);
            scanf_s("%d", &s->modules[IndiceModules].branches[IndiceBranches].nb_notes);

            // Allocation de pointeur de structure Notes
            s->modules[IndiceModules].branches[IndiceBranches].notes = malloc(s->modules[IndiceModules].branches[IndiceBranches].nb_notes * sizeof(Note));
            if (!s->modules[IndiceModules].branches[IndiceBranches].notes) {  //contôle sécurité de l'allocation de Notes
                perror("\nErreur alloc notes");
                return 1;
            }

            for (IndiceNotes = 0; IndiceNotes < s->modules[IndiceModules].branches[IndiceBranches].nb_notes; IndiceNotes++) {
                //nommé la note actuel
                printf("\nNom de la note %d de la branche %s appartenant au module %s : ", IndiceNotes + 1, s->modules[IndiceModules].branches[IndiceBranches].nom_branche,s->modules[IndiceModules].nom_module);
                scanf_s(" %20s", s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom, (unsigned)_countof(s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom));
                     // fgets(s->modules[IndiceModules].branches[IndiceBranches].nom, NOM_TAILLE, stdin);
                     // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom[strcspn(s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom, "\n")] = '\0'; //pour mettre le nom de la note
               // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom[0] = '\0';                  //pour pas mettre de nom et laisser vide
               // s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].valeur = VALEUR_VIDE;           //pour pas mettre de note
                printf("\nNom donnee a la note %d de la branche %s appartenant au module %s est %s:", IndiceNotes + 1, s->modules[IndiceModules].branches[IndiceBranches].nom_branche, s->modules[IndiceModules].nom_module, s->modules[IndiceModules].branches[IndiceBranches].notes[IndiceNotes].nom);
            }
            printf("\nNom donnee a la branche %d du module %s : %s ", IndiceBranches + 1, s->modules[IndiceModules].nom_module, s->modules[IndiceModules].branches[IndiceBranches].nom_branche);
        }
        printf("\nNom donnee au module %d : %s ", IndiceModules + 1, s->modules[IndiceModules].nom_module);
    }
    return 0;
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
    afficherTableau(&s);

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
    afficherTableauFichier(&s, "logModulesNotes.txt");
    libererSysteme(&s);

    return 0;
}
