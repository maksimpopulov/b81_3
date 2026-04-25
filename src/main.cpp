#include "Automata.h"
#include <iostream>

int main() {
    std::cout << "=== Демонстрация работы автомата горячих напитков ===" << std::endl;

    Automata automata;

    automata.on();

    automata.getMenu();

    automata.coin(150);

    automata.choice(2); 

    automata.cook();

    automata.finish();

    std::cout << "\n=== Второй сценарий: отмена операции ===" << std::endl;

    Automata automata2;
    automata2.on();
    automata2.getMenu();
    automata2.coin(50);
    automata2.choice(4); 
    automata2.cancel();   

    std::cout << "\n=== Третий сценарий: недостаточно средств ===" << std::endl;

    Automata automata3;
    automata3.on();
    automata3.coin(60);
    automata3.choice(3); 
    automata3.cook();     
    automata3.coin(70);  
    automata3.choice(3); 
    automata3.cook();    
    automata3.finish();

    return 0;
}
