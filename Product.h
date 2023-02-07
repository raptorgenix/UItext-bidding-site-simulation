#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
#include<map>
using namespace std;

class Product{
    private:
    /* data */
        int product_id;
        double init_price;
        double final_price;
        string quality;
        bool is_sold;
        bool bid_open;
        string category_name;
        string type_name;
        map<string, double>bid_list;
        string buyer;
        string seller;
    public:
    //constructor
    Product();
    //Product(int id, double p1, double p2, string quli, bool if_sold, bool open);
    //getter
    int getID(){return product_id;}
    double getInitPrice(){return init_price;}
    double getFinalPrice(){return final_price;}
    string getQuality(){return quality;}
    bool getIsSold(){return is_sold;}
    bool getBidOpen(){return bid_open;}
    virtual string getCategoryName(){return category_name;}
    virtual string getTypeName(){return type_name;}
    //string getWinner();
    map<string, double>getBidsList(){return bid_list;}
    string getBuyer(){return buyer;}
    string getSeller(){return seller;}
    //setter
    void setID(int num){product_id = num;}
    void setInitPrice(double num){init_price = num;}
    void setquality(string str){quality = str;}
    void setIsSold(bool s){is_sold = s;}
    void setBidOpen(bool s){bid_open = s;} // open/close bids
    void setFinalPrice(double p){final_price = p;}
    void addBids(pair<string, double> b){bid_list.insert(b);}
    bool operator==(const Product& p1);
    void setBuyer(string name){buyer = name;}
    void removeBids(string name);
    void setSeller(string name){seller= name;}
    // void setCategory(string s){category_name = s;}
    // void setType(string s)
};
// category 1
class Phone : public Product{
    public:
        string getCategoryName(){return "Phone";}
};
// category 2
class Computer : public Product{
    public:
        string getCategoryName(){return "Computer";}
};
//category 3
class Book : public Product{
    public:
        string getCategoryName(){return "Book";}
};
//category 4
class House : public Product{
    public:
        string getCategoryName(){return "House";}
};
//category 5
class Clothes : public Product{
    public:
        string getCategoryName(){return "Clothes";}
};
// sub phone
class iphone : public Phone{
    public:
        string getTypeName(){return"iphone";}
};
 // sub Computer
class dell : public Computer{
    public:
        string getTypeName(){return "dell";}

};
// sub book
class textbook : public Book{
    public:
        string getTypeName(){return "textbook";}
};
// sub house
class apartment : public House{
    public:
        string getTypeName(){return "apartment";}
};
// sub clothes
class hat : public Clothes{
    public:
        string getTypeName(){return "hat";}
};
// factory desgin
class ProductFactory{
    public:

    static iphone* getIphone();
    static textbook* getTextbook();
    static apartment* getApartment();
    static hat* getHat();
    static dell* getDell();

};

#endif