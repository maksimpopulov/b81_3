// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"
#include <cassert>
#include <iostream>

void testOn() {
    Automata a;
    assert(a.getState() == STATES::OFF);
    a.on();
    assert(a.getState() == STATES::WAIT);
    std::cout << "✓ Тест 1 пройден: Включение автомата" << std::endl;
}

void testOff() {
    Automata a;
    a.on();
    a.coin(100);
    a.off();
    assert(a.getState() == STATES::ACCEPT);
    a.cancel();
    a.off();
    assert(a.getState() == STATES::OFF);
    std::cout << "✓ Тест 2 пройден: Выключение автомата" << std::endl;
}

void testCoin() {
    Automata a;
    a.on();
    a.coin(100);
    assert(a.getState() == STATES::ACCEPT);
    assert(a.getCash() == 100);
    a.coin(50);
    assert(a.getCash() == 150);
    std::cout << "✓ Тест 3 пройден: Внесение денег" << std::endl;
}

void testInvalidChoice() {
    Automata a;
    a.on();
    a.coin(100);
    bool result = a.choice(10);
    assert(!result);
    assert(a.getState() == STATES::ACCEPT);
    std::cout << "✓ Тест 4 пройден: Неверный выбор напитка" << std::endl;
}

void testCheckInsufficientFunds() {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(1);
    bool hasMoney = a.check();
    assert(!hasMoney);
    assert(a.getState() == STATES::ACCEPT);
    std::cout << "✓ Тест 5 пройден: Проверка недостаточности средств" << std::endl;
}

void testCookSuccess() {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(1);
    a.cook();
    assert(a.getState() == STATES::COOK);
    assert(a.getCash() == 20); 
    std::cout << "✓ Тест 6 пройден: Успешное приготовление" << std::endl;
}

void testCancel() {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    assert(a.getState() == STATES::WAIT);
    assert(a.getCash() == 0);
    std::cout << "✓ Тест 7 пройден: Отмена операции" << std::endl;
}

void testFinish() {
    Automata a;
    a.on();
    a.coin(100);
    a.choice(1);
    a.cook();
    a.finish();
    assert(a.getState() == STATES::WAIT);
    assert(a.getCash() == 0);
    std::cout << "✓ Тест 8 пройден: Завершение обслуживания" << std::endl;
}

void testChoiceWrongState() {
    Automata a;
    a.on();
    bool result = a.choice(1);
    assert(!result);
    assert(a.getState() == STATES::WAIT);
    std::cout << "✓ Тест 9 пройден: Выбор напитка в неправильном состоянии" << std::endl;
}

void testFullCycle() {
    Automata a;
    a.on();                         
    a.coin(150);                    
    a.choice(2);                   
    assert(a.getState() == STATES::CHECK);
    a.cook();                       
    assert(a.getState() == STATES::COOK);
    a.finish();                    
    assert(a.getState() == STATES::WAIT);
    assert(a.getCash() == 50);     
    std::cout << "✓ Тест 10 пройден: Полный цикл работы автомата" << std::endl;
}

void testAddMoneyAfterInsufficient() {
    Automata a;
    a.on();
    a.coin(60);              
    a.choice(3);                
    a.cook();                      
    assert(a.getState() == STATES::ACCEPT);
    a.coin(70);                    
    a.choice(3);                
    a.cook();                      
    assert(a.getState() == STATES::COOK);
    a.finish();
    assert(a.getCash() == 10);      
    std::cout << "✓ Тест 11 пройден: Добавление денег после недостатка" << std::endl;
}

void testGetMenu() {
    Automata a;
    auto menu = a.getMenu();
    assert(menu.size() == 6);
    assert(menu[0] == "Эспрессо");
    std::cout << "✓ Тест 12 пройден: Получение меню" << std::endl;
}

int main() {
    std::cout << "Запуск модульных тестов..." << std::endl;
    std::cout << "=========================" << std::endl;

    testOn();
    testOff();
    testCoin();
    testInvalidChoice();
    testCheckInsufficientFunds();
    testCookSuccess();
    testCancel();
    testFinish();
    testChoiceWrongState();
    testFullCycle();
    testAddMoneyAfterInsufficient();
    testGetMenu();

    std::cout << "=========================" << std::endl;
    std::cout << "Все тесты успешно пройдены!" << std::endl;

    return 0;
}
