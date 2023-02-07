#ifndef TEXTUI_H
#define TEXTUI_H

#include <iostream>
#include <string>
#include <vector>
#include "Store.h"
using namespace std;

class TextUI {
public:
  TextUI();

  string mainMenu(string str);

  int RouteChoice(Store *store, string choice, string id);

private:
  vector<string> buyer_menu;
  vector<string> seller_menu;
};

#endif  


