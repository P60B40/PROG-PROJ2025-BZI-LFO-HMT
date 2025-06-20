#include "GestionNotes.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


Module* trouverModule(Systeme* s, const char* ptrNom_module) {
    int i;
    for (i = 0; i < s->nb_modules; i++) {
        if (strcmp(s->modules[i].nom_module, ptrNom_module) == 0)
            return &s->modules[i];
    }
    return NULL;
}

Branch* trouverBranche(Module* m, const char* ptrNom_branche) {
    int i;
    for (i = 0; i < m->nb_branches; i++) {
        if (strcmp(m->branches[i].nom_branche, ptrNom_branche) == 0)
            return &m->branches[i];
    }
    return NULL;
}

int ajouterNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note, float valeur) {
    int i;
    int j;
    int note_utiliser = 0;//
    int note_ajouter = 0;//

    Module* ptrm= trouverModule(s, ptrNom_module);
    Branch* ptrb = trouverBranche(ptrm, ptrNom_branche);

    if (!ptrm) {
        printf("Module introuvable\n");
        return 1;
    }
    else if (!ptrb) {
        printf("Branche introuvable\n");
        return 1;
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("la note doit etre entre 1.00 et 6.00\n");
        return 1;
    }
    else {
        for (i = 0; i < ptrb->nb_notes; i++) {
            if (strcmp(ptrb->notes[i].nom, ptrNom_note) == 0) {
                //char reponse[3] = { 0 };
               // printf("Nom de note deja utilisee\nvoulez vous ecrasez l'ancienne valeur ?\noui/non : ");
                //scanf(" %3s", &reponse);
                //getchar();
                //for (j = 0; j < 3; j++) {reponse[j] = toupper(reponse[j]);}//convertire en majuscule les caractères
               // if(strcmp( "OUI", reponse) == 1)//si user à choisit autre chose que OUI
                printf("Nom de note deja utilisee");
                    note_utiliser = 1;
            }
        }
    }

    if (note_utiliser == 0) {
        for (i = 0; i < ptrb->nb_notes; i++) {
            if ((ptrb->notes[i].valeur == 0.0)&&(note_ajouter == 0)) {
                strcpy(ptrb->notes[i].nom, ptrNom_note);
                ptrb->notes[i].valeur = valeur;
                printf("Note ajoutée avec succès.\n");
                note_ajouter = 1;
            }
        }
    }else{ return 1; }
    if (note_ajouter == 0) {
        printf("Aucune case vide pour ajouter la note.\n");
        return 1;
    }else{ return 0; }
}

int modifierNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note, float valeur) {
    int i;
    int note_modifier = 0;//
    Module* ptrm = trouverModule(s, ptrNom_module);

    Branch* ptrb = trouverBranche(ptrm, ptrNom_branche);
    if (!ptrm) {
        printf("Module introuvable.\n");
        return 1;
    }
    else if (!ptrb) {
        printf("Branche introuvable.\n");
        return 1;
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("pour rappel :\n la note doit etre entre 1.00 et 6.00\n");
        return 1;
    }
    else {
        for (i = 0; i < ptrb->nb_notes; i++) {
            if (strcmp(ptrb->notes[i].nom, ptrNom_note) == 0) {
                strcpy(ptrb->notes[i].nom, ptrNom_note);
                ptrb->notes[i].valeur = valeur;
                note_modifier = 1;
                printf("Note modifier avec succès.\n");
            }
        }
    }
    if (note_modifier == 0) {
        printf("Note introuvable.\n");
        printf("Verifiez l'orthographe du nom de la note.\n");
        return 1;
    }else{return 0;}
    
}

int supprimerNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note) {
    int i;
    int note_supprimer = 0;//
    Module* ptrm = trouverModule(s, ptrNom_module);
    Branch* ptrb = trouverBranche(ptrm, ptrNom_branche);

    if (!ptrm) {
        printf("Module introuvable.\n");
        return 1;
    }
    else if (!ptrb) {
        printf("Branche introuvable.\n");
        return 1;
    }
    else {
        for (i = 0; i < ptrb->nb_notes; i++) {
            if (strcmp(ptrb->notes[i].nom, ptrNom_note) == 0) {
                ptrb->notes[i].nom[0] = '\0';
                ptrb->notes[i].valeur = VALEUR_VIDE;
                printf("Note supprimée avec succès.\n");
                note_supprimer = 1;
            }
        }
    }
    if (note_supprimer == 0) {
        printf("Note introuvable.\n");
        printf("Verifiez l'orthographe du nom de la note.\n");
        return 1;
    }else{return 0;}
    
}