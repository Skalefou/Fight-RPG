#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "fighter.h"
#include "weapon.h"
#include "seller.h"

std::string dictionary[13] = {
    "attack",
    "exit",
    "fire",
    "health",
    "load",
    "magic",
    "new",
    "potion",
    "save",
    "warrior",
    "wizard",
    " ",
    " "
};

// CHANGELOG: Mettre à jour le changelog après une modification.

void changeDictionaryWeapon(std::string w1, std::string w2) {
    transform(w1.begin(), w1.end(), w1.begin(), ::tolower);
    transform(w2.begin(), w2.end(), w2.begin(), ::tolower);
    dictionary[11] = w1;
    dictionary[12] = w2;
}

bool strcmpNoCase(std::string s1, std::string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if (s1 == s2)
        return true;
    else
        return false;
}

bool contains(std::string str1, std::string str2) {
    return (str1.find(str2) != std::string::npos);
}

std::string searchCase(std::string select) {
    transform(select.begin(), select.end(), select.begin(), ::tolower);
    for (int i = 0; i < 13; i++)
        if (contains(dictionary[i], select))
            return dictionary[i];
    return select;
}

void errorCin() {
    std::cout << std::endl << "Error, please try again" << std::endl;
    std::cin.clear();
    std::cin.ignore(255, '\n');
}

std::string selectName(int round) {
    std::string name {""};
    std::string verif {""};
    
    if (round) {
        do {
            std::cout << "What is your name ? (max 16 characters) : ";
            while (!(std::cin >> name) || name.size() > 16)
                errorCin();
            std::cout << std::endl << "Are you sure of this name ? (Yes / No) : ";
            while (!(std::cin >> verif) || (!strcmpNoCase(verif, "NO")) && (!strcmpNoCase(verif, "YES")) && (!strcmpNoCase(verif, "N")) && (!strcmpNoCase(verif, "Y")))
                errorCin();
        } while (strcmpNoCase(verif, "NO") || strcmpNoCase(verif, "N"));
    }
    return name;
} //Select name for player.

bool selectClassCharacter(int round) {
    if (round) {
        std::string select { "" };
        std::cout << "What is your class ?" << std::endl << "class :" << std::endl << "1) Warrior" << std::endl << "2) Wizard" << std::endl;
        while (true) {
            while (!(std::cin >> select))
                errorCin();
            select = searchCase(select);
            if (select == "warrior" || select == "1")
                return WARRIOR;
            else if (select == "wizard" || select == "2")
                return WIZARD;
            else
                errorCin();
        }
    }
    else
        return true;
         
}

int idMonsterSelect(int level) {
    int id;
    int rng = rand() % 100;
    if (rng <= 10)
        id = MINOTAURE;
    else if (rng <= 30)
        id = OGRE;
    else if (rng <= 50)
        id = ORC;
    else if (rng <= 75)
        id = GOBLIN;
    else
        id = GNOME;

    if (level < 5 && id > GNOME)
        id = GNOME;
    else if (level < 10 && id > GOBLIN)
    id = GOBLIN;
    else if (level < 15 && id > ORC)
        id = ORC;
    else if (level < 20 && id > OGRE)
        id = OGRE;
    return id;
}

int levelMonsterSelect(int levelPlayer) {
    int level;
    level = rand() % (5000 - 1000) + 1000;
    level /= 1000;
    return level + levelPlayer;
}

std::string alignInformation(int a, int b) {
    int c = CONSOLE_SIZE_X;
    c -= a + b;
    return std::string(c, ' ');
}

bool gameOver() {
    std::string select {""};

    system("cls");
    std::cout << "Game over, do you want restart the game ? (Yes/No) : ";
    while (!(std::cin >> select) && (!strcmpNoCase(select, "Y")) && (!strcmpNoCase(select, "YES")) && (!strcmpNoCase(select, "NO")) && (!strcmpNoCase(select, "N")))
        errorCin();
    if (strcmpNoCase(select, "YES") || strcmpNoCase(select, "Y"))
        return true;
    else
        return false;
}

bool aleaClass() {
    int level = rand() % (100 - 0) + 0;
    if (level >= 50)
        return WIZARD;
    else
        return WARRIOR;
    return WARRIOR;
}

