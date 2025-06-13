#include "GestionNotes.h"
#include <stdint.h>


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

int ajouterNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur) {
    int i;
    uint8_t note_utiliser = 0;
    uint8_t note_ajouter = 0;

    Module* m = trouverModule(s, nom_module);
    Branch* b = trouverBranche(m, nom_branche);

    if (!m) {
        printf("Module introuvable.\n");
        return 1;
    }
    else if (!b) {
        printf("Branche introuvable.\n");
        return 1;
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("pour rappel :\n la note doit etre entre 1.00 et 6.00\n");
        return 1;
    }
    else {
        for (i = 0; i < b->nb_notes; i++) {
            if (strcmp(b->notes[i].nom, nom_note) == 0) {
                printf("Nom de note déjà utilisé.\n");
                note_utiliser = 1;
            }
        }
    }

    if (note_utiliser == 0) {
        for (i = 0; i < b->nb_notes; i++) {
            if (b->notes[i].valeur == VALEUR_VIDE && note_ajouter == 0) {
                strcpy(b->notes[i].nom, nom_note);
                b->notes[i].valeur = valeur;
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

int modifierNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur) {
    int i;
    uint8_t note_modifier = 0;
    Module* m = trouverModule(s, nom_module);

    Branch* b = trouverBranche(m, nom_branche);
    if (!m) {
        printf("Module introuvable.\n");
        return 1;
    }
    else if (!b) {
        printf("Branche introuvable.\n");
        return 1;
    }
    else if (valeur < 1.00 || valeur > 6.00) {
        printf("note invalide \n");
        printf("pour rappel :\n la note doit etre entre 1.00 et 6.00\n");
        return 1;
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
        return 1;
    }
    return 0;
}

int supprimerNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note) {
    int i;
    uint8_t note_supprimer = 0;
    Module* m = trouverModule(s, nom_module);
    Branch* b = trouverBranche(m, nom_branche);

    if (!m) {
        printf("Module introuvable.\n");
        return 1;
    }
    else if (!b) {
        printf("Branche introuvable.\n");
        return 1;
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
        return 1;
    }else{return 0;}
    
}