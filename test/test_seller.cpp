#include "../Seller.h"

int main(){

    // textbook* b = ProductFactory::getTextbook();
    // b->getIsSold(true);
    // iphone* c = ProductFactory::getIphone();
    // apartment* d = ProductFactory::getApartment();
    User * u = new User();
    Seller* s = dynamic_cast<Seller*> (u);
    if(s == NULL) cout << " cmn" << endl;
    //cout <<  s->getID();
    


}