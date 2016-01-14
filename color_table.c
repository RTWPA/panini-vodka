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