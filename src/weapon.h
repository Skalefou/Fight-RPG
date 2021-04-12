#ifndef WEAPON_H
#define WEAPON_H
#pragma once

#include <fstream>

constexpr bool SWORD = 0;
constexpr bool ROD = 1;

std::string convertRomanNumeral(int i);

class Weapon {
public:
	Weapon(int quality, int level, bool type);
	Weapon(int level, bool type);
	Weapon(int level, bool type, bool id);
	void saveWeapon(std::ofstream& save);
	void loadWeapon(std::ifstream& save);
	void changeWeapon(int level, bool classWeapon);
	int damageWeapon();
	float magicEfficiency();
	bool aType() const;
	signed int aLevel() const;
	signed int aQuality() const;
	std::string WeaponName() const;
private:
	int aleaLevel(int level);
	signed int m_level, m_quality;
	bool m_type; 
};

#endif