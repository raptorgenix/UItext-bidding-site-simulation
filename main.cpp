
#include"TextUI.h"

int main(int argc, char* argv[]){


    //string choice = ui.mainMenu("buyer");
    //cout << choice << endl;
    Store *s = Store::GetInstance(argv[1], argv[2]);
    //ui.RouteChoice(s, choice);
    TextUI ui;
    string choice;
    while (choice != "3") {

        cout << "welcome to BidToBuy" << endl;
        cout << "1: be a Buyer" << endl;
        cout << "2: be a Seller" << endl;
        cout << "3: exit" << endl;
        cout << "pick a side: ";
        cin >> choice;
        cout << endl;
        
        if(choice == "1"){//user must decice if they are going to be a buyer or seller; buyer is selection 1, seller is selection 2
            while(choice != "exit"){
                choice = ui.mainMenu("buyer"); //get buyer menu options to choose from
                cout << endl;
                int check = ui.RouteChoice(s, choice, "buyer"); //check if user is still in session using menu
                if(check == -1) break;
                else if(check == -2) exit(0);
            }
        } else if(choice == "2"){//route to seller menu
             while(choice != "exit"){
                choice = ui.mainMenu("seller");//display menu options for seller from mainmenu class
                cout << endl;
                int check = ui.RouteChoice(s, choice, "seller");
                if(check == -1) break; //when user decides to exit or session is complete, trigger break conditions
                else if(check == -2) exit(0);
            }
        } else if(choice != "3") cout << "enter a number pls" << endl; //edge case handler if users have not input a valid command, but exit if user picks option 3
  }

}