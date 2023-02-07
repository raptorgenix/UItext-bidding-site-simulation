#include <iostream>
#include <string>
#include <vector>
#include <map>
#include"Product.h"
#include"User.h"


class Seller : public User{

    public:
        // create product base on type and add to map
        void addProductForSale(Product* p); 
        vector<Product*>getProduct(){return product_list;}
        bool addProduct(Product* p);
        string getID(){return "Seller";}
        Product* getById(int id);

    private:
        //seller have a list he sold
       vector<Product*> product_list;
};