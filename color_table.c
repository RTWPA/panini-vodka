#include <stdio.h>
#include <stdlib.h>

#include "includes/image.h"
#include "includes/color_table.h"


/**
*@brief Structure définissant une table de couleurs
* *(L'attribut couleur est défini dans le .h)
*/

struct color_table
{

	color* colors;
	int nb_colors;
	boolean owner;

};

/**
*@brief Permet de créer une table de couleurs a partir d'une image 
*@param Image a partir de laquelle on veut créer une table.
*/

color_table create_color_table(image img)
{
	
	color_table new_table = malloc(sizeof(color_table));
	int i, *pixel_color;
	
	/* Conditions d'erreur qui permetent de quitter la focntion si necessaire*/
	assert(img != NULL);
	assert(image_give_hauteur(img) == 1);

	new_table->owner = true;


	new_table->nb_colors = image_give_largeur(img);

	new_table->colors = malloc(sizeof(color) * new_table->nb_colors);

  	image_debut(img);

	/* On créer la nouvelle table pixel par pixel*/
	
  	for(i = 0; i < new_table->nb_colors; i++)
  	{

		pixel_color = image_lire_pixel(img);
		
		new_table->colors[i] = malloc(sizeof(color));

		new_table->colors[i]->red = pixel_color[0];
		new_table->colors[i]->green = pixel_color[1];
		new_table->colors[i]->blue = pixel_color[2];

		image_pixel_suivant(img);

	}

	return new_table; 

}

/**
*@brief Permet de supprimer une table de couleur existante
*@param Table à supprimer.
*/

boolean destroy_color_table(color_table table)
{
	/* Condition d'erreur qui permetent de quitter la focntion si necessaire*/
	assert(table != NULL);

	/* On ne détruit la couleur que si le owner est set sur true*/
	
	if (table->owner == true)
	{
		free(table->colors);
		free(table);
		return true;
	}

	return false;
	
}

/**
*@brief Permet de copier une table existante en y incluant des modifications
*@param Table à dupliquer
*@param Point de départ de la nouvelle table
* 
*/

color_table color_table_duplicate(color_table table,int offset,int length)
{
	
	/* On alloue autant de mémoire que la table d'origine*/

	color_table new_table = malloc(sizeof(color_table));
	int i;

	/* Conditions d'erreur qui permetent de quitter la focntion si necessaire*/
	assert(table != NULL);
	assert(offset >= 0 && offset < length);
	assert(offset + length < table->nb_colors);

	new_table->owner = false;
	new_table->nb_colors = length;
	new_table->colors = malloc(sizeof(color) * new_table->nb_colors);

	/*on ajoute les couleurs pixel par pixel*/
	for(i = 0; i < new_table->nb_colors; i++){

		new_table->colors[i] = malloc(sizeof(color_table));
		new_table->colors[i] = table->colors[i + offset];

	}

	return new_table;

}

/**
*@brief Permet de récuperer les couleurs présentes dans une structure couleur
* d'une table et de le mettre dans une structure differente
*@param ID de la couleur à récuperer.
*@param Nouvelle table.
* 
*/

void color_table_get_color(color_table table, int color_id, color color_struc)
{

	/* Conditions d'erreur qui permetent de quitter la focntion si necessaire*/
	assert(table != NULL);
	assert(color_struc != NULL);
	assert(color_id >= 0 && color_id < table->nb_colors);
	
	/* On récupère chaque composante pour la couleur donnée*/
	
	color_struc->red = table->colors[color_id]->red;	
	color_struc->green = table->colors[color_id]->green;	
	color_struc->blue = table->colors[color_id]->blue;
	
}

/**
*@brief Permet de comparaison de qsort (configuration)
* 
*/

int compare(void const *a, void const *b, void *arg)
{

	/*Fichier de configuration de qsort*/
	
	color p = *(const color *)a, q = *(const color *)b;
	int a_comp, b_comp;
	
	switch (*(axis *) arg)
	{
		case red:
		
			a_comp = p->red;
			b_comp = q->red;
	
			break;

		case green:

			a_comp = p->green;
			b_comp = q->green;

			break;

		case blue:

			a_comp = p->blue;
			b_comp = q->blue;

			break;	
	}
	
	if (a_comp == b_comp)
		return 0;

	if (a_comp < b_comp)
		return -1;

	return 1;

}

/**
*@brief Fonction de récupération du nb_colors dans une structure color-table 
*@param table la table dont on veux récuperer nb_color
*/

int color_table_get_nb_color(color_table table)
{

	/*geter de nb_color*/
	return table->nb_colors;

}

/**
*@brief Fonction de tri d'une table solon un axe prédéfini
*@param table à trier
*@param Axe à définir.
*/

void color_table_sort(color_table table, axis component)
{
	
	/* Condition d'erreur qui permetent de quitter la focntion si necessaire*/
	assert(table != NULL);
	
	qsort_r(table->colors, color_table_get_nb_color(table), sizeof(color), compare, &component);
	
}
