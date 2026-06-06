// Copyright 2026 maksimpopulov
#include "Automata.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

Automata::Automata() : cash(0.0), state(STATES::OFF) {
  menu = {"Tea", "Coffee", "Hot Chocolate", "Milk"};
  prices = {1.0, 1.5, 2.0, 1.2};
}

void Automata::on() {
  if (state == STATES::OFF) {
    state = STATES::ON;
    cash = 0.0;
    std::cout << "Automaton is ON.\n";
  } else {
    std::cout << "Automaton is already ON.\n";
  }
}

void Automata::off() {
  if (state != STATES::OFF) {
    if (cash > 0) {
      std::cout << "Returning " << cash << " credits. ";
      cash = 0.0;
    }
    state = STATES::OFF;
    std::cout << "Automaton is OFF.\n";
  } else {
    std::cout << "Automaton is already OFF.\n";
  }
}

void Automata::coin(double amount) {
  if (amount <= 0) {
    std::cout << "Invalid amount.\n";
    return;
  }

  if (state == STATES::ON) {
    state = STATES::WAIT;
    cash += amount;
    std::cout << "Inserted " << amount << " credits. Total: " << cash << "\n";
    state = STATES::ACCEPT;
  } else if (state == STATES::ACCEPT || state == STATES::WAIT) {
    cash += amount;
    std::cout << "Inserted " << amount << " credits. Total: " << cash << "\n";
  } else {
    std::cout << "Cannot accept coins in current state.\n";
  }
}

std::string Automata::getMenu() {
  std::stringstream ss;
  ss << "===== MENU =====\n";
  for (size_t i = 0; i < menu.size(); ++i) {
    ss << i + 1 << ". " << menu[i] << " - " << prices[i] << " credits\n";
  }
  ss << "================\n";
  return ss.str();
}

STATES Automata::getState() {
  return state;
}

bool Automata::check(int drinkIndex) {
  if (drinkIndex < 0 || drinkIndex >= static_cast<int>(prices.size())) {
    std::cout << "Invalid drink selection.\n";
    return false;
  }

  if (state == STATES::ACCEPT || state == STATES::WAIT) {
    state = STATES::CHECK;
    if (cash >= prices[drinkIndex]) {
      std::cout << "Sufficient funds.\n";
      state = STATES::COOK;
      return true;
    } else {
      std::cout << "Insufficient funds. Need "
                << prices[drinkIndex] - cash << " more credits.\n";
      state = STATES::ACCEPT;
      return false;
    }
  } else {
    std::cout << "Cannot check funds in current state.\n";
    return false;
  }
}

bool Automata::choice(int drinkIndex) {
  if (drinkIndex < 0 || drinkIndex >= static_cast<int>(menu.size())) {
    std::cout << "Invalid drink index.\n";
    return false;
  }

  if (state == STATES::ACCEPT) {
    return check(drinkIndex);
  } else {
    std::cout << "Cannot make a choice in current state.\n";
    return false;
  }
}

void Automata::cook(int drinkIndex) {
  if (drinkIndex < 0 || drinkIndex >= static_cast<int>(menu.size())) {
    std::cout << "Invalid drink index.\n";
    return;
  }

  if (state == STATES::COOK) {
    std::cout << "Cooking " << menu[drinkIndex] << "...\n";
    for (int i = 0; i < 3; ++i) {
      std::cout << ".";
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "\n" << menu[drinkIndex] << " is ready! Enjoy!\n";
    cash -= prices[drinkIndex];
    state = STATES::FINISH;
  } else {
    std::cout << "Cannot cook in current state.\n";
  }
}

void Automata::cancel() {
  if (state == STATES::ACCEPT || state == STATES::WAIT ||
      state == STATES::CHECK || state == STATES::COOK) {
    state = STATES::CANCEL;
    std::cout << "Operation cancelled.\n";
    finish();
  } else {
    std::cout << "Cannot cancel in current state.\n";
  }
}

double Automata::finish() {
  double change = 0.0;
  if (state == STATES::FINISH || state == STATES::CANCEL) {
    change = cash;
    if (change > 0) {
      std::cout << "Returning change: " << change << " credits\n";
    }
    cash = 0.0;
    state = STATES::ON;
    std::cout << "Transaction completed.\n";
  } else if (state == STATES::ACCEPT || state == STATES::WAIT) {
    change = cash;
    cash = 0.0;
    state = STATES::ON;
    std::cout << "Transaction cancelled. Returning " << change << " credits.\n";
  } else {
    std::cout << "Cannot finish in current state.\n";
  }
  return change;
}

void Automata::loadMenuFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << "\n";
    return;
  }

  menu.clear();
  prices.clear();

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string name;
    double price;
    if (std::getline(ss, name, ',') && (ss >> price)) {
      menu.push_back(name);
      prices.push_back(price);
    }
  }
  file.close();
  std::cout << "Menu loaded from " << filename << "\n";
}

void Automata::setMenu(const std::vector<std::string>& newMenu,
                       const std::vector<double>& newPrices) {
  if (newMenu.size() == newPrices.size() && !newMenu.empty()) {
    menu = newMenu;
    prices = newPrices;
    std::cout << "Menu updated successfully.\n";
  } else {
    std::cout << "Error: Menu and prices size mismatch or empty menu.\n";
  }
}

double Automata::getCash() const {
  return cash;
}
