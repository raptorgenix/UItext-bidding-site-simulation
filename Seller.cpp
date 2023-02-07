#include"Seller.h"


void Seller:: addProductForSale(Product* p){
    product_list.push_back(p); //append list of products this user has for sale with added parameter
    p->setSeller(this->getUsername());//apply username of seller to product being put on sale
}
bool Seller::addProduct(Product* p){
    if(p->getSeller() == this->getUsername()){ //add product to the inventory of this seller (generally if not sold)
        product_list.push_back(p);
        return true;
    }
    return false;
}

Product* Seller::getById(int id){
    for(unsigned int i = 0; i < product_list.size(); i++){//return a product from the inventory of this seller based on the product's ID
        if(product_list[i]->getID() == id) return product_list[i];
    }
    return NULL;
}