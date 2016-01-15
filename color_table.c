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
  				return new_table; 

  		}
	}

	return new_table; 

}

boolean destroy_color_table(color_table table)
{

	if (table->owner == true)
	{
		free(table);
		return true;
	}

	return false;
	
}

color_table color_table_duplicate(color_table table,int offset,int length)
{
		
	color_table new_table;
	int i;

	assert(table != NULL);
	assert(offset >= 0 && offset < length);
	assert(offset + length < table->nb_colors);

	new_table->owner = false;
	new_table->nb_colors = length;
	new_table->colors = malloc(sizeof(color) * new_table->nb_colors);

	for(i = 0; i < new_table->nb_colors; i++){

		new_table->colors[i] = table->colors[i + offset];

	}

	return new_table;

}

void color_table_get_color(color_table table, int color_id, color color_struc)
{

	assert(table != NULL);
	assert(color_id >= 0 && color_id < table->nb_colors);
	
	color_struc->red = table->colors[color_id]->red;	
	color_struc->green = table->colors[color_id]->green;	
	color_struc->blue = table->colors[color_id]->blue;
	
}
