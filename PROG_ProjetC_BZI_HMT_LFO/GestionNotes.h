
#ifndef GESTIONNOTES_H
#define GESTIONNOTES_H

#include "main.h"

Module* trouverModule(Systeme* s, const char* nom_module);
Branch* trouverBranche(Module* m, const char* nom_branche);
int ajouterNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur);
int modifierNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note, float valeur);
int supprimerNote(Systeme* s, const char* nom_module, const char* nom_branche, const char* nom_note);

#endif