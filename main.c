#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"
#include "edition.h"
#include "stats.h"
#include "affichage.h"
#include "persistence.h" // Modifié ici

#define MAX_LIGNES 20

void initialiserCatalogue(Ligne catalogue[], int nombreMaxLignes) {
    for (int i = 0; i < nombreMaxLignes; i++) {
        catalogue[i].nomLigne[0] = '\0';
        catalogue[i].tete = NULL;
    }
}

int afficherMenu() {
    int choix;
    printf("\n=============================================\n");
    printf("    C-TRANSIT : GESTION DU RESEAU URBAIN     \n");
    printf("=============================================\n");
    printf("1. Creer une nouvelle ligne de transport\n");
    printf("2. Ajouter une station a une ligne\n");
    printf("3. Supprimer une station d'une ligne\n");
    printf("4. Rechercher une station dans tout le reseau\n");
    printf("5. Afficher tout le reseau\n");
    printf("6. Afficher l'itineraire detaille (Aller/Retour)\n");
    printf("7. Afficher les statistiques (Nombre & Duree)\n");
    printf("8. Sauvegarder et Quitter\n");
    printf("=============================================\n");
    printf("Votre choix (1-8) : ");
    
    if (scanf("%d", &choix) != 1) {
        while (getchar() != '\n'); 
        return -1;
    }
    return choix;
}

int main() {
    Ligne catalogue[MAX_LIGNES];
    int nbLignesActuelles = 0;
    int choix;
    
    char nomTemporaire[50];
    int positionTemporaire;
    int indexLigne;

    // Utilisation de ta fonction d'initialisation
    initialiserCatalogue(catalogue, MAX_LIGNES);

    // Chargement via persistence.h
    chargerFormatJSON("reseau.json", catalogue, &nbLignesActuelles);

    do {
        choix = afficherMenu();

        switch (choix) {
            case 1:
                printf("\n--- CREATION D'ONE NOUVELLE LIGNE ---\n");
                creerNouvelleLigne(catalogue, &nbLignesActuelles, MAX_LIGNES);
                break;

            case 2:
                printf("\n--- AJOUTER UNE STATION ---\n");
                if (nbLignesActuelles == 0) {
                    printf("⚠️ Erreur : Creez d'abord une ligne.\n");
                    break;
                }
                printf("Selectionnez l'index de la ligne (0 a %d) : ", nbLignesActuelles - 1);
                scanf("%d", &indexLigne);
                if (indexLigne < 0 || indexLigne >= nbLignesActuelles) {
                    printf("❌ Index invalide.\n");
                    break;
                }
                printf("Nom de la station : ");
                scanf(" %[^\n]", nomTemporaire);
                printf("Type d'insertion :\n 0: En tete\n 1: En fin\n 2: A position precise\nChoix : ");
                int typeInsertion;
                scanf("%d", &typeInsertion);

                if (typeInsertion == 0) {
                    insererEnTete(&catalogue[indexLigne], nomTemporaire);
                } else if (typeInsertion == 1) {
                    insererEnFin(&catalogue[indexLigne], nomTemporaire);
                } else if (typeInsertion == 2) {
                    printf("Entrez l'index de la position : ");
                    scanf("%d", &positionTemporaire);
                    insererAIndex(&catalogue[indexLigne], nomTemporaire, positionTemporaire);
                }
                break;

            case 3:
                printf("\n--- SUPPRIMER UNE STATION ---\n");
                if (nbLignesActuelles == 0) break;
                printf("Index de la ligne : ");
                scanf("%d", &indexLigne);
                printf("Nom de la station : ");
                scanf(" %[^\n]", nomTemporaire);
                supprimerStation(&catalogue[indexLigne], nomTemporaire);
                break;

            case 4:
                printf("\n--- RECHERCHER UNE STATION ---\n");
                printf("Nom de la station cherchee : ");
                scanf(" %[^\n]", nomTemporaire);
                Ligne* ligneTrouvee = NULL;
                Station* st = rechercherStationGlobal(catalogue, nbLignesActuelles, nomTemporaire, &ligneTrouvee);
                if (st != NULL && ligneTrouvee != NULL) {
                    printf("✅ Trouvee sur la ligne : %s\n", ligneTrouvee->nomLigne);
                } else {
                    printf("❌ Introuvable.\n");
                }
                break;

            case 5:
                afficherReseauGlobal(catalogue, nbLignesActuelles);
                break;

            case 6:
                printf("\n--- ITINERAIRE DETAILLES ---\n");
                printf("Index de la ligne : ");
                scanf("%d", &indexLigne);
                printf("\n--- SENS ALLER ---\n");
                afficherItineraireAllerRec(catalogue[indexLigne].tete);
                printf("\n--- SENS RETOUR ---\nNULL");
                afficherItineraireRetourRec(catalogue[indexLigne].tete);
                printf("\n");
                break;

            case 7:
                printf("\n--- STATISTIQUES RECURSIVES ---\n");
                printf("Index de la ligne : ");
                scanf("%d", &indexLigne);
                printf("Nombre de stations : %d\n", compterStationsRec(catalogue[indexLigne].tete));
                printf("Duree estimee : %d minutes\n", calculerDureeTrajetRec(catalogue[indexLigne].tete));
                break;

            case 8:
                sauvegarderFormatJSON("reseau.json", catalogue, nbLignesActuelles);
                libererMemoireReseau(catalogue, nbLignesActuelles);
                printf("Au revoir !\n");
                break;
        }
    } while (choix != 8);

    return 0;
}