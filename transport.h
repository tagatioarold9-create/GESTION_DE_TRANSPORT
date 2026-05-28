#ifndef TRANSPORT_H
#define TRANSPORT_H

// ============================================================================
// 1. STRUCTURES DE DONNÉES (Livrable Binôme 1)
// ============================================================================

// Structure pour une Station (Nœud de la liste chaînée) [cite: 35, 58]
typedef struct Station {
    char nom[50];               // Nom de la station (ex: "Gare Centrale") [cite: 17]
    struct Station* suivant;    // Pointeur vers la station suivante 
} Station;

// Structure pour une Ligne (Point d'entrée de la liste) [cite: 35, 58]
typedef struct Ligne {
    char nomLigne[30];          // Nom de la ligne (ex: "Ligne A") [cite: 14]
    Station* tete;              // Pointeur vers la première station 
} Ligne;


// ============================================================================
// 2. PROTOTYPES DES FONCTIONS PAR BINÔME
// ============================================================================

// 🛠️ BINÔME 1 : Les Architectes (Structures & Initialisation) [cite: 54]
// Fichiers : transport.h / main.c / transport.c [cite: 57]
void initialiserCatalogue(Ligne catalogue[], int nombreMaxLignes); // [cite: 60]
int afficherMenu(); // [cite: 59]


// 🔄 BINÔME 2 : Les Éditeurs (Modifications du Réseau) 
// Fichiers : edition.h / edition.c [cite: 64]
void creerNouvelleLigne(Ligne catalogue[], int* nbLignesActuelles, int maxLignes); // [cite: 65]
void insererEnTete(Ligne* ligne, const char* nomStation); // [cite: 66]
void insererEnFin(Ligne* ligne, const char* nomStation); // [cite: 66]
void insererAIndex(Ligne* ligne, const char* nomStation, int position); // [cite: 66]
void supprimerStation(Ligne* ligne, const char* nomStation); // [cite: 67]


// 📊 BINÔME 3 : Les Analystes (Statistiques Récursives) [cite: 68]
// Fichiers : stats.h / stats.c [cite: 71]
int calculerDureeTrajetRec(Station* station); // [cite: 18, 72]
int compterStationsRec(Station* station); // [cite: 18, 73]


// 🖥️ BINÔME 4 : Les Visuels (Affichage Récursif & Recherche) [cite: 75]
// Fichiers : affichage.h / affichage.c [cite: 78]
void afficherReseauGlobal(Ligne catalogue[], int nbLignes); // [cite: 21, 81]
void afficherItineraireAllerRec(Station* station); // [cite: 22, 79]
void afficherItineraireRetourRec(Station* station); // [cite: 22, 79]
Station* rechercherStationGlobal(Ligne catalogue[], int nbLignes, const char* nomCherche, Ligne** ligneTrouvee); // [cite: 17, 80]


// 💾 BINÔME 5 : Les Gardiens (Moteur de Sauvegarde JSON) [cite: 82]
// Fichiers : persistence.h / persistence.c [cite: 85]
void sauvegarderFormatJSON(const char* nomFichier, Ligne catalogue[], int nbLignes); // [cite: 24, 86]
void chargerFormatJSON(const char* nomFichier, Ligne catalogue[], int* nbLignes); // [cite: 26, 87]
void libererMemoireReseau(Ligne catalogue[], int nbLignes); // 

#endif 