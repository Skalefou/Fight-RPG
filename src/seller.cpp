#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "seller.h"
#include "fighter.h"

void Seller::alea(Fighter& player, int round) {
	if (player.ascendLevel() % 5 == 0 && player.ascendLevel() <= 25 || round % 5 == 0)
		tradeTable(player);
}

bool Seller::verifWeaponSell(Weapon& weapon, Fighter& player) {
	Weapon weaponPlayer = player.ascendWeapon();
	int level[2] = { 0 };
	level[0] += (weaponPlayer.aQuality() - 1) * 5;
	level[0] += weaponPlayer.aLevel();
	level[1] += (weapon.aQuality() - 1) * 5;
	level[1] += weapon.aLevel();
	if (level[0] >= level[1])
		return true;
	else
		return false;
}

bool Seller::errorSell(bool weaponS) {
	if (!(weaponS))
		return true;
	else {
		system("cls");
		std::cout << "Error : This item has already been sold" << std::endl;
		system("pause");
		return false;
	}
}

void Seller::tradeTable(Fighter& player) {
	Weapon weaponSell1(player.ascendLevel(), player.ascendClassCharacter(), 1);
	Weapon weaponSell2((player.ascendLevel() + 1), player.ascendClassCharacter(), 1);
	unsigned int weaponCost1 = costWeaponGold(weaponSell1, player.ascendClassCharacter(), 0), weaponCost2 = costWeaponGold(weaponSell2, player.ascendClassCharacter(), 1);
	std::string select = { "" };
	bool weaponS1 = verifWeaponSell(weaponSell1, player), weaponS2 = verifWeaponSell(weaponSell2, player);

	changeDictionaryWeapon(weaponSell1.WeaponName(), weaponSell2.WeaponName());
	while (1) {
	system("cls");
	system("mode con cols=128 lines=32");
	if (player.ascendLevel() % 5 == 0 && player.ascendLevel() <= 25)
		std::cout << "Be careful, the next enemy is a boss !" << std::endl;
	std::cout << "You have found a merchant !" << std::endl << "You have " << player.ascendMoney() << " gold(s) and " << player.ascendPotionQuantity() << " potion(s) !" << std::endl << "Here is what it offers : " << std::endl;
	std::cout << std::string(3, '\n');
	if(!(weaponS1))
		std::cout << "1) " << weaponSell1.WeaponName() << " ("<< weaponCost1 << " gold)" << std::endl;
	else
		std::cout << "1) " << "---SELL---" << std::endl;
	if(!(weaponS2))
		std::cout << "2) " << weaponSell2.WeaponName() << " (" << weaponCost2 << " gold)" << std::endl;
	else
		std::cout << "2) " << "---SELL---" << std::endl;
	std::cout << "3) Potion (P) (" << POTIONCOST << " gold)" << std::endl;
	std::cout << "4) Exit (E)" << std::endl;

	
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::getline(std::cin, select);
		select = searchCase(select);
		if (select == "exit" || select == "4") break;
		else if ((select == "1" || select == weaponSell1.WeaponName()) && errorSell(weaponS1)) {
			giveWeapon(player, weaponSell1, weaponCost1);
			weaponS1 = verifWeaponSell(weaponSell1, player);
			weaponS2 = verifWeaponSell(weaponSell2, player);
		}
		else if ((select == "2" || select == weaponSell2.WeaponName()) && errorSell(weaponS2)) {
			giveWeapon(player, weaponSell2, weaponCost2);
			weaponS1 = verifWeaponSell(weaponSell1, player);
			weaponS2 = verifWeaponSell(weaponSell2, player);
		}
		else if (select == "3" || strcmpNoCase(select, USE_POTION) || strcmpNoCase(select, "P"))
			givePotion(player);
		else
			errorCin();
			
	}
}

unsigned int Seller::costWeaponGold(Weapon& weapon, bool classCharacter, bool f) {
	unsigned int cost = 0;
	const unsigned int Coef[5] = { 1, 3, 5, 10, 20 };
	cost += Coef[weapon.aQuality() - 1] * 100;
	cost += Coef[weapon.aLevel() - 1] * 10;
	if (f)
		cost *= 1.5;
	
	return cost;
}

void Seller::givePotion(Fighter& player) {
	if (player.ascendMoney() >= POTIONCOST) {
		player.removeMoney(POTIONCOST);
		player.addPotion();
		std::cout << "You bought a potion" << std::endl;
	}
	else
		std::cout << "You do not have enough money !" << std::endl;
}

void Seller::giveWeapon(Fighter& player, Weapon weapon, int cost) {
	if (player.ascendMoney() >= cost) {
		player.removeMoney(cost);
		player.changeWeaponPlayer(weapon);
		std::cout << "You bought a weapon !" << std::endl;
	}
	else
		std::cout << "You do not have enough money !" << std::endl;
}
