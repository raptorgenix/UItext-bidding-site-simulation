#include "Buyer.h"

bool Buyer::addBidToProduct(Product* p, double bids){

    if(this->getBalance() >= bids && p->getBidOpen() && bids > p->getInitPrice()){//checks if adequate funds are present for a bid and whether that item currently is open to bid on
        pair<string, double> b(this->getUsername(), bids);//generates bid data to give to bid vector for product
        p->addBids(b);//adds additional bid to vector
        bids_list.push_back(p);
        return true;
    }
    else return false;
}
bool Buyer::addProduct(Product* p){
    if(p->getBuyer() == this->getUsername()){//if user is buyer and has successfully purchased an item, add it to their product list vector
        product_list.push_back(p);
        return true;
    }
    return false;
}
// remove product in the bids list if not win the bids
void Buyer::removeUnbids(){
    for(unsigned int i = 0; i < bids_list.size(); i++){
        if(bids_list[i]->getBidOpen() == false){
            // add to product owned list if current buyer is the winner.
            if(bids_list[i]->getBuyer() == this->getUsername()){
                product_list.push_back(bids_list[i]);
            } else{
                pair <string, string> p("sorry, you did not win the product!", bids_list[i]->getSeller());
                this->addMail(p);
            }
            bids_list.erase(bids_list.begin()+i);
        }
    }
}