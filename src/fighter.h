#ifndef FIGHTER_H
#define FIGHTER_H
#pragma once

#include <string>
#include <fstream>
#include "weapon.h"

constexpr bool WARRIOR = 0;
constexpr bool WIZARD = 1;
constexpr unsigned int HEALTH_MAX_WARRIOR = 100;
constexpr unsigned int HEALTH_MAX_WIZARD = 75;
constexpr unsigned int MANA_MAX_WARRIOR = 5;
constexpr unsigned int MANA_MAX_WIZARD = 20;
constexpr unsigned int POTION_QUANTITY_START = 3;
constexpr unsigned int MINOTAURE = 5;
constexpr unsigned int OGRE = 4;
constexpr unsigned int ORC = 3;
constexpr unsigned int GOBLIN = 2;
constexpr unsigned int GNOME = 1;
constexpr unsigned int COST_FIRE = 1;
constexpr unsigned int COST_HEALTH = 5;
constexpr unsigned int STARTING_MONEY = 100;
constexpr signed int CONSOLE_SIZE_X = 128;
const std::string ATTACK = { "ATTACK" };
const std::string USE_POTION = { "POTION" };
const std::string EXIT = { "EXIT" };
const std::string MAGIC = { "MAGIC" };
const std::string FIRE = { "FIRE (1 mana)" };
const std::string HEALTH = { "HEALTH (5 mana)" };
const std::string LOADS = { "LOAD (L)" };
const std::string SAVE = { "SAVE (S)" };
constexpr bool LOAD = false;
constexpr bool NEW = true;

bool strcmpNoCase(std::string s1, std::string s2);
void changeDictionaryWeapon(std::string w1, std::string w2);
bool contains(std::string str1, std::string str2);
std::string searchCase(std::string select);

class Fighter {
public:
	Fighter(bool classCharacter, std::string name, bool chooseGame); //Player
	Fighter(int id, int level, bool classCharacter, bool chooseGame); //Enemy
	void resetPlayer(bool classCharacter, std::string name);
	void changeEnemy(int id, int level, bool classCharacter);
	void saveFile(std::ofstream& save);
	void loadFile(std::ifstream& save);
	void bossLoad(int id);
	void changeWeaponPlayer(Weapon& weapon);
	void removeMoney(int i);
	void addPotion();
	void attack(Fighter &target);
	bool fire(Fighter& target);
	bool health();
	void receiveAttack(int damage);
	void usePotion();
	void actionEnemy(Fighter &target);
	void gainExperience(Fighter &enemy);
	bool isLive() const;
	std::string nameDisplay() const;
	std::string classCharacterDisplay() const;
	std::string healthDisplay() const;
	std::string manaDisplay() const;
	std::string levelDisplay() const;
	std::string WeaponDisplay() const;
	std::string PotionDisplay() const;
	int ascendHealthMax() const;
	int ascendLevel() const;
	int ascendMoney() const;
	bool ascendClassCharacter() const;
	int ascendPotionQuantity() const;
	Weapon ascendWeapon() const;

private:
	void gainLevel();
	void gainMoney(Fighter& enemy);
	std::string m_name;
	bool m_classCharacter; //m_classCharacter only player
	signed int m_lvl, m_experience; //m_experience only player
	Weapon m_weapon;
	signed int m_health, m_healthMax, m_mana, m_manaMax;
	signed int m_money; //Player Only
	signed int m_potionQuantity;
};

#endif