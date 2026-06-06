// Copyright 2026 maksimpopulov
#include "Automata.h"
#include <iostream>

int main() {
  Automata automata;

  automata.on();
  std::cout << automata.getMenu();

  automata.coin(1.0);
  automata.coin(0.5);

  if (automata.choice(1)) {
    automata.cook(1);
    automata.finish();
  }

  std::cout << "\n--- New customer ---\n";

  automata.coin(3.0);
  std::cout << automata.getMenu();

  if (automata.choice(2)) {
    automata.cook(2);
    automata.finish();
  }

  std::cout << "\n--- Test cancellation ---\n";

  automata.coin(1.5);
  automata.cancel();

  std::cout << "\n--- Shutting down ---\n";

  automata.off();

  return 0;
}
