#include "../User.h"

int main(){
    // string phone = "7203330940";
    // string username = "brain not found";
    // string address = "s nate cir";
    // double balance = 3224.34;
    User* u = new User();
    User* u1 = new User();
    cout << "phone: " << u->getPhone() << endl;
    cout << "user: " <<u->getUsername() << endl;
    cout << "adress: " << u->getAddress() << endl;
    cout <<"balance: " << u->getBalance() << endl;

    // test mailbox
    u->displayMail();
    pair<string, User*>s("love the bids", u);
    u->addMail(s);
    u->displayMail();
    // rate
    // if empty 
    cout << "rate: " << u->getRate() << endl;;
    u->addRate(4);
    u->addRate(4.4);
    u->addRate(4.3);
    u->addRate(4.2);
    cout << "rate after insertion: " <<fixed<<setprecision(1)<< u->getRate();
    cout << "==: " << (u == u1) << endl;
}