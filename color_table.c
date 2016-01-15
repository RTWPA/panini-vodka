#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "color_table.h"

struct color
{

	int red;
	int green;
	int blue;

};

struct color_table
{

	color* colors;
	int nb_colors;
	boolean owner;

};

color_table create_color_table(image img)
{

	color_table new_table;
	int i, *pixel_color;

	new_table->owner = true;

	if(image_give_hauteur(img) == 1)
	{

		new_table->nb_colors = image_give_largeur(img) / 3;

		new_table->colors = malloc(sizeof(color) * new_table->nb_colors);

  		image_debut(img);

  		for(i = 0; i < new_table->nb_colors; i++)
  		{

  			pixel_color = image_lire_pixel(img);

  			new_table->colors[i]->red = pixel_color[0];
  			new_table->colors[i]->green = pixel_color[1];
  			new_table->colors[i]->blue = pixel_color[2];

  			if(image_pixel_suivant(img) != vrai)
  				break;

  		}

	}

	return new_table; 

}

boolean destroy_color_table(color_table){

	int i;

	color_table->nb_colors = i;

	if (color_table.owner == true)
		free(color_table->colors);
	

	return false
	
}

color_table color_table_duplicate(color_table,int offset,int length){

	assert(color_table != NULL);
	assert(offset < 0 || offset > length);
	assert(offset + length > length);
	
	color_table sou_table;
	int i;

	sous_table->owner = false;
	sous_table->nb_colors = length;
	sous_table-> = malloc(sizeof(color) * sous_table->nb_colors);

	for(i = 0; i < new_table->nb_colors; i++){

		sous_table->colors[i] = color_table->colors[i + offset];

	}

	return sous_table;

}

void color_table_get_color(color_table,int,color*){

	
}