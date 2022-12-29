// Structure
struct s_partisan
{
    int orientation;
    // Orientation  possible : 1 : Clan du haut (rouge) ; 2 : Clan du bas (vert)
    int tuile;
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
{
    int orientation;
    // Orientation  du joueur : 1 : Clan du haut (rouge) ; 2 : Clan du bas (vert)
    int cartes[7];
    /*
    Liste de 7 cases qui représente les cartes disponible pour le joueur
    Chaque case (0 à 6) correspond à un personnage (1 à 7). 1 = Dispo. 0 = Personnage plus dispo
    */
};

// Fonctions dans le fichier affichage
void grille(int *, int *);
void gril(struct s_partisan);
void restant(struct s_joueur);                   // Fonction qui affiche au joueur ces cartes restantes
void restant_demande(struct s_joueur);
void aff_plateau(struct s_partisan *); // Cette fonction affiche le tableau du jeu

// Fichier jeu - 1 Général
void debut(struct s_partisan *, struct s_joueur, struct s_joueur);               // Fonction du début du jeu
void place_carte(struct s_partisan *, struct s_joueur *, int, int); // Fonction qui place une carte sur le plateau et l'enlève de la liste
int convertir(char *);                                       // Convertir des coordonnées passées en paramètre en un index pour le tableau du plateau
int emplacement(struct s_partisan *);                        // Cette fonction demande l'index et le renvoie
int choix_personnage(struct s_joueur);                                 // Choix du personnage

// Fichier jeu - 2 Pouvoir des cartes
void action_roi(struct s_partisan *, int);