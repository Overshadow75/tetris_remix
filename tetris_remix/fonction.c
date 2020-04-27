#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "head.h"

/*creer un tableau 2D vide*/
void menu()
{
    int choix;
    printf("TETRIS\n");
    printf("1 : commencer à jouer\n");
    printf("2 : afficher les règles du jeu\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    while (choix != 1 && choix != 2)
    {
        printf("veuillez choisir entre le choix 1 ou 2.\n veuillez entrer votre choix : ");
        scanf("%d", &choix);
    }
    if (choix == 2)
    {
        clear();
        regle();
    }
}
// commentaire
void continuer()
{
    int a = 0;
    printf("entrez 1 pour continuer : ");
    while (a != 1)
        scanf("%d", &a);
}


void regle()
{
    printf("REGLE DU TETRIS\nVous pourrez choisir entre trois formes de plateau : \n- Triangle\n- Cercle\n- Losange\n");
    printf("\nLe but du jeu est de ne pas dépasser le dessus du plateau,\n pour cela vous aurez à chaque tour, le choix entre 3 blocs à positionner.\n");
    printf("Grace à ces blocs, il vous faudra compléter des lignes pour pouvoir les détruire.\nDétruire un ligne vous fera gagner des points et de l'espace.\n\n");
    continuer();
    clear();
}


void clear()
{
    system("cls");
    system("clear");
}

int choixForme()
{
    int choix = 0;
    clear();
    printf("choisissez parmi les formes : \n");
    printf("1 : cercle\n2 : triangle\n3 : losange\nvotre choix : ");
    while (choix != 1 && choix != 2 && choix != 3)
    {
        scanf("%d", &choix);
    }
    return choix;

}

int** creer_tab2D_dyn(int L, int C) 
{
    L = L*2;
    int** tab = (int**) malloc(L * 2 * sizeof(int));
    int i, j;
    for (i=0; i<L; i++) 
	{
        tab[i] = (int*) malloc(C * sizeof(int));
    }
    if (tab == NULL) 
	{
        exit(EXIT_FAILURE);
    }
    return tab;
}





/*remplir un tableau 2D*/ 
void remplir_plateau(int** tab, int L, int C) 
{
    int i, j;
    for (i=0; i<L; i++) 
	{
        for (j=0; j<C; j++) 
		{
            tab[i][j] = 2;
        }
    }
}

void carre(int** tab, int L) 
{
    int i, j;
    for (i=0; i<L; i++) 
	{
        for (j=0; j<L; j++) 
		{
            tab[i][j] = 0;
        }
    }
}

void triangle(int** tab, int L, int C) 
{
    int i, j, k, l;
    for (i = 0; i < L; i++)
    {
        l = 1;
        k = 1;
        l = l - i;
        k = k + i;
        for ( j = l; j <= k; j++)
        {
            tab[i][(C/2)-j+1] = 0;
        }
        
    }
    
    
}

void losange(int** tab, int L, int C) 
{
    int i, j, k, l;
    L = L-1;
    for (i = 0; i < L/2; i++)
    {
        l = 1;
        k = 1;
        l = l - i;
        k = k + i;
        for ( j = l; j <= k; j++)
        {
            /*printf("%d %d\n", l, k);*/
            tab[i][(C/2)-j+1] = 0;
        }
        
    }
    for ( i = L/2; i <= L; i++)
    {
        l = 1;
        k = 1;
        l = l - L+i;
        k = k + L-i;
        for ( j = l; j <= k; j++)
        {
            /*printf("%d %d\n", l, k);*/
            tab[i][(C/2)-j+1] = 0;
        }
    }
    
}

void cercle(int** tab, int L, int C) 
{
    int i, j;
    for (i=0; i<L; i++) 
	{
        for (j=0; j<C; j++) 
		{
            if (i == 0 || i == 1 || i == 2)
            {
                if (j+i < 3 || j-i > C-4)
                {
                    tab[i][j] = 2;
                } else
                {
                    tab[i][j] = 0;
                }
                
            } 
            else if (i == L-1 || i == L-2 || i == L-3)
            {
                if (j+L-i < 4 || j+i > (C*2)-5)
                {
                    tab[i][j] = 2;
                } else
                {
                    tab[i][j] = 0;
                }
            }else
                tab[i][j] = 0;
        }
    }
}


/*afficher un tableau 2D*/
void afficher_plateau(int** tab, int L, int C) 
{
    int i, j;
    clear();
    char coordMin = 'a', coordMaj = 'A';
    printf("  ");
    for (i = 0; i < C; i++)
    {
        printf("%c", coordMin+i);
        printf(" ");
    }
    printf("\n");

    for (i=0; i<L; i++) 
	{   
        printf("%c ", coordMaj+i);
        for (j=0; j<C; j++) 
		{
            if (tab[i][j] == 0)
            {
                printf(".");
            } else if (tab[i][j] == 1)
            {
                printf("■");
            } else if (tab[i][j] == 2)
            {
                printf(" ");
            }
            printf(" ");
        }
        printf("\n");
    }
}


/*pour les blocs*/
int*** creer_tab_blocs()
{
    int *** blocs = (int***) malloc(57 * 5 * 5 * sizeof(int));
    int i, j;
    for ( i = 0; i < 57; i++)
    {
        blocs[i] = (int**) malloc(5 * 5 * sizeof(int));
        for ( j = 0; j < 5; j++)
        {
            blocs[i][j] = (int*) malloc(5 * sizeof(int));
        }
        
    }
    return blocs;
    
}

void remplir_blocs(int*** blocs)
{
    int i, j, k;
    for ( i = 0; i < 57; i++)
    {
        for ( j = 0; j < 5; j++)
        {
            for ( k = 0; k < 5; k++)
            {
                blocs[i][j][k] = 0;
            }
            
        }
        
    }
    
}


void afficher_blocs(int*** blocs) 
{
    int i, j, k;
    for ( i = 0; i < 57; i++)
    {
        printf("\n");
    
        for (j=0; j<5; j++) 
        {   

            for (k=0; k<5; k++) 
            {
                if (blocs[i][j][k] == 0)
                {
                    printf(".");
                } else if (blocs[i][j][k] == 1)
                {
                    printf("■");
                }
                printf(" ");
            }
            printf("\n");
        } 
    } 
}

void creer_bloc(int*** blocs)
{
    int i;
    for ( i = 0; i < 57; i++)
    {
        switch (i)
        {
        /*blocs commun*/
        case 0:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][4][1] = 1;
            
            break;

        case 1:
            blocs[i][4][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 2:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            break;
        
        case 3:
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 4:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][3][1] = 1;
            break;
        
        case 5:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][1] = 1;
            break;
        
        case 6:
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            break;
        
        case 7:
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 8:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            break;
        
        case 9:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            break;
        
        case 10:
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 11:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            break;
        
        case 12:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][2] = 1;
            break;
        
        case 13:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 14:
            blocs[i][3][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            break;
        
        case 15:
            blocs[i][4][1] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            break;
        
        case 16:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            break;
        
        case 17:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            break;
        
        case 18:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            break;
        
        case 19:
            blocs[i][4][0] = 1;
            break;
        
        /*blocs cercle*/
        case 20:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][0] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][2] = 1;
            blocs[i][1][3] = 1;
            break;
        
        case 21:
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][2] = 1;
            break;
        
        case 22:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][3] = 1;
            break;
        
        case 23:
            blocs[i][4][3] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][3] = 1;
            blocs[i][1][2] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][0] = 1;
            break;
        
        case 24:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            break;

        case 25:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][2] = 1;
            blocs[i][1][2] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][0] = 1;
            break;

        case 26:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][1][1] = 1;
            break;

        case 27:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            break;
        
        case 28:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            blocs[i][0][0] = 1;
            break;
        
        case 29:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][4][4] = 1;
            break;
        
        case 30:
            blocs[i][4][0] = 1;
            blocs[i][4][4] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][3][4] = 1;
            break;
        
        case 31:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            blocs[i][3][3] = 1;
            break;
        
        /*blocs losange*/
        case 32:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            blocs[i][1][2] = 1;
            blocs[i][1][3] = 1;
            break;
        
        case 33:
            blocs[i][4][3] = 1;
            blocs[i][3][3] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][1] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][0] = 1;
            break;
        
        case 34:
            blocs[i][4][2] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][2] = 1;
            blocs[i][1][2] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][0] = 1;
            blocs[i][1][3] = 1;
            break;
        
        case 35:
            blocs[i][4][0] = 1;
            blocs[i][4][3] = 1;
            blocs[i][1][0] = 1;
            blocs[i][1][3] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            break;
        
        case 36:
            blocs[i][4][2] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][3] = 1;
            blocs[i][2][4] = 1;
            break;
        
        case 37:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][0] = 1;
            blocs[i][1][1] = 1;
            blocs[i][1][2] = 1;
            blocs[i][1][3] = 1;
            break;
        
        case 38:
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][0] = 1;
            blocs[i][2][1] = 1;
            blocs[i][1][0] = 1;
            break;

        case 39:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][2] = 1;
            blocs[i][2][3] = 1;
            blocs[i][1][3] = 1;
            break;

        case 40:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            blocs[i][0][0] = 1;
            break;
        
        case 41:
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][4][3] = 1;
            blocs[i][2][3] = 1;
            break;
        
        case 42:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][4][3] = 1;
            blocs[i][4][4] = 1;
            break;
        
        case 43:
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][3] = 1;
            blocs[i][4][3] = 1;
            break;
        
        case 44:
            blocs[i][1][0] = 1;
            blocs[i][1][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][1] = 1;
            break;
        
        case 45:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            blocs[i][1][0] = 1;
            break;
        
        /*blocs triangle*/

        case 46:
            blocs[i][4][2] = 1;
            blocs[i][3][2] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            break;
        
        case 47:
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][0] = 1;
            break;
        
        case 48:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][2] = 1;
            break;
        
        case 49:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][1] = 1;
            blocs[i][2][2] = 1;
            break;
        
        case 50:
            blocs[i][4][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][2][2] = 1;
            break;
        
        case 51:
            blocs[i][2][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][4][2] = 1;
            break;
        
        case 52:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            blocs[i][2][0] = 1;
            break;
        
        case 53:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            blocs[i][4][2] = 1;
            break;
        
        case 54:
            blocs[i][4][0] = 1;
            blocs[i][3][0] = 1;
            break;

        case 55:
            blocs[i][4][1] = 1;
            blocs[i][3][0] = 1;
            blocs[i][3][1] = 1;
            blocs[i][3][2] = 1;
            blocs[i][2][1] = 1;
            break;
        
        case 56:
            blocs[i][4][0] = 1;
            blocs[i][4][1] = 1;
            break;

        default:
            break;
        }
            
    }
    
}

