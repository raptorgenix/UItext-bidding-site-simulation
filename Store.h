#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "Buyer.h"
#include "Seller.h"
#include "Product.h"
using namespace std;

class Store{
    private: 
        vector<Seller*> seller_list;
        vector<Buyer*> buyer_list; 
        static Store* instance;
        Store(string file_user, string file_product);
        vector<Product*> productOnsale;
    public:
        //Store();
        static Store *GetInstance(string file_user, string file_product);
        void addSeller(Seller*s){seller_list.push_back(s);}
        void addBuyer(Buyer*b){buyer_list.push_back(b);}
        Seller* getOneSeller(){return seller_list.back();}
        Buyer* getOneBuyer(){return buyer_list.back();}
        void displaySellerProduct(int choice, Seller* seller,string type, string quality);    //get product by types(view similar products) // view product being sale
        void displayBuyerProduct(int choice, Buyer* buyer);
        void closeBid(Product* p);
        Buyer* getB(string name);
        Seller* getS(string name);
        void addProduct(Product* p){productOnsale.push_back(p);}
        void displayOnSaleProduct();
        Product* getById(int id);
};
#endif