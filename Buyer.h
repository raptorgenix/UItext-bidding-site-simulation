
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include"Product.h"
#include"User.h"

class Buyer : public User{
    public:
        //return true if user have enough money put bids
        bool addBidToProduct(Product* p, double bids);
        bool addProduct(Product* p);
        vector<Product*>getOwnProduct(){return product_list;}
        vector<Product*>getBidProduct(){return bids_list;}
        void removeUnbids();
        string getID(){return "Buyer";}
    private:
        // Buyer has a list of product he brought or add bid on it
        vector<Product*> product_list;
        vector<Product*> bids_list;
  
};