int* creer_tab1D_dyn(int size) 
{
    int* tab = (int*) malloc(size * sizeof(int));
    int i, j;

    if (tab == NULL)
	{
        exit(EXIT_FAILURE);
    }
    return tab;
}

void afficher_blocs_forme(int*** blocs, int* forme_tab, int size) 
{
    int i, j, k;

    for ( i = 0; i < size; i++)
    {
        printf("\n");

        for (j=0; j<5; j++)
        {

            for (k=0; k<5; k++)
            {
                if (blocs[forme_tab[i]][j][k] == 0)
                {
                    printf(".");
                } else if (blocs[forme_tab[i]][j][k] == 1)
                {
                    printf("■");
                }
                printf(" ");
                if (j == 2 && k == 4)
                    printf("  %d", i);
            }
            printf("\n");
        } 
    } 
}
void choix_pos(int* pos)
{
    
    char a;
    printf("veuillez entrer la coordonné horizontale de votre choix (entre A et Z) : ");
    scanf(" %c", &a);
    
    if (a > 90)
        a = a - 97;
    else
        a = a - 65;
   
    pos[0] = a;

    printf("veuillez entrer la coordonné verticale de votre choix (entre a et z) : ");
    scanf(" %c", &a);
  
    if (a > 90)
        a = a - 97;
    else
        a = a - 65;
  
    pos[1] = a;
    
    
}

