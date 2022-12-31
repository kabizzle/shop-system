#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Writes the products in the shop into the specified binary file. 
 * 
 * \param filename The name of the file.
 * \param shop An array of products, of which last product has an empty name.
 * 
 * \returns 0 if products can be written to the file.
 * \returns 1 if an error occurs.
 */
int write_binary(const char* filename, const Product* shop) {
	FILE *file = fopen(filename, "wb");

	if (file == NULL)
		return 1;

	while (shop->name[0]){
		if (fwrite(shop, sizeof(Product), 1, file) != 1){
			fclose(file);
			return 1;
		}
		shop++;
	}
	fclose(file);
	return 0;
	}

/**
 * \brief Reads the shop products from the specified binary file.
 * 
 * \param filename The name of the file
 * 
 * \return  Returns a dynamically allocated array of products read from the 
 *          file in the read order. NULL if an error occurs. 
 */
Product* read_binary(const char* filename) {
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
		return NULL;

	Product *product_array;

	int i = 0;
	// int size = 0;
	product_array  = calloc(sizeof(Product), 20);
	while (!feof(file)) {
		// size = i + 1;
			// product_array = realloc(product_array, size*sizeof(Product));

		fread(&product_array[i], sizeof(Product), 1, file);
		i++;
	}
	// product_array[i].name[0] == '\0';
	fclose(file);
	return product_array;
}

/**
 * \brief  Writes the shop products into a text file.
 * 
 * \details The file writes each product as follows.
 * 
 *          <product-name> <price> <in-stock>
 * 
 *       In other words, the structure fields are separated with a space, and the array 
 *       elements are separated by a newline. Because the data items are separated by a 
 *       space, the product name should not have spaces in it.
 * 
 *       The last array element (with the name of null character) should not be 
 *       written into the file.
 * 
 * \param filename The name of the file.
 * \param shop An array of products, of which last product has an empty name.
 * 
 * \returns 0 if products can be written to the file.
 * \returns 1 if an error occurs.
 */
int write_plaintext(const char* filename, const Product* shop) {
	FILE *file = fopen(filename, "w");
	if (file == NULL)
		return 1;
	
	int i = 0;
	Product current = shop[i];
	while (current.name[0]){
		int valid = fprintf(file, "%s %f %d\n", current.name, current.price, current.in_stock);
		
		if (valid < 0){
			fclose(file);
			return 1;
		}
		i++;
		current = shop[i];
	}

	fclose(file);
	return 0;
}

/**
 * \brief Reads the shop products from the specified text file.
 * 
 * \param filename The name of the file
 * 
 * \return  Returns a dynamically allocated array of products read from the 
 *          file in the read order. NULL if an error occurs. 
 *
 * \note You can parse each line using sscanf function.
 */
Product* read_plaintext(const char* filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return NULL;
	
	Product* product_array = calloc(sizeof(Product), 20);

	int i = 0;
	// int size = 0;
	// char line[1000];
	int valid = 0;

	valid = fscanf(file, "%s %f %d\n", product_array[i].name, &product_array[i].price, &product_array[i].in_stock);
	while (valid == 3) {
		i++;
		valid = fscanf(file, "%s %f %d\n", product_array[i].name, &product_array[i].price, &product_array[i].in_stock);
	}	
	fclose(file);
	return product_array;
}
