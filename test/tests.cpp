// Copyright 2026 maksimpopulov
#include <gtest/gtest.h>
#include "Automata.h"

TEST(Testmach, TurnOnFromOff) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), STATES::ON);
}

TEST(Testmach, InitialCashIsZero) {
    Automata a;
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(Testmach, InvalidChoiceIgnored) {
    Automata a;
    a.on();
    a.coin(100);
    EXPECT_FALSE(a.choice(99));
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(Testmach, CancelDuringAcceptResetsCash) {
    Automata a;
    a.on();
    a.coin(150);
    a.cancel();
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::ON);
}

TEST(Testmach, EnoughMoneyForCoffee) {
    Automata a;
    a.on();
    a.coin(80);
    EXPECT_TRUE(a.check(1));
}

TEST(Testmach, CoinInsertionIncreasesCash) {
    Automata a;
    a.on();
    a.coin(1.5);
    EXPECT_DOUBLE_EQ(a.getCash(), 1.5);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(Testmach, DoubleCoinInsertion) {
    Automata a;
    a.on();
    a.coin(1.0);
    a.coin(0.5);
    EXPECT_DOUBLE_EQ(a.getCash(), 1.5);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(Testmach, OffWhileHavingCashReturnsMoney) {
    Automata a;
    a.on();
    a.coin(2.5);
    a.off();
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(Testmach, ChoiceWithoutMoney) {
    Automata a;
    a.on();
    EXPECT_FALSE(a.choice(0));
    EXPECT_EQ(a.getState(), STATES::ON);
}

TEST(Testmach, SuccessfulPurchaseFlow) {
    Automata a;
    a.on();
    a.coin(2.0);
    EXPECT_TRUE(a.choice(0));
    EXPECT_EQ(a.getState(), STATES::COOK);
    a.cook(0);
    EXPECT_EQ(a.getState(), STATES::FINISH);
    double change = a.finish();
    EXPECT_DOUBLE_EQ(change, 1.0);
    EXPECT_EQ(a.getState(), STATES::ON);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(Testmach, InsufficientFundsForDrink) {
    Automata a;
    a.on();
    a.coin(0.8);
    EXPECT_FALSE(a.choice(1));
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.8);
}

TEST(Testmach, GetMenuNotEmpty) {
    Automata a;
    std::string menu = a.getMenu();
    EXPECT_FALSE(menu.empty());
    EXPECT_NE(menu.find("Tea"), std::string::npos);
    EXPECT_NE(menu.find("Coffee"), std::string::npos);
}

TEST(Testmach, InvalidCoinAmountIgnored) {
    Automata a;
    a.on();
    a.coin(-5.0);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
    EXPECT_EQ(a.getState(), STATES::ON);
}

TEST(Testmach, CancelWithoutMoney) {
    Automata a;
    a.on();
    a.cancel();
    EXPECT_EQ(a.getState(), STATES::ON);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(Testmach, CookWithoutChoice) {
    Automata a;
    a.on();
    a.coin(2.0);
    a.cook(0);
    EXPECT_NE(a.getState(), STATES::FINISH);
    EXPECT_EQ(a.getState(), STATES::ACCEPT);
}

TEST(Testmach, TurnOnWhenAlreadyOn) {
    Automata a;
    a.on();
    a.on();
    EXPECT_EQ(a.getState(), STATES::ON);
}

TEST(Testmach, TurnOffWhenAlreadyOff) {
    Automata a;
    a.off();
    EXPECT_EQ(a.getState(), STATES::OFF);
}

TEST(Testmach, ExactPaymentNoChange) {
    Automata a;
    a.on();
    a.coin(1.0);
    EXPECT_TRUE(a.choice(0));
    a.cook(0);
    double change = a.finish();
    EXPECT_DOUBLE_EQ(change, 0.0);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}
