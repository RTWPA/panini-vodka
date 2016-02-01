#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "includes/image.h"
#include "includes/color_table.h"

int main(int argc, char *argv[])

{

	int bestID, bestValue, currentValue = 0, i;
	int* pixel_color;
	int new_pixel[3];
	image img = FAIRE_image(), table = FAIRE_image();
	color_table table_convert;
	color table_current_color;

	if(argc == 0 || argc == 1)
	{
		
		printf("Vous devez entrer le chemin d'une image en premier et le chemin d'une table de couleurs en second.\n");
		return EXIT_FAILURE;
		
	}
	
	if(image_charger(img, argv[1]) < 0)
		return EXIT_FAILURE;
		
	if(image_charger(table, argv[2]) < 0)
		return EXIT_FAILURE;

	table_convert = create_color_table(table);
	table_current_color = malloc(sizeof(color));
	
	image_debut(img);
	
	do
	{
		
		pixel_color = image_lire_pixel(img);
		
		color_table_get_color(table_convert, 0, table_current_color);
		
		bestID = 0;
		bestValue = abs((pixel_color[0] - table_current_color->red));
		bestValue += abs((pixel_color[1] - table_current_color->green));
		bestValue += abs((pixel_color[2] - table_current_color->blue));
		
		for(i = 1; i < color_table_get_nb_color(table_convert); i++)
		{
			
			color_table_get_color(table_convert, i, table_current_color);
			
			currentValue = abs((pixel_color[0] - table_current_color->red));
			currentValue += abs((pixel_color[1] - table_current_color->green));
			currentValue += abs((pixel_color[2] - table_current_color->blue));
			
			if(currentValue < bestValue)
			{
				
				bestValue = currentValue;
				bestID = i;
				
			}
			
		}
		
		color_table_get_color(table_convert, bestID, table_current_color);
		
		new_pixel[0] = table_current_color->red;
		new_pixel[1] = table_current_color->green;
		new_pixel[2] = table_current_color->blue;
		
		image_ecrire_pixel(img, new_pixel);
		
	}while(image_pixel_suivant(img) == vrai);
	
	image_sauvegarder(img, "test.ppm");

    return EXIT_SUCCESS;

}
