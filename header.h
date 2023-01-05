// Structures
struct s_partisan
/*
Structure qui représente un personnage placé et orienté
dans la cour du roi.
*/
{
    int orientation; // Orientation  possible : 1 : Clan rouge ; 2 : vert
    int personnage;
    /*
    Tuiles possibles :
    1 : Citoyen
    2 : Roi
    3 : Reine
    4 : Princesse
    5 : Ministre
    6 : Général
    7 : Château
    */
};

struct s_joueur
/*
Structure qui représente un joueur
*/
{
    int orientation;
    // Orientation  du joueur : 1 : Clan rouge ; 2 : Clan vert
    int cartes[7];
    /*
    Tableau de 7 cases qui représente les cartes disponibles pour le joueur
    Chaque case (0 à 6) correspond à un personnage (1 à 7). 1 = Dispo. 0 = Personnage plus dispo
    */
};

// Fonctions dans le fichier affichage
void restant(struct s_joueur); // Fonction qui affiche au joueur ses cartes restantes
void restant_demande(struct s_joueur);
void aff_plateau(struct s_partisan *); // Cette fonction affiche le tableau du jeu
void affichage_actions_possibles(int*, int); // Affichage des zones d'applications

// Fichier jeu - 1 Général
void place_carte(struct s_partisan *, struct s_joueur *, int, int); // Fonction qui place une carte sur le plateau et l'enlève de la liste
int convertir(char *);                                              // Convertir des coordonnées passées en paramètre en un index pour le tableau du plateau
int choix_emplacement(struct s_partisan *);                         // Cette fonction demande l'index et le renvoie
int choix_personnage(struct s_joueur);                              // Choix du personnage
int est_plein(struct s_partisan *);
int joueur_gagnant(struct s_partisan *);

// Fichier jeu - 2 Pouvoir des cartes
void action(struct s_partisan *, struct s_joueur, int, int);
int choix_roi_ministre_general(int *);
int choix_reine(int *);
void action_detruire(struct s_partisan *, int);
void action_pivoter(struct s_partisan *, int);