int verif_validite(int coorI, int coorJ, int* forme_tab, int numBloc, int** tab, int*** blocs, int L, int C)
{
    int i, j, cI = 3;
    /*première étape de validation*/
    if (coorI >= L || coorJ >= C)
        return 0;
    
    for ( i = 4; i >= 0; i--)
    { cI++;
        for ( j = 0; j < 5; j++)
        {
            if (blocs[forme_tab[numBloc]][i][j] == 1)
            {
                /*troisième étape de validation*/
                if (coorI +4-cI < 0 || coorI+4-cI >= L || coorJ + j < 0 || coorJ + j >= C)
                    return 0;
                /*quatrième étape de validation*/
                if (tab[coorI + 4-cI][coorJ + j] == 1 || tab[coorI + 4-cI][coorJ + j] == 2)
                    return 0;
            }
        }  
    }
    return 1;
}

void decaler_ligne(int ligne, int** tab, int C) 
{
    int i, j, jStart, jEnd = 0, verif = 0;
    for (i = 0; i < C; i++) 
    {
        if (tab[ligne][i] == 0 && verif == 0) 
        {
            jStart = i;
            verif = 1;
        }
        if (verif == 1 && tab[ligne][i] == 2)
        {
            jEnd = i-1;
            break;
        }
    }
    if (jEnd == 0)
        jEnd = C-1;
        
    for (i = ligne - 1; i >= 0; i--) 
    {
        for (j = jStart; j <= jEnd; j++) 
        {
            if (tab[i][j] == 1) 
            {
                tab[i + 1][j] = 1;
                tab[i][j] = 0;
            }
        }
    }
}

