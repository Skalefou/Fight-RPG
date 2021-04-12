#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "fighter.h"
#include "weapon.h"

Fighter::Fighter(bool classCharacter, std::string name, bool chooseGame) : m_name(name), m_classCharacter(classCharacter), m_weapon(1, 1, classCharacter), m_potionQuantity(POTION_QUANTITY_START), m_lvl(1), m_experience(0), m_money(STARTING_MONEY) {
	if(chooseGame)
		resetPlayer(classCharacter, name);
	else {
		std::ifstream save { "save.sfile" };
		std::string l;
		getline(save, l);
		loadFile(save);
	}

}

void Fighter::resetPlayer(bool classCharacter, std::string name) {
	if (classCharacter == WARRIOR) {
		m_healthMax = HEALTH_MAX_WARRIOR;
		m_health = HEALTH_MAX_WARRIOR;
		m_manaMax = MANA_MAX_WARRIOR;
		m_mana = MANA_MAX_WARRIOR;
	}
	else {
		m_healthMax = HEALTH_MAX_WIZARD;
		m_health = HEALTH_MAX_WIZARD;
		m_manaMax = MANA_MAX_WIZARD;
		m_mana = MANA_MAX_WIZARD;
	}
}

Fighter::Fighter(int id, int level, bool classCharacter, bool chooseGame) : m_experience(0), m_weapon(level, m_classCharacter), m_money(0) {
	if(chooseGame)
		changeEnemy(id, level, classCharacter);
	else {
		std::ifstream save { "save.sfile" };
		std::string l;
		for (int i = 0; i < 5; i++)
			getline(save, l);
		loadFile(save);
	}
}

void Fighter::changeEnemy(int id, int level, bool classCharacter) {
	m_healthMax = 0;
	m_lvl = level;
	m_classCharacter = classCharacter;
	m_weapon.changeWeapon(level, classCharacter);

	switch (id) {
	case GNOME:
		m_name = "Gnome";
		m_healthMax += 20;
		break;
	case GOBLIN:
		m_name = "Goblin";
		m_healthMax += 50;
		break;
	case ORC:
		m_name = "Orc";
		m_healthMax += 100;
		break;
	case OGRE:
		m_name = "Ogre";
		m_healthMax += 250;
		break;
	case MINOTAURE:
		m_name = "Minotaure";
		m_healthMax += 500;
		break;
	}
	m_healthMax += level * (m_healthMax / 10);

	m_potionQuantity = rand() % (1000 - 0) + 0;
	if (m_potionQuantity < 8) // 1/128
		m_potionQuantity = 3;
	else if (m_potionQuantity < 32) // 1/32
		m_potionQuantity = 2;
	else if (m_potionQuantity < 125) // 1/8
		m_potionQuantity = 1;
	else
		m_potionQuantity = 0;

	if (m_classCharacter == WARRIOR) {
		m_mana = 0;
		m_manaMax = 0;
	}
	else {
		m_manaMax = 20;
		m_manaMax += level * (m_manaMax / 10);
		m_mana = m_manaMax;
		m_healthMax *= 0.75;
		m_health = m_healthMax;
	}

	m_health = m_healthMax;
}

void Fighter::saveFile(std::ofstream& save) {
	const std::string V { " " };
	save << m_name << "\n" << m_classCharacter << V << m_lvl << V << m_experience << V << m_health << V << m_healthMax << V << m_mana << V << m_manaMax << V << m_money << V << m_potionQuantity << "\n";
	m_weapon.saveWeapon(save);
}

void Fighter::loadFile(std::ifstream& save) {
	std::getline(save >> std::ws, m_name);
	save >> m_classCharacter >> m_lvl >> m_experience >> m_health >> m_healthMax >> m_mana >> m_manaMax >> m_money >> m_potionQuantity;
	m_weapon.loadWeapon(save);
}

void Fighter::bossLoad(int id) {
	switch (id) {
		case 1:
			m_name = "Gnome king";
			m_classCharacter = WARRIOR;
			m_lvl = 5;
			m_healthMax = 60;
			m_health = 60;
			m_manaMax = 0;
			m_mana = 0;
			m_weapon.changeWeapon(5, WARRIOR);
			m_potionQuantity = 0;
			break;
		case 2:
			m_name = "Goblin lord";
			m_classCharacter = WARRIOR;
			m_lvl = 10;
			m_healthMax = 175;
			m_health = 175;
			m_manaMax = 0;
			m_mana = 0;
			m_weapon.changeWeapon(10, WARRIOR);
			m_potionQuantity = 0;
			break;
		case 3:
			m_name = "Captain Orc";
			m_classCharacter = WARRIOR;
			m_lvl = 15;
			m_healthMax = 400;
			m_health = 400;
			m_manaMax = 0;
			m_mana = 0;
			m_weapon.changeWeapon(15, WARRIOR);
			m_potionQuantity = 0;
			break;
		case 4:
			m_name = "Noble Ogre";
			m_classCharacter = WARRIOR;
			m_lvl = 20;
			m_healthMax = 750;
			m_health = 750;
			m_manaMax = 0;
			m_mana = 0;
			m_weapon.changeWeapon(20, WARRIOR);
			m_potionQuantity = 0;
			break;
		case 5:
			m_name = "Demonic minotaur";
			m_classCharacter = WARRIOR;
			m_lvl = 25;
			m_healthMax = 3000;
			m_health = 3000;
			m_manaMax = 0;
			m_mana = 0;
			m_weapon.changeWeapon(25, WARRIOR);
			m_potionQuantity = 0;
			break;
	}
}

