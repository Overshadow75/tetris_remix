#ifndef __LIST__H__
#define __LIST__H__

/* structures*/




/* Prototypes de fonctions */
void menu();
void continuer();
void regle();
void clear();
int choixForme();
int** creer_tab2D_dyn(int L, int C);
void remplir_plateau(int** tab, int L, int C);
void carre(int** tab, int L);
void triangle(int** tab, int L, int C);
void losange(int** tab, int L, int C);
void cercle(int** tab, int L, int C);
void afficher_plateau(int** tab, int L, int C);
int verif_validite(int coorI, int coorJ, int* forme_tab, int numBloc, int** tab, int*** blocs, int L, int C);
void decaler_ligne(int ligne, int** tab, int C);

/*toutes les formes de bloc
il y a : 20 blocs commun, 12 blocs cercle, 14 blocs losange, 11 blocs triangle, total de 57 blocs.
il y a : 1 bloc 1x1, 7 blocs 2x2, 21 blocs 3x3, 22 blocs 4x4, 6 blocs 5x5, total de 57 blocs. */

int*** creer_tab_blocs();
void remplir_blocs(int*** blocs);
void afficher_blocs(int*** blocs);
void creer_bloc(int*** blocs);
void afficher_blocs_forme(int*** blocs, int* forme_tab, int size);
int* creer_tab1D_dyn(int size);

int select_blocs();
int selection_blocs_joueur();
void affichage_option2(int*** blocs, int* forme_tab, int nb_blocs);
void placer_blocs(int** tab, int*** blocs, int coorI, int coorJ, int num_bloc);
int etat_ligne(int **tab, int taille, int ligne);
int etat_colonne(int **tab, int taille, int colonne);
void annuler_ligne(int**tab, int taille, int ligne, int etatL);
void annuler_colonne(int**tab, int taille, int ligne, int etatC);
int calcul_score(int comptL, int comptC);
#endif