int selection_num_bloc(){
    int numero_bloc;
    printf("Entrez le numéro du bloc : ");
    scanf("%d",&numero_bloc);

    return numero_bloc;
}

int select_blocs() {
    int option;

    printf("OPTIONS \n");
    printf(" 1: ensemble des blocs disponibles\n ou\n 2: 3 blocs sont choisis aléatoirement\n");
    printf("saisie : ");
    do{
        scanf("%d", &option);
    }while(option < 1 || option > 2);


    if(option == 1){
        printf("affichage des blocs disponibles");
        return 1;
    }
    else
        return 2;
}

void affichage_option2(int*** blocs, int* forme_tab, int nb_blocs) {
    int i, j, k;

        srand(time(NULL));
        int alea1 = ((rand() % nb_blocs)+1);
        int alea2 = ((rand() % nb_blocs)+1);
        int alea3 = ((rand() % nb_blocs)+1);

        printf("\n");
        printf("bloc : %d",alea2);
        printf("\n");
        for (j=0; j<5; j++)
        {

            for (k=0; k<5; k++)
            {
                if (blocs[forme_tab[alea1]][j][k] == 0)
                {
                    printf(".");
                } else if (blocs[forme_tab[alea1]][j][k] == 1)
                {
                    printf("■");
                }
                printf(" ");
            }
            printf("\n");
        }
            printf("\n");
            printf("bloc : %d",alea2);
            printf("\n");
            for (j=0; j<5; j++)
            {

                for (k=0; k<5; k++)
                {
                    if (blocs[forme_tab[alea2]][j][k] == 0)
                    {
                        printf(".");
                    } else if (blocs[forme_tab[alea2]][j][k] == 1)
                    {
                        printf("■");
                    }
                    printf(" ");
                }
                printf("\n");
            }
            
            printf("\n");
            printf("bloc : %d",alea3);
            printf("\n");
            for (j=0; j<5; j++)
            {

                for (k=0; k<5; k++)
                {
                    if (blocs[forme_tab[alea3]][j][k] == 0)
                    {
                        printf(".");
                    } else if (blocs[forme_tab[alea3]][j][k] == 1)
                    {
                        printf("■");
                    }
                    printf(" ");
                }
                printf("\n");
            }

    printf("\n");
}

void placer_blocs(int** tab, int*** blocs, int coorI, int coorJ, int num_bloc)
{
    int i=0;
    int j;
    int taille_bloc = 5;
    while(i<taille_bloc)
    {
        j=0;
        while(j<taille_bloc)
        {
            tab[coorI-i][coorJ+j] = tab[coorI-i][coorJ+j]+ blocs[num_bloc][taille_bloc-i-1][j];
            j++;
        }
        i++;
    }
}

int etat_ligne(int **tab, int taille, int ligne){
    int j;
    int ligne_pleine = 1, ligne_nonpleine = 0;

    for(j=0; j<taille; j++){
        if(tab[ligne][j] == 0){
            return ligne_nonpleine;
        }
    }
    return ligne_pleine;

}

int etat_colonne(int **tab, int taille, int colonne){
    int i;
    int colonne_pleine = 1, colonne_nonpleine = 0;

    for(i=0; i<taille; i++){
        if(tab[i][colonne] == 0){
            return colonne_nonpleine;
        }
    }
    return colonne_pleine;

}

int calcul_score(int comptL, int comptC){
    if(comptL == 1)
        return 100;
    else if(comptC == 1)
        return 100;
    return 0;
}

void annuler_ligne(int**tab, int taille, int ligne, int etatL){
    int j;
    if(etatL == 1){
        for(j=0; j<taille; j++){
            if(tab[ligne][j] == 1){
                tab[ligne][j] = 0;
            }
        }
    }
}

void annuler_colonne(int**tab, int taille, int colonne, int etatC){
    int i;
    if(etatC == 1){
        for(i=0; i<taille; i++){
            if(tab[i][colonne] == 1){
                tab[i][colonne] = 0;
            }
        }
    }
}