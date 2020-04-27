#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "fonction.c"


int main()
{
	int size = 0, L, C, v = 0, i, j, etatL, etatC, choix, indice_choix, num_bloc, game = 1, cEssai, validite, coorI, coorJ, scoreL, scoreC, score;
	int** tab;


	int losange_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};
	int cercle_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
	int triangle_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56};
	int forme_tab[50];
	int pos[2];
	
	/*cercle_tab = creer_tab1D_dyn(32);
	triangle_tab = creer_tab1D_dyn(31);
	losange_tab = creer_tab1D_dyn(34);*/

	int*** blocs = creer_tab_blocs();
	remplir_blocs(blocs);
	creer_bloc(blocs);

	menu();

	int forme = choixForme();

	printf("entrez la taille du plateau (min 21) : ");
	scanf("%d", &size);
	while (size < 21)
	{
		printf("entrez la taille du plateau (minimum 21) : ");
		scanf("%d", &size);
	}

	if (forme == 1)
	{
		L = size;
		C = size;
	}
	if (forme == 2)
	{
		if (size %2 == 0)
		{
			size++;
		}
		L = (size/2)+1;
		C = size;
	}
	if (forme == 3)
	{
		if (size%2 == 0)
			size++;
		L = size;
		C = size;
	}
	


    tab = creer_tab2D_dyn(L, C);
	remplir_plateau(tab, L, C);
	


	if (forme == 1)
	{
	    cercle(tab, L, C);
		int forme_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
		//int etatL = etat_ligne(tab, size, coorI, coorJ);
		//printf("%d", etatL);
    }
	if (forme == 2)
	{
		triangle(tab, L, C);
		int forme_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56};
	}
	if (forme == 3)
	{
		losange(tab, L, C);
		int forme_tab[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};
	}

	
	while (game == 1)
	{
		cEssai = 0;
		validite = 0;
		afficher_plateau(tab, L, C);
		choix = select_blocs();
		if(choix == 1){
			afficher_blocs_forme(blocs, forme_tab, 32);
		}
		if(choix == 2){
			affichage_option2(blocs, forme_tab, 32);
		}
		num_bloc = selection_num_bloc();
		while (validite == 0 && cEssai < 3)
		{
			afficher_plateau(tab, L, C);
			choix_pos(pos);
			coorI = pos[0];
			printf("coorI = %d\n", coorI);
			coorJ = pos[1];
			printf("coorJ = %d\n", coorJ);
			validite = verif_validite(coorI, coorJ, forme_tab, num_bloc, tab, blocs, L, C);
			printf("%d", validite);
			if (validite == 0)
				cEssai++;
			if (cEssai == 3)
				game = 0;
		}
		afficher_plateau(tab, L, C);
		if (validite == 1 && game == 1)
			placer_blocs(tab, blocs, coorI, coorJ, num_bloc);
		afficher_plateau(tab, L, C);
		continuer();
		for (i = 0; i < size; i++)
		{
			etatL = etat_ligne(tab, size, i);
			if (etatL == 1)
			{
				annuler_ligne(tab, size, i, etatL);
				decaler_ligne(i, tab, C);
				scoreL = scoreL + calcul_score(1,0);
			}

		}
        for (j = 0; j < size; j++)
        {
            etatC = etat_colonne(tab, size, j);
            if (etatC == 1)
			{
                annuler_colonne(tab, size, i, etatC);
                scoreC = scoreC + calcul_score(0,1);
			}
        }
		validite = 0;
	}

	score = scoreL + scoreC;
	printf("jeu terminé");
	printf("Score : %d", score);

	free(tab);
	free(blocs);

    return 0;
}