void Fighter::changeWeaponPlayer(Weapon& weapon) {
	m_weapon = weapon;
}

void Fighter::removeMoney(int i) {
	m_money -= i;
}

void Fighter::addPotion() {
	m_potionQuantity++;
}

void Fighter::attack(Fighter &target) {
	std::cout << m_name << " inflicts " << m_weapon.damageWeapon() << " damage points" << std::endl;
	target.receiveAttack(m_weapon.damageWeapon());
}

bool Fighter::fire(Fighter& target) {
	if (m_mana >= COST_FIRE) {
		std::cout << m_name << " inflicts " << (m_weapon.magicEfficiency() * 15) << " fire damage" << std::endl;
		target.receiveAttack((m_weapon.magicEfficiency() * 15));
		m_mana -= COST_FIRE;
		return false;
	}
	else
		return true;
}

bool Fighter::health() {
	if (m_mana >= COST_HEALTH) {
		std::cout << m_name << " uses the health spell, he recovers " << (m_weapon.magicEfficiency() * 40) << " life points" << std::endl;
		m_health += m_weapon.magicEfficiency() * 40;
		m_mana -= COST_HEALTH;
		if (m_health > m_healthMax)
			m_health = m_healthMax;
		return false;
	}
	return true;
}

void Fighter::receiveAttack(int damage) {
	m_health -= damage;
	if (m_health < 0)
		m_health = 0;
}

void Fighter::usePotion() {
	if (m_potionQuantity > 0) {
		std::cout << m_name << " uses a potion, he recovers all his life" << std::endl;
		m_potionQuantity -= 1;
		m_health = m_healthMax;
		m_mana = m_manaMax;
	}
}

void Fighter::actionEnemy(Fighter &target) {
	if (m_potionQuantity > 0 && m_health <= (m_healthMax / 4))
		usePotion();
	else if (m_mana >= 1 && m_classCharacter == WIZARD)
		fire(target);
	else
		attack(target);
}

void Fighter::gainExperience(Fighter &enemy) {
	int i = rand() % 100;
	if (i <= 30)
		m_potionQuantity++;
	m_experience += (0.75 * enemy.ascendHealthMax());
	m_experience += (5 * enemy.ascendLevel());
	if (m_experience >= m_lvl * 100) {
		m_experience -= m_lvl * 100;
		gainLevel();
	}
	gainMoney(enemy);

}

void Fighter::gainMoney(Fighter& enemy) {
	int i = enemy.ascendHealthMax() * 1;
	i += 5 * enemy.ascendLevel();
	m_money += i;
}

bool Fighter::isLive() const
{
	if (m_health > 0)
		return true;
	else
		return false;
}

std::string Fighter::nameDisplay() const {
	return "Name : " + m_name;
}

std::string Fighter::classCharacterDisplay() const {
	std::string t {""};
	if (m_classCharacter == WARRIOR)
		t = "Warrior";
	else
		t = "Wizard";
	return "Class : " + t;
}

std::string Fighter::healthDisplay() const {
	std::ostringstream i;
	i << "Health : " << m_health << "/" << m_healthMax;
	return i.str();
}

std::string Fighter::manaDisplay() const {
	std::ostringstream i;
	i << "Mana : " << m_mana << "/" << m_manaMax;
	return i.str();
}

std::string Fighter::levelDisplay() const {
	std::ostringstream t;
	t << "Level : " << m_lvl;
	return t.str();
}

std::string Fighter::WeaponDisplay() const {
	std::string name { "Weapon : " };
	name += m_weapon.WeaponName();
	return name;
}

std::string Fighter::PotionDisplay() const {
	std::ostringstream t;
	t << "Potion : " << m_potionQuantity;
	return t.str();
}

int Fighter::ascendHealthMax() const {
	return m_healthMax;
}

int Fighter::ascendLevel() const {
	return m_lvl;
}

int Fighter::ascendMoney() const {
	return m_money;
}

bool Fighter::ascendClassCharacter() const {
	return m_classCharacter;
}

int Fighter::ascendPotionQuantity() const {
	return m_potionQuantity;
}

Weapon Fighter::ascendWeapon() const {
	return m_weapon;
}

void Fighter::gainLevel() {
	m_lvl++;
	if (m_classCharacter == WARRIOR) {
		m_healthMax += (HEALTH_MAX_WARRIOR / 10);
		m_manaMax += (MANA_MAX_WARRIOR / 10);
	}
	else {
		m_healthMax += (HEALTH_MAX_WIZARD / 10);
		m_manaMax += (MANA_MAX_WIZARD / 10);
	}
	m_health = m_healthMax;
	m_mana = m_manaMax;
}
