#include "../Product.h"

int main(){

    iphone * iph = ProductFactory::getIphone();
    cout<< "id: " << iph->getID() << endl;
    cout<< "init price: " << iph->getInitPrice() << endl;
    cout<< "final price: " << iph->getFinalPrice() << endl;
    cout<< "quality: " << iph->getQuality() << endl;
    cout<< "is sold: " << iph->getIsSold() << endl;
    cout<< "bid open: " << iph->getBidOpen() << endl;
    cout <<"type: " << iph->getTypeName() << endl;
    cout << "category: " << iph->getCategoryName() << endl;



    


}