#include "Product.h"

 Product::Product(){ //product template instantiator
    product_id = 0;
    init_price = 0;
    final_price = 0;
    quality = "good";
    is_sold = true;
    bid_open = false;
    category_name = "category_name";
    type_name = "type_name";
    buyer = "buyer";
    seller = "seller";
 }


  //factory implementation-- this is where our product types are generated from our ProductFactory class
 iphone * ProductFactory :: getIphone(){
   return new iphone();
 }

 textbook * ProductFactory:: getTextbook(){
   return new textbook();
 }

 apartment * ProductFactory :: getApartment(){
   return  new apartment();
 }
  hat * ProductFactory :: getHat(){
   return new hat();
  }

  dell * ProductFactory :: getDell(){
   return new dell();
  }

bool Product::operator==(const Product& p1){ //override == operator for products to check if they are exact same instance of the product
    return(p1.product_id == this->product_id &&
           p1.quality == this->quality &&
           p1.init_price== this-> init_price&&
           p1.category_name == this->category_name &&
           p1.buyer == this->buyer
    );
}
// for the case highest bids buyer doesn't have enough money
void Product::removeBids(string name){
    for (auto it = bid_list.begin(); it != bid_list.end(); ++it){
      if(it->first == name) it->second = 0;
    }
}

