#include "TextUI.h"
#include<time.h>

TextUI::TextUI(){//generate menu options for seller and buyer into vectors
    seller_menu.push_back("back");
    seller_menu.push_back("post product for sale");
    seller_menu.push_back("view similar products");
    seller_menu.push_back("read and respond messages");
    seller_menu.push_back("check balance");
    seller_menu.push_back("rate user");
    seller_menu.push_back("update info");
    seller_menu.push_back("view product sold and yet to be sold");
    seller_menu.push_back("close bids");
    seller_menu.push_back("exit");

    buyer_menu.push_back("back");
    buyer_menu.push_back("view products for sale");
    buyer_menu.push_back("palce bids");
    buyer_menu.push_back("read and respond messages");
    buyer_menu.push_back("check balance");
    buyer_menu.push_back("rate user");
    buyer_menu.push_back("update info");
    buyer_menu.push_back("view bought product");
    buyer_menu.push_back("view bid product");
    buyer_menu.push_back("exit");
}

string TextUI::mainMenu(string str){
    int choice = -1;
    vector<string> menu; //menu object containing options
    if(str == "buyer") menu = buyer_menu; //determine menu based on whether user is a seller or a buyer
    else menu = seller_menu;
    while (choice < 0 || choice >= menu.size()) {//retrieve input from user to choose menu options in a while loop
        // display the main menu
        for (int i = 0; i < menu.size(); i++) {
        cout << to_string(i) << ": " << menu[i] << endl;
        }
        string str_choice;
        cin >> str_choice;
        try {
        choice = std::stoi(str_choice);
        } catch (const std::invalid_argument& ia) {
        std::cout << "Enter a number" << std::endl;
        }
    }
    return menu[choice];
}
int TextUI::RouteChoice(Store *store, string choice, string id){//handler for menu option selected --- id is "buyer" or seller depending on what user is

    Seller* curr_seller = store->getOneSeller(); // CoolGuy5
    Buyer* curr_buyer = store->getOneBuyer(); // LongName6
    if(choice == "post product for sale"){//if user chooses to put product on sale
        string type;
        string quality;
        string init_price;
        cout <<"pls enter you product info:" << endl; //request user input for name/quality/price
        cout << "type name: ";
        cin >> type;
        cout << "quality: ";
        cin >> quality;
        cout << "initial price: ";
        cin >> init_price;

        Product* p;
        if(type == "iphone") p = ProductFactory::getIphone();//generate product object from factory depending on the product type input
        else if(type == "textbook") p = ProductFactory::getTextbook();
        else if(type == "apartment") p = ProductFactory::getApartment();
        else if(type == "hat") p = ProductFactory::getHat();
        else  p = ProductFactory::getDell();//for edge cases, just assume the product is a dell

        srand (time(NULL));
        int pid = rand()%10000;
        p->setID(pid); //assign product attributes after creating the object from the factory (assign seller information and product information)
        p->setInitPrice(stod(init_price));
        p->setquality(quality);
        p->setSeller(curr_seller->getUsername());
        p->setIsSold(false);
        p->setBidOpen(true);
        
        if(curr_seller->addProduct(p)){ //error catcher; if the product is succesfully added for sale, add it to the store
            store->addProduct(p);
            cout << "success adding products" << endl;
            cout << endl;
        }
        return 0; //error

    } else if(choice == "view similar products"){ //displays all the products of the same type/quality as given by user
        string type;
        string quality;
        cout <<"pls enter the product info you want to view:" << endl;
        cout << "type name: ";
        cin >> type;
        cout << "quality: ";
        cin >> quality;
        store->displaySellerProduct(2, curr_seller, type, quality);
        return 0;
    }else if(choice =="read and respond messages"){//show all messages in mailbox for user

        string input;
        string name;
        string content;
        if (id == "buyer") curr_buyer->displayMail();//display messages sent to buyer, no other actions needed
        else curr_seller->displayMail(); //in the case of sellers, allow the seller to respond to messages from buyers
        cout << "do you want to respond any messages? Y/N  ";
        cin >> input;
        cout << endl;
        if(input =="y" || input=="Y"){ //respond to users from inbox
            cout << "enter username you want to respond: ";
            cin >> name;
            if(id == "seller"){
                if(store->getB(name) == NULL){ //search for buyer, tell user if the buyer does not exist
                    cout << "user doesn't exist" << endl;
                } else{
                    cout << "enter your responds: "<< endl; //populate content field to send message to buyer
                    cin >> content;
                    cout << endl;
                    pair<string, string>mail(content, curr_seller->getUsername());
                    store->getB(name)->addMail(mail); //append mail vector for the designated buyer with the content input and the username of the seller sending the message
                }
            } else{ //if the user is a buyer, get seller name
                if(store->getS(name) == NULL){
                    cout << "user doesn't exist" << endl;
                } else{
                    cout << "enter your responds: "<< endl;
                    cin >> content;
                    cout << endl;
                    pair<string, string>mail(content, curr_seller->getUsername());
                    store->getS(name)->addMail(mail); //append seller mailbox
                }
            }
        }
        
        return 0;

    }else if(choice == "rate user"){

        string name;
        string rate;
        double rate1 = 0.0; //initialize rating empty info
        cout << "enter username you want to rate: ";
        cin >> name;
        cout << endl;
        if (id == "seller"){
            Buyer *checkb = store->getB(name);
            if (checkb == NULL){
                cout << "Could not find this user" << endl;
                return 0;
            }
        }
        if(id == "buyer") {
            Seller *checks = store->getS(name);
            if(checks == NULL){
                cout << "Could not find this user" << endl;
                return 0;
            }
        }
        if(id == "seller") rate1 = store->getB(name)->getRate();//get buyer rating by the username input to rate them (if the user is a seller)
        else rate1 = store->getS(name)->getRate();//if they are a buyer, they will instead be rating a seller
        cout << "user current rating is: " << rate1 << endl;
        cout << "enter your rating: ";
        cin >> rate;
        cout << endl;
        if(id == "seller"){
            store->getB(name)->addRate(stod(rate));//add new rating to the vector of that buyer's ratings (if user is a seller)
            rate1 = store->getB(name)->getRate();//get new rating after user has added one
        }
        else{
            store->getS(name)->addRate(stod(rate));//add new rating to seller's vector
            rate1 = store->getS(name)->getRate();
        }
        cout << "after rating, user rating is: " << rate1 << endl;
        cout << endl;
        return 0;

    }else if(choice == "check balance"){

        if(id == "seller") cout << "current balance is: " << curr_seller->getBalance() << endl;//get balance from user class
        else cout << "current balance is: " << curr_buyer->getBalance() << endl;
        return 0;

    }else if(choice == "update info"){
        string c;
        int check = 0;
        string name;
        string address;
        string phone;
        cout << endl;
        cout << "current info: " << endl;
        cout << endl;
        if(id == "seller"){
            cout << check++ << " username: " << curr_seller->getUsername() << endl;//print out existing user information
            cout << check++ << " address: " << curr_seller->getAddress() << endl;
            cout << check++ << " phone: " << curr_seller-> getPhone() << endl;
            cout << endl;
            cout << "pick a number to update: ";
            cin >> c;
            if(c == "0"){
                cout << "enter the username you want to change: ";//add username to user class, updates user info
                cin >> name;
                curr_seller->setUsername(name);//setter called for user with input
            } else if(c == "1"){
                cout << "enter the address you want to change: " << endl;
                cin >> address;
                curr_seller->setAddress(address);//address setter to update user info
            } else{
                cout <<"enter the phone number you want to change: " << endl;
                cin >> phone;
                curr_seller->setPhone(phone);//continued with phone
            }
            cout << endl;
            cout << "successful update info: " << endl;
            cout << endl;
            cout << " username: " << curr_seller->getUsername() << endl;//display new user information after it has been updated
            cout << " address: " << curr_seller->getAddress() << endl;
            cout << " phone: " << curr_seller-> getPhone() << endl;
        } else{
            cout << check++ << " username: " << curr_buyer->getUsername() << endl;//same process for buyer instead of seller
            cout << check++ << " address: " << curr_buyer->getAddress() << endl;
            cout << check++ << " Phone: " << curr_buyer-> getPhone() << endl;
            cout << "pick a number to update: " << endl;
            cin >> c;
            if(c == "0"){
                cout << "enter the username you want to change: ";//option to update different information
                cin >> name;
                curr_buyer->setUsername(name);
            } else if(c == "1"){
                cout << "enter the address you want to change: " << endl;
                cin >> address;
                curr_buyer->setAddress(address);
            } else{
                cout <<"enter the phone number you want to change: " << endl;
                cin >> phone;
                curr_buyer->setPhone(phone);
            }
            cout << endl;
            cout << "successful update info: " << endl;
            cout << endl;
            cout << " username: " << curr_buyer->getUsername() << endl;//print updated information 
            cout << " address: " << curr_buyer->getAddress() << endl;
            cout << " phone: " << curr_buyer-> getPhone() << endl;
        }
        cout << endl;
        return 0;

    }else if(choice == "view product sold and yet to be sold"){

        store->displaySellerProduct(1, curr_seller, "good", "good");//arbitary item in market from store object
        return 0;

    }else if(choice == "close bids"){

        string pid;
        cout << "enter the id of product you want to close: ";
        cin >> pid;
        Product* check = store->getById(stoi(pid));
        if(check == NULL){
            cout << "did not find this ID" << endl;
            return 0;
        }
        store->closeBid(store->getById(stoi(pid)));//closes bidding for the object input
        return 0;

    }else if(choice =="view products for sale"){

        store->displayOnSaleProduct();//call store function to display vector of products available for sale
        return 0;

    }else if(choice =="palce bids"){
        
        string pid;
        string bid;
        cout << "enter the product id you want to bid: ";
        cin >> pid;
        cout << "enter how much you want to bid: ";
        cin >> bid;

        Product* check = store->getById(stoi(pid));
        if(check == NULL){
            cout << "did not find this ID" << endl;
            return 0;
        }
        if(curr_buyer->addBidToProduct(store->getById(stoi(pid)), stod(bid))){//adds one bid to product bid vector (if funds are sufficient)
            cout << "sucess bidding" << endl;
        } else{
            cout << "fail to bid" << endl;//if id is invalid or funds are insufficient
        }
        cout << endl;
        return 0;

    }else if(choice =="view bought product"){

        store->displayBuyerProduct(1, curr_buyer);//call store class to check what products this user object has bought
        return 0;

    }else if(choice =="view bid product"){

        store->displayBuyerProduct(2, curr_buyer);//call store class to get product, returns bids
        return 0;

    }else if(choice == "exit"){//exit choice will end loop for menu
        return -2;
    }else if(choice == "back"){//return to main menu
        return -1;
    }else{
        cout << endl;
        cout << "pick a available number pls" << endl;//edge case checking
        cout << endl;
        return 0;
    }
}

// int TextUI::BuyerRouteChoice(Store *store, string choice, Seller* seller){

// }
// else if(choice =="view products for sale"){

//     }else if(choice =="palce bids"){
        
//     }else if(choice =="rate seller"){
        
//     }else if(choice =="view bought product"){
        
//     }else if(choice =="view bid product"){
        
//     }else if(choice == "exit"){
//         return -2;
//     }else if(choice == "back"){
//         return -1;
//     }else{
//         cout << endl;
//         cout << "pick a available number pls" << endl;
//         cout << endl;
//         return 0;
//     }