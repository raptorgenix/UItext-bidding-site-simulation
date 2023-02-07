#include "../Store.h"

int main(){

    
    Store * store = Store::GetInstance();

    textbook* b = ProductFactory::getTextbook();
    b->setIsSold(true);

    iphone* c = ProductFactory::getIphone();
    apartment* d = ProductFactory::getApartment();

    // Seller* s1 = new Seller();
    // s1->setUsername("name1");
    // Seller* s2 = new Seller();
    // s2->setUsername("name2");
    // Seller* s3 = new Seller();
    // s3->setUsername("name3");

    // s1->addProductForSale(b);
    // s1->addProductForSale(c);
    // s1->addProductForSale(d);

    // s2->addProductForSale(b);
    // s2->addProductForSale(c);
    // s2->addProductForSale(d);

    // s3->addProductForSale(b);
    // s3->addProductForSale(c);
    // s3->addProductForSale(d);

    // store->addSeller(s1);
    // store->addSeller(s2);
    // store->addSeller(s3);
    // store->displaySellerProduct(1,s1,"textbook");
    // store->displaySellerProduct(1,s2,"textbook");

    // store->displaySellerProduct(2,s1,"textbook");

    Buyer* b1 = new Buyer();
    b1->setUsername("b1");
    Buyer* b2 = new Buyer();
    b2->setUsername("b2");
    Buyer* b3 = new Buyer();
    b3->setUsername("b3");

    b1->addBidToProduct(b,10);
    b1->addBidToProduct(c,11);
    b1->addBidToProduct(d,13);
    b2->addBidToProduct(b,15);
    b2->setBalance(0.0);
    store->addBuyer(b1);
    store->addBuyer(b2);

    store->displayBuyerProduct(2,b1);
     store->displayBuyerProduct(2,b2);
    store->closeBid(b);
    store->displayBuyerProduct(2,b1);
    store->displayBuyerProduct(2,b2);

}