void displayInterface(Fighter& player, Fighter& enemy) {
    system("cls");
    system("mode con cols=128 lines=32");

    std::cout << player.nameDisplay() << alignInformation(std::size(player.nameDisplay()), std::size(enemy.nameDisplay())) << enemy.nameDisplay() << std::endl;
    std::cout << player.classCharacterDisplay() << alignInformation(std::size(player.classCharacterDisplay()), std::size(enemy.classCharacterDisplay())) << enemy.classCharacterDisplay() << std::endl;
    std::cout << player.healthDisplay() << alignInformation(std::size(player.healthDisplay()), std::size(enemy.healthDisplay())) << enemy.healthDisplay() << std::endl;
    std::cout << player.manaDisplay() << alignInformation(std::size(player.manaDisplay()), std::size(enemy.manaDisplay())) << enemy.manaDisplay() << std::endl;
    std::cout << player.levelDisplay() << alignInformation(std::size(player.levelDisplay()), std::size(enemy.levelDisplay())) << enemy.levelDisplay() << std::endl;
    std::cout << player.WeaponDisplay() << alignInformation(std::size(player.WeaponDisplay()), std::size(enemy.WeaponDisplay())) << enemy.WeaponDisplay() << std::endl;
    std::cout << player.PotionDisplay() << alignInformation(std::size(player.PotionDisplay()), std::size(enemy.PotionDisplay())) << enemy.PotionDisplay() << std::endl;
    std::cout << "Money : " << player.ascendMoney() << " gold" << std::endl;
    std::cout << std::endl << std::endl << std::string((128 / 2), ' ') << "ACTION :" << std::endl;
    std::cout << std::string((128 / 7), ' ') << ATTACK << " (A)" << std::string((128 / 7), ' ') << MAGIC << " (M)" << std::string((128 / 7), ' ') << USE_POTION << " (P)" << std::string((128 / 7), ' ') << EXIT << " (E)";
    std::cout << std::endl << std::string(128 / 3, ' ') << SAVE << std::string(128 / 3, ' ') << LOADS;

    std::cout << std::string(5, '\n') << std::string(128, '-') << std::endl;
}

bool magicPlayerChoose(Fighter& player, Fighter& enemy) {
    bool programLaunched = true, verifyErrorSelect = false;
    std::string select = { "" };

    do {
        std::cout << player.manaDisplay() << std::endl;
        std::cout << "Please choose a spell or quit :" << std::string(2, '\n');
        std::cout << std::string((128 / 6), ' ') << FIRE << " (F)" << std::string((128 / 6), ' ') << HEALTH << " (H)"<< std::string((128 / 6), ' ') << EXIT << " (E)";
        std::cout << std::string(3, '\n') << std::string(128, '-') << std::endl;

    
        verifyErrorSelect = false;
        while (!(std::cin >> select))
            errorCin();
        system("cls");
        if (strcmpNoCase(select, "EXIT") || strcmpNoCase(select, "E")) {
            displayInterface(player, enemy);
            return true;
        }
        else if (strcmpNoCase(select, "FIRE") || strcmpNoCase(select, "F")) {
            if (player.fire(enemy)) {

                std::cout << "ERROR : You don't have enough mana !" << std::endl;
                verifyErrorSelect = true;
            }
        }
        else if (strcmpNoCase(select, "HEALTH") || strcmpNoCase(select, "H")) {
            if (player.health()) {
                std::cout << "ERROR : You don't have enough mana !" << std::endl;
                verifyErrorSelect = true;
            }
        }
        else {
            verifyErrorSelect = true;
            errorCin();
        }
    } while (verifyErrorSelect);

    return false;
}

int bossComing(int level) {
    switch (level) {
        case 5:
            return 1;
            break;
        case 10:
            return 2;
            break;
        case 15:
            return 3;
            break;
        case 20:
            return 4;
            break;
        case 25:
            return 5;
            break;
    }
    return 0;
}

bool errorSave() {
    std::ifstream save{ "save.sfile" };
    if (save)
        return true;
    else {
        std::string x { "" };
        std::cout << "ERROR : The save file is non-existent or corrupted" << std::endl;
        system("pause");
        return false;
    }
}

void errorCinStart() {
    std::cout << "Error, please try again";
    std::cin.clear();
    std::cin.ignore(255, '\n');
}

bool start() {
    std::string select = { "" };
    do {
        system("cls");
        std::cout << "1.1" << std::string(5, ' ') << std::string(128 - 16, '-') << std::string(8, ' ');
        std::cout << std::string(8, ' ') << "|" << std::string(110, ' ') << "|" << std::string(8, ' ');
        std::cout << std::string(8, ' ') << "|" << std::string(52, ' ') << "Fight RPG" << std::string(49, ' ') << "|" << std::string(8, ' ');
        std::cout << std::string(8, ' ') << "|" << std::string(47, ' ') << "Creator : Skalefou" << std::string(45, ' ') << "|" << std::string(8, ' ');
        std::cout << std::string(8, ' ') << "|" << std::string(110, ' ') << "|" << std::string(8, ' ');
        std::cout << std::string(8, ' ') << std::string(128 - 16, '-') << std::string(8, ' ');
        std::cout << std::string(5, '\n');
        std::cout << std::string(56, ' ') << "1) New (N)" << std::string(56, ' ');
        std::cout << std::string(62, ' ') << "2) Load (L)" << std::string(55, ' ');
        std::cout << std::string(3, '\n') << std::string(56, ' ');
    
            while (!(std::cin >> select)) {
                std::cout << std::endl << std::string(56, ' ');
                errorCinStart();
                std::cout << std::endl << std::string(56, ' ');
            }
            select = searchCase(select);
            if (select == "1" || select == "new")
                return NEW;
            else if (select == "2" || select == "load" && errorSave())
                return LOAD;
            else {
                std::cout << std::endl << std::string(56, ' '); 
                errorCinStart();
                std::cout << std::endl << std::string(56, ' ');
        }
    } while (true);
}

