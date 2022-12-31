#ifndef AALTO_SHOP_H
#define AALTO_SHOP_H

/**
 * \brief A product of the shop
 */
typedef struct {
	char name[31]; //!< The name of the product
	float price;   //!< The price
	int in_stock;  //!< The number of items in the stock
} Product;

int write_binary(const char* filename, const Product* shop);

Product* read_binary(const char* filename);

int write_plaintext(const char* filename, const Product* shop);

Product* read_plaintext(const char* filename);

#endif /* AALTO_SHOP_H */
