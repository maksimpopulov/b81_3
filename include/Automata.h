#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

enum class STATES {
    OFF,      
    WAIT,     
    ACCEPT,   
    CHECK,    
    COOK      
};

class Automata {
private:
    int cash;                           
    std::vector<std::string> menu;      
    std::vector<int> prices;           
    STATES state;                     
    int selectedDrinkIndex;            

public:
    Automata();

    void on();                          
    void off();                         
    void coin(int amount);              
    std::vector<std::string> getMenu(); 
    STATES getState();                  
    bool choice(int index);             
    bool check();                       
    void cancel();                      
    void cook();                        
    void finish();                      


    int getCash() const;               
    void loadMenu(const std::vector<std::string>& drinks, const std::vector<int>& costs); 
};

#endif
