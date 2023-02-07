#include "Store.h"

// init
Store * Store::instance = NULL;
// constructor
Store::Store(string file_user, string file_product){
    // initialize user file first
    ifstream file;
    file.open(file_user);
    vector<User*> users;
    string line;
    if(file.is_open()){
        // read each line
        while(getline(file,line)){
            vector<string> tokens;
            istringstream iss(line);
            string token;
            // split by ,
            while(std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }
            User* u = new User();
            u->setPhone(tokens[0]);
            u->setUsername(tokens[1]);
            u->setAddress(tokens[2]);
            u->setBalance(stod(tokens[3]));
            users.push_back(u);
        }
    } else{
        cout << "fail to open user file" << endl;
    }
    file.close();
    // init products
    file.open(file_product);
    if(file.is_open()){
        // read by line
        while(getline(file,line)){
            vector<string> tokens;
            istringstream iss(line);
            string token;
            // split by ,
            while(std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }
            // init product
            Product* p;
            if(tokens[3] == "iphone") p = ProductFactory::getIphone();
            else if(tokens[3] == "textbook") p = ProductFactory::getTextbook();
            else if(tokens[3] == "apartment") p = ProductFactory::getApartment();
            else if(tokens[3] == "hat") p = ProductFactory::getHat();
            else  p = ProductFactory::getDell();
            // update each product info
            p->setID(stoi(tokens[0]));
            p->setFinalPrice(std::stod(tokens[1]));
            p->setquality(tokens[4]);
            p->setBuyer(tokens[5]);
            //sign each product to its buyer 
            for(unsigned int i  = 0; i < users.size(); i++){
                if(users[i]->getUsername() == tokens[5]){
                    Buyer* b = getB(tokens[5]);
                    if(b == NULL){
                        b = new Buyer();
                        b->setUsername(users[i]->getUsername());
                        b->setBalance(users[i]->getBalance());
                        b->setAddress(users[i]->getAddress());
                        b->setPhone(users[i]->getPhone());
                        buyer_list.push_back(b);
                    }
                    b->addProduct(p);
                }
            }
            // sign each product to its seller
            p->setSeller(tokens[6]);
            for(unsigned int i  = 0; i < users.size(); i++){
                if(users[i]->getUsername() == tokens[6]){
                    Seller * s = getS(tokens[6]);
                    if(s == NULL){
                        s = new Seller();
                        s->setUsername(users[i]->getUsername());
                        s->setBalance(users[i]->getBalance());
                        s->setAddress(users[i]->getAddress());
                        s->setPhone(users[i]->getPhone());
                        seller_list.push_back(s);
                    }
                    s->addProduct(p);
                }
            }
            p->setInitPrice(stod(tokens[7]));
        }
    } else{
        cout << "fail to open bids file" << endl;
    }
    file.close();
}
Store * Store::GetInstance(string file_user, string file_product){
    if(instance == NULL){
        instance = new Store(file_user, file_product);
    }
    return instance;
}
// display products base on if sold
//choice 1: view input Seller sold product or on sale product
//choice 2: view similar products that were historically sold
void Store::displaySellerProduct(int choice, Seller* seller, string type, string quality){
    int count = 0;
    if(seller_list.empty()){
        cout << "no user and product have been added.";
    } else{
        if(choice == 1){
        cout << endl;
        cout<< "      Seller Name       productID        product type        product state        bids" << endl;
        // ouput every element in the map via loop
        for(unsigned int i = 0; i < seller_list.size(); i++){ 
            if(seller_list[i] == seller){
                for(unsigned int k = 0; k < seller_list[i]->getProduct().size(); k++){
                        cout << count++ << "      ";
                        cout << seller_list[i]->getUsername() << "            ";
                        cout << seller_list[i]->getProduct()[k]->getID() << "                ";
                        cout << seller_list[i]->getProduct()[k]->getTypeName() << "            ";
                        if(seller_list[i]->getProduct()[k]->getIsSold()) cout << "sold" << "            ";
                        else cout << "on sale" << "            ";
                        if(seller_list[i]->getProduct()[k]->getBidOpen())cout << "open" << endl;
                        else cout << "closed" << endl;
                }
            }
        }
        } else if(choice == 2){
            cout << endl;
            cout<< "      product quality        product type        initital price        final price" << endl;
            for(unsigned int i = 0; i < seller_list.size(); i++){
                for(unsigned int k = 0; k < seller_list[i]->getProduct().size(); k++){
                    // output if is sold and type is the same as input type
                    if(seller_list[i]->getProduct()[k]->getIsSold() && seller_list[i]->getProduct()[k]->getTypeName()== type &&seller_list[i]->getProduct()[k]-> getQuality() == quality){
                        cout << count++ << "      ";
                        cout << seller_list[i]->getProduct()[k]->getQuality() << "                ";
                        cout << seller_list[i]->getProduct()[k]->getTypeName() << "            ";
                        cout << seller_list[i]->getProduct()[k]->getInitPrice() << "            ";
                        cout << seller_list[i]->getProduct()[k]->getFinalPrice() << "            " << endl;
                    }
                }
            }
        }
    }
}
// choice 1: view already brought product by input buyer
// choice 2: view product input buyer bids on
void Store ::displayBuyerProduct(int choice, Buyer* buyer){
    int count = 0;
    if(choice == 1){
        cout << endl;
        cout<< "      Buyer Name       productID        product type        product state" << endl;
        // ouput every element in the map via loop
        for(unsigned int i = 0; i < buyer_list.size(); i++){ 
            if(buyer_list[i] == buyer){
                for(unsigned int k = 0; k < buyer_list[i]->getOwnProduct().size(); k++){
                    if(buyer_list[i]->getOwnProduct()[k]->getIsSold()){
                        cout << count++ << "      ";
                        cout << buyer_list[i]->getUsername() << "            ";
                        cout << buyer_list[i]->getOwnProduct()[k]->getID() << "                ";
                        cout << buyer_list[i]->getOwnProduct()[k]->getTypeName() << "            ";
                        cout << "own" << endl;
                    }
                }
            } 
        }
    } else if(choice == 2){
        cout << endl;
        cout << "      Product type          Product Quality         Bids($)" << endl;
        for(unsigned int i = 0; i < buyer_list.size(); i++){
            if(buyer_list[i] == buyer){
                //cout << "find the shit"  << buyer_list[i]->getProduct().size()<< endl;
                for(unsigned int k = 0; k < buyer_list[i]->getBidProduct().size(); k++){
                    cout << "       ";
                    cout << (buyer_list[i]->getBidProduct()[k])->getTypeName() << "                  ";
                    cout << (buyer_list[i]->getBidProduct()[k])->getQuality() << "                     ";
                    map<string, double> temp = (buyer_list[i]->getBidProduct()[k])->getBidsList();
                    for (auto it = temp.begin(); it != temp.end(); ++it){
                        if (it-> first == buyer->getUsername()){
                            cout << it->second << endl;
                            break;
                        }
                    }
                }  
            }
        }
    }
}
// return the username of max bid
pair<string,double> winner(map<string, double> list){
    double max = 0;
    string name;
    for(auto it = list.cbegin(); it != list.cend(); ++it){
        if(it->second > max){
            max = it->second;
            name = it-> first;
        }
    }
    pair<string,double> res(name,max);
    return res;
}
//update info after close bids
void Store::closeBid(Product* p){
    // loop until find highest bids buyer who can buy this product
    while(1){
        // loop through buyer list address
        for(int i = 0; i < buyer_list.size(); i++){
            // find the buyer address and have enough money 
            if(buyer_list[i]->getUsername() == winner(p->getBidsList()).first && buyer_list[i]->getBalance()>= winner(p->getBidsList()).second){
                // set ownship and close bids
                p->setBuyer(buyer_list[i]->getUsername());
                p->setBidOpen(false);
                p->setIsSold(true);
                // update user balance
                double left = buyer_list[i]->getBalance() - winner(p->getBidsList()).second;
                buyer_list[i]->setBalance(left);
                // send a email
                pair <string, string> mess("congrats, you win the product!", p->getSeller());
                // update seller buyer account balance
                for(unsigned int a = 0; a < seller_list.size(); a++){
                    if(seller_list[a]->getUsername() == p->getSeller()){
                        seller_list[a]->setBalance(seller_list[a]->getBalance()+winner(p->getBidsList()).second);
                    }
                }
                buyer_list[i]->addMail(mess);
                // move other buyer from bidding this product.
                for(unsigned int k = 0; k < buyer_list.size(); k++){
                    buyer_list[k]->removeUnbids();
                }
                // delete the product from on sale list
                for(unsigned int i = 0; i < productOnsale.size(); i++){
                    if(p == productOnsale[i]){
                        productOnsale.erase(productOnsale.begin()+i);
                    }
                }
                break;
            } 
        }
        // if the highest bid buyer not have enough money
        // set his bids to zero on this product
        p->removeBids(winner(p->getBidsList()).first);
        // if all the buyer who bids on this product have not enough money just do nothing
        if(winner(p->getBidsList()).second == 0) break;
    }
}

