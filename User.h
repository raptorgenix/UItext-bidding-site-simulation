#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include<iomanip>

using namespace std;

class User{
    public:
        //construtor
        User();
        User(string phone, string name, string addresses, double balance);
        //getter
        string getPhone(){return phone_num;}
        string getUsername(){return username;}
        string getAddress(){return address;}
        double getBalance(){return account_balance;}// check balance
        bool displayMail(); // read message
        double getRate();// return the mean of vector
        virtual string getID(){return id;}
        //setter
        void setPhone(string num){phone_num = num;}
        void setUsername(string str){username = str;}
        void setAddress(string str){address = str;}
        void setBalance(double num){account_balance = num;}
        void addMail(pair<string, string>s){mailbox.insert(s);}// respond message
        void addRate(double r){rate_list.push_back(r);}
        bool operator==(const User& u1);

    private:
        string phone_num;
        string username;
        string address;
        double account_balance;
        string id;
        vector<double> rate_list;
        map<string, string> mailbox;

};

#endif