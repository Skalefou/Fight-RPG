#ifndef SELLER_H
#define SELLER_H
#pragma once

#include "fighter.h"

constexpr signed int PROBABILITY_SELLER_COMING = 10; // x/100
constexpr signed int POTIONCOST = 100; // x/100

void errorCin();

class Seller {
public:
	void alea(Fighter &player, int round);
private:
	bool errorSell(bool weaponS);
	bool verifWeaponSell(Weapon& weapon, Fighter& player);
	void tradeTable(Fighter& player);
	unsigned int costWeaponGold(Weapon& weapon, bool classCharacter, bool f);
	void givePotion(Fighter& player);
	void giveWeapon(Fighter& player, Weapon weapon, int cost);
};

#endif