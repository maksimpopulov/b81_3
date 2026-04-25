#include "Automata.h"
#include <iostream>
#include <thread>
#include <chrono>

Automata::Automata()
    : cash(0), state(STATES::OFF), selectedDrinkIndex(-1) {
    menu = { "Эспрессо", "Американо", "Капучино", "Латте", "Горячий шоколад", "Чай" };
    prices = { 80, 100, 120, 130, 110, 70 };
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        std::cout << "Автомат включен. Состояние: Ожидание" << std::endl;
    }
    else {
        std::cout << "Автомат уже включен" << std::endl;
    }
}

void Automata::off() {
    if (state == STATES::OFF) {
        std::cout << "Автомат уже выключен" << std::endl;
    }
    else if (state == STATES::WAIT) {
        state = STATES::OFF;
        cash = 0;
        selectedDrinkIndex = -1;
        std::cout << "Автомат выключен" << std::endl;
    }
    else {
        std::cout << "Невозможно выключить автомат в текущем состоянии" << std::endl;
    }
}

void Automata::coin(int amount) {
    if (amount <= 0) {
        std::cout << "Введите положительную сумму" << std::endl;
        return;
    }

    if (state == STATES::WAIT) {
        cash = amount;
        state = STATES::ACCEPT;
        std::cout << "Внесено " << amount << " руб. Состояние: Приём денег" << std::endl;
    }
    else if (state == STATES::ACCEPT) {
        cash += amount;
        std::cout << "Добавлено " << amount << " руб. Всего: " << cash << " руб." << std::endl;
    }
    else {
        std::cout << "Невозможно внести деньги в текущем состоянии" << std::endl;
    }
}

std::vector<std::string> Automata::getMenu() {
    std::cout << "\n=== МЕНЮ ===" << std::endl;
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << ". " << menu[i] << " - " << prices[i] << " руб." << std::endl;
    }
    return menu;
}

STATES Automata::getState() {
    return state;
}

bool Automata::choice(int index) {
    if (state != STATES::ACCEPT) {
        std::cout << "Выбор напитка доступен только в состоянии 'Приём денег'" << std::endl;
        return false;
    }

    if (index < 1 || index > static_cast<int>(menu.size())) {
        std::cout << "Неверный номер напитка" << std::endl;
        return false;
    }

    selectedDrinkIndex = index - 1;
    state = STATES::CHECK;
    std::cout << "Выбран напиток: " << menu[selectedDrinkIndex]
        << " (" << prices[selectedDrinkIndex] << " руб.)" << std::endl;
    return true;
}

bool Automata::check() {
    if (state != STATES::CHECK) {
        std::cout << "Проверка доступна только в состоянии 'Проверка наличности'" << std::endl;
        return false;
    }

    if (cash >= prices[selectedDrinkIndex]) {
        std::cout << "Средств достаточно. Начинаем приготовление..." << std::endl;
        return true;
    }
    else {
        std::cout << "Недостаточно средств. Внесено: " << cash
            << " руб., требуется: " << prices[selectedDrinkIndex] << " руб." << std::endl;
        std::cout << "Вернитесь в состояние 'Приём денег' и внесите недостающую сумму" << std::endl;
        state = STATES::ACCEPT;
        return false;
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        if (cash > 0) {
            std::cout << "Возврат денег: " << cash << " руб." << std::endl;
            cash = 0;
        }
        selectedDrinkIndex = -1;
        state = STATES::WAIT;
        std::cout << "Сеанс отменён. Состояние: Ожидание" << std::endl;
    }
    else if (state == STATES::COOK) {
        std::cout << "Невозможно отменить - напиток уже готовится" << std::endl;
    }
    else {
        std::cout << "Отмена недоступна в текущем состоянии" << std::endl;
    }
}

void Automata::cook() {
    if (state != STATES::CHECK) {
        std::cout << "Приготовление доступно только после проверки средств" << std::endl;
        return;
    }

    if (cash >= prices[selectedDrinkIndex]) {
        cash -= prices[selectedDrinkIndex];
        state = STATES::COOK;
        std::cout << "Приготовление " << menu[selectedDrinkIndex] << "... ";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Готово!" << std::endl;
    }
    else {
        std::cout << "Недостаточно средств для приготовления" << std::endl;
        state = STATES::ACCEPT;
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        std::cout << "Заберите ваш " << menu[selectedDrinkIndex] << std::endl;
        if (cash > 0) {
            std::cout << "Ваша сдача: " << cash << " руб." << std::endl;
            cash = 0;
        }
        selectedDrinkIndex = -1;
        state = STATES::WAIT;
        std::cout << "Спасибо за покупку! Состояние: Ожидание" << std::endl;
    }
    else {
        std::cout << "Завершение обслуживания доступно только после приготовления" << std::endl;
    }
}

int Automata::getCash() const {
    return cash;
}

void Automata::loadMenu(const std::vector<std::string>& drinks, const std::vector<int>& costs) {
    if (drinks.size() == costs.size()) {
        menu = drinks;
        prices = costs;
    }
}
