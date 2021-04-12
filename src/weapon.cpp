#include <cstdlib>
#include <ctime>
#include <string>
#include "weapon.h"
#include "fighter.h"

Weapon::Weapon(int quality, int level, bool type) : m_quality(quality), m_level(level), m_type(type) {

}

Weapon::Weapon(int level, bool type) {
	changeWeapon(level, type);
}

Weapon::Weapon(int level, bool type, bool id) {
	m_quality = (level - 1) / 5 + 1 ;
	m_level = level % 5;
	if (m_quality > 5)
		m_quality = 5;
	if (m_level == 0 || level > 25)
		m_level = 5;
	if (level < 5)
		m_level = level;
	m_type = type;
}

void Weapon::saveWeapon(std::ofstream& save) {
	const std::string V { " " };
	save << m_level << V << m_quality << V << m_type << "\n";
}

void Weapon::loadWeapon(std::ifstream& save) {
	save >> m_level >> m_quality >> m_type;
}

void Weapon::changeWeapon(int level, bool classWeapon) {
	level = aleaLevel(level);
	m_quality = level / 5 + 1;
	m_level = level % 5;
	if (m_quality > 5)
		m_quality = 5;
	if (m_level == 0 || level > 25)
		m_level = 5;
	if (level < 5)
		m_level = level;

	m_type = classWeapon;
}

int Weapon::aleaLevel(int level) {
	int min = (level * 10000) - 30000;
	if (min < 10000)
		min = 10000;
	int max = min + 50000;
	level = rand() % (max - min) + min;
	return level /= 10000;
}

int Weapon::damageWeapon() {
	int damage = 0;
	damage += m_quality * 10;
	damage += (2 * m_level - 2);
	if (m_type == ROD)
		return 5;
	return damage;
}

float Weapon::magicEfficiency() {
	float damage = 0;
	if (m_type != ROD)
		return 0.5;
	damage += m_quality;
	float levelDamage = (2 * m_level) - 2;
	levelDamage /= 10;
	return damage + levelDamage;
}

bool Weapon::aType() const {
	return m_type;
}

signed int Weapon::aLevel() const {
	return m_level;
}

signed int Weapon::aQuality() const {
	return m_quality;
}

std::string Weapon::WeaponName() const {
	std::string name { "" };
	switch (m_quality)
	{
	case 1:
		name += "Basic ";
		break;
	case 3:
		name += "Grand ";
		break;
	case 4:
		name += "Expert ";
		break;
	case 5:
		name += "Master ";
		break;
	}
	if (m_type == SWORD)
		name += "Warrior Sword ";
	else
		name += "Wizard Rod ";
	name += "(level " + convertRomanNumeral(m_level) + ")";
	return name;
}

std::string convertRomanNumeral(int i) {
	switch (i) {
	case 1:
		return "I";
		break;
	case 2:
		return "II";
		break;
	case 3:
		return "III";
		break;
	case 4:
		return "IV";
		break;
	case 5:
		return "V";
		break;
	}
	return "I";
}