// get the buyer coorsponding to the name

Buyer* Store::getB(string name){//simple search through buyers
    for(unsigned int i = 0; i < buyer_list.size(); i++){
        if(buyer_list[i]->getUsername() == name){//checks if username matches search, returns buyer object if found
            return buyer_list[i];
        }
    }
    return NULL;
}

Seller* Store::getS(string name){
    for(unsigned int i = 0; i < seller_list.size(); i++){//simple search through seller list instead of buyer
        if(seller_list[i]->getUsername() == name){//if the name is found, return the seller; return nothing otherwise
            return seller_list[i];
        }
    }
    return NULL;
}
void Store:: displayOnSaleProduct(){//checks for all available products in onsale vector, prints them with their id, type, quality, and price
    int count = 0;
    cout << "    product ID         product type         product quality        price" << endl;
    for(unsigned int i = 0; i < productOnsale.size(); i++){
        cout << count;
        cout << "   "<< productOnsale[i]->getID() << "       ";
        cout << "   "<< productOnsale[i]->getTypeName() << "         ";
        cout << "   "<< productOnsale[i]->getQuality() << "         ";
        cout << "   "<< productOnsale[i]->getInitPrice() << "         " << endl;
        count++;
    }
}
Product* Store::getById(int id){//returns product through simple search by id
    for(unsigned int i = 0; i < productOnsale.size(); i++){//checks if the product is present in the vector of onsale items
        if(productOnsale[i]->getID() == id) return productOnsale[i];
    }
    return NULL;
}