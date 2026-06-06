// Copyright 2026 maksimpopulov
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

enum class STATES {
    OFF,
    ON,
    WAIT,
    ACCEPT,
    CHECK,
    COOK,
    CANCEL,
    FINISH
};

class Automata {
private:
    double cash;
    std::vector<std::string> menu;
    std::vector<double> prices;
    STATES state;

public:
    Automata();
    void on();
    void off();
    void coin(double amount);
    std::string getMenu();
    STATES getState();
    bool choice(int drinkIndex);
    bool check(int drinkIndex);
    void cancel();
    void cook(int drinkIndex);
    double finish();
    void loadMenuFromFile(const std::string& filename);
    void setMenu(const std::vector<std::string>& newMenu,
        const std::vector<double>& newPrices);
    double getCash() const;
};

#endif
