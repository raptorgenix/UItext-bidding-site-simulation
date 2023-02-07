#include "User.h"

// user class constructor
User::User(){//default constructor, user begins with $10k
    phone_num = "phone";
    username = "name";
    address = "addresses";
    account_balance = 10000.0;
    id = "user";
}
User::User(string phone, string name, string addresses, double balance){ //intstantiate user with attributes from file when selected
    phone_num = phone;
    username = name;
    address = addresses;
    account_balance = balance;
}
 // read message
 bool User:: displayMail(){
    if(mailbox.empty()){ //when mailbox is empty, give user default  empty message
        cout << endl;
        cout << "Currently no mail in the mailBox " << endl;
        return false; //return false to indicate empty mailbox to caller
    } else{
        cout << endl;
        for(auto it = mailbox.cbegin(); it != mailbox.cend(); ++it){//iterate through mailbox to display messages
            cout << "message: " << it->first << "     from user: " <<it->second<< endl;
        }
    }
    return true;
 }
// return the mean of vector
 double User:: getRate(){
     if(rate_list.empty()){
         return 0;
     } else{
         double sum = 0.0;
         for(unsigned int i = 0; i < rate_list.size(); i++){
             sum += rate_list[i];
         }
         return sum;
     }
 }

 bool User:: operator==(const User& u1){ //overriden operator to check equivalency of user objects, checks username/address/balance/phonenumber to see if all are the same
     return (u1.username == this->username &&
             u1.address == this-> address &&
             u1.account_balance == this->account_balance &&
             u1.phone_num == this->phone_num);
 }