bool save(Fighter& player, Fighter& enemy, int& round) {
    std::string select { "" };
    bool errorSelect, toSave;
    system("mode con cols=128 lines=32");
    system("cls");
    std::cout << "Are you sure you want to save ? (Yes/No) : ";
    do {
        errorSelect = false;
        while (!(std::cin >> select))
            errorCin();
        if (strcmpNoCase(select, "YES") || strcmpNoCase(select, "Y"))
            toSave = true;
        else if (strcmpNoCase(select, "NO") || strcmpNoCase(select, "NO")) {
            system("cls");
            displayInterface(player, enemy);
            return true;
        }
        else {
            errorCin();
            errorSelect = true;
        }
    } while (errorSelect);

    std::ofstream save { "save.sfile" };
    save << round << "\n";
    player.saveFile(save);
    save << "\n";
    enemy.saveFile(save);
    system("cls");
    displayInterface(player, enemy);
    return true;
}

bool load(Fighter& player, Fighter& enemy, int& round) {

    std::string select{ "" };
    bool errorSelect, toSave;
    system("mode con cols=128 lines=32");
    system("cls");
    std::cout << "Are you sure you load the last save ? (Yes/No) : ";
    do {
        errorSelect = false;
        while (!(std::cin >> select))
            errorCin();
        if (strcmpNoCase(select, "YES") || strcmpNoCase(select, "Y"))
            toSave = true;
        else if (strcmpNoCase(select, "NO") || strcmpNoCase(select, "N")) {
            system("cls");
            displayInterface(player, enemy);
            return true;
        }
        else {
            errorCin();
            errorSelect = true;
        }
    } while (errorSelect);

    std::ifstream save { "save.sfile" };
    if (!(errorSave())) {
        system("cls");
        displayInterface(player, enemy);
        return true;
    }
    save >> round;
    player.loadFile(save);
    enemy.loadFile(save);
    system("cls");
    displayInterface(player, enemy);
    return true;
}

void loadRound(int& round) {
    std::ifstream save{ "save.sfile" };
    save >> round;
}

int main()
{
    strcmpNoCase("Salut", "Bateau");
    srand(time(NULL));
    system("mode con cols=128 lines=32");

    bool chooseGame = start();
    system("cls");
    Fighter player(selectClassCharacter(chooseGame), selectName(chooseGame), chooseGame);
    Fighter enemy(idMonsterSelect(player.ascendLevel()), levelMonsterSelect(player.ascendLevel()), aleaClass(), chooseGame);
    Seller seller;
    std::string select { "" };
    int round = 1;
    bool verifySelectError, programLaunched = true;

    if (!(chooseGame))
        loadRound(round);

    while (programLaunched) {
        do {
            displayInterface(player, enemy);
            verifySelectError = false;
            while (!(std::cin >> select))
                errorCin();
            system("cls");
            select = searchCase(select);
            if (select == "attack")
                player.attack(enemy);
            else if (select == "magic")
                verifySelectError = magicPlayerChoose(player, enemy);
            else if (select == "potion")
                player.usePotion();
            else if (select == "save")
                verifySelectError = save(player, enemy, round);
            else if (select == "load")
                verifySelectError = load(player, enemy, round);
            else if (select == "exit")
                programLaunched = false;
            else {
                verifySelectError = true;
                errorCin();
            }
        } while (verifySelectError);
        if (!(programLaunched))
            break;

        if (enemy.isLive()) {
            enemy.actionEnemy(player);
            system("pause");
        }
        else {
            system("pause");
            player.gainExperience(enemy);
            int i = bossComing(player.ascendLevel());
            if (i == 0)
                enemy.changeEnemy(idMonsterSelect(player.ascendLevel()), levelMonsterSelect(player.ascendLevel()), aleaClass());
            else
                enemy.bossLoad(i);

            
            seller.alea(player, round);
            round++;
        }
        if (!(player.isLive())) {
            programLaunched = gameOver();
            if (programLaunched) {
                player.resetPlayer(selectClassCharacter(NEW), selectName(NEW));
                enemy.changeEnemy(idMonsterSelect(player.ascendLevel()), levelMonsterSelect(player.ascendLevel()), aleaClass());
                round = 1;
            }
        }
    }
    return false;
}

//g++ -s -static-libstdc++ -static-libgcc -std=c++17 rpg.cpp fighter.cpp weapon.cpp seller.cpp -o rpg 
