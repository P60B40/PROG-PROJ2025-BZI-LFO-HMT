
#ifndef GESTIONNOTES_H
#define GESTIONNOTES_H

#include "main.h"

Module* trouverModule(Systeme* s, const char* ptrNom_module);
Branch* trouverBranche(Module* m, const char* ptrNom_branche);
int ajouterNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note, float valeur);
int modifierNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note, float valeur);
int supprimerNote(Systeme* s, const char* ptrNom_module, const char* ptrNom_branche, const char* ptrNom_note);

#endif