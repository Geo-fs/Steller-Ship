//
#include "GameLogger.h"

static void delay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


//type
//break
enum class ItemType {
    LaserCannon = 11,
    ShieldGenerator = 12,
    HyperdriveBooster = 13,
    RepairNanobots = 14,
    CloakingDevice = 15,
    TractorBeam = 16,
    EnergyCapacitor = 17,
    QuantumScanner = 18,
    PlasmaTorpedo = 19,
    GravityManipulator = 20,
    AntimatterReactor = 21,
    WormholeGenerator = 22,
    IonThruster = 23,
    NebulaCompass = 24,
    StellarMapper = 25,
    AsteroidDrill = 26,
    FusionReactor = 27,
    CosmicRayDeflector = 28,
    SubspaceCommunicator = 29,
    StasisFieldProjector = 30
};

struct ItemInfo {
    std::string name;
    int itemnumber;
    std::string itemcodeid;
    int levelsAvailable;
    std::string versionUpdated;
    std::string description;
    std::string ability;
    std::string uses;
    int kickback;
    double rarity;

};

//break
class PlanetElement {
public:
    PlanetElement(const std::string& name, const std::vector<std::pair<std::string, int>>& options)
        : name(name), options(options) {
    }

    std::string getName() const { return name; }
    const std::vector<std::pair<std::string, int>>& getOptions() const { return options; }

private:
    std::string name;
    std::vector<std::pair<std::string, int>> options;
};

class PlanetElements {
public:
    PlanetElements() {
        elements.emplace_back("Biome", std::vector<std::pair<std::string, int>>{
            {"Desert", 1},
            { "Jungle", 2 },
            { "Ocean", 3 },
            { "Tundra", 4 },
            { "Mountain", 5 },
            { "Forest", 6 },
            { "Volcanic", 7 },
            { "Cratered", 8 },
            { "Dead", 9 }
        });
        elements.emplace_back("Atmosphere", std::vector<std::pair<std::string, int>>{
            {"Breathable", 1},
            { "Toxic", 2 },
            { "None", 3 }
        });
        elements.emplace_back("Life", std::vector<std::pair<std::string, int>>{
            {"Yes", 1},
            { "No", 2 }
        });
        elements.emplace_back("Civilization", std::vector<std::pair<std::string, int>>{
            {"Yes", 1},
            { "No", 2 }
        });
    }

    const PlanetElement& getElement(const std::string& name) const {
        for (const auto& element : elements) {
            if (element.getName() == name) {
                return element;
            }
        }
        throw std::runtime_error("Element not found");
    }

    int getValueForOption(const std::string& elementName, const std::string& optionName) const {
        const PlanetElement& element = getElement(elementName);
        for (const auto& option : element.getOptions()) {
            if (option.first == optionName) {
                return option.second;
            }
        }
        throw std::runtime_error("Option not found");
    }

private:
    std::vector<PlanetElement> elements;
};

//break

class gameNumber {
private:
    std::string shipName;
    std::vector<ItemInfo> inventory;
    int xp;
    std::random_device rd;
    int roundCount;
    PlanetElements planetElements;
    std::mt19937 gen{ std::random_device{}() };

    std::string generatePlanetName() {
        const std::string consonants = "bcdfghjklmnpqrstvwxyz";
        const std::string vowels = "aeiou";
        std::string name;
        for (int i = 0; i < 5; ++i) {
            name += (i % 2 == 0) ? consonants[gen() % consonants.length()] : vowels[gen() % vowels.length()];
        }
        return name;
    }
    // break 89372g



    // break 32887

    std::unordered_map<ItemType, ItemInfo> itemInfoMap = {
        {ItemType::LaserCannon,{"Laser Cannon", 1, "1.1", 1, "v 1.05", "Fires Blasts Of Energy At Opponents.", "Damage +20", "ALL", 0, 0.20}},
        {ItemType::ShieldGenerator,{"Shield Generator", 2, "1.2", 1, "v 1.05", "Puts Up A Temporary Shield Between You And Your Opponents.", "Shield 5 Seconds", "2", 0, 0.20}},
        {ItemType::HyperdriveBooster,{"Hyperdrive Booster", 3, "1.3", 1, "v 1.05", "Enables 25% More Resources For The Next 2 Planets.", "Resources +25 For 2 Planets", "1", 0, 0.20}},
        {ItemType::RepairNanobots,{"Repair Nanobots", 4, "1.4", 2, "v 1.05", "Fixes Your Ship Fast And Easy!", "Repair +25 For 1 Planet", "1", 0, 0.10}},
        {ItemType::CloakingDevice,{"Cloaking Device", 5, "1.5", 2, "v 1.05", "Enables You To Hide Your Ship For 5 Planets.", "Life = 0 For 5 Planets", "1", 0, 0.10}}, // add an extra } here on down
        {ItemType::TractorBeam,{"Tractor Beam", 6, "1.6", 3, "v 1.05", "Does 50 Damage To Your Opponent.", "Damage +50", "1", 0, 0.10}},
        {ItemType::EnergyCapacitor,{"Energy Capacitor", 7, "1.7", 1, "v 1.05", "Enables Speed Increase By 25.", "Speed +25 For 1 Planet", "1", 0, 0.10}},
        {ItemType::QuantumScanner,{"Quantum Scanner", 8, "1.8", 2, "v 1.05", "Enables 50% More Resources For The Next Planet.", "Resources +50 For 1 Planet", "1", 0, 0.10}},
        {ItemType::PlasmaTorpedo,{"Plasma Torpedo", 9, "1.9", 4, "v 1.05", "Destroys Your Opponent In One Strike.", "Damage +200 For 1 Planet", "1", 30, 0.10}},
        {ItemType::GravityManipulator,{"Gravity Manipulator", 10, "2", 1, "v 1.05", "Decreases The Chance Of Being Spotted By Aliens By 25% For 2 Planets.", "Life = 0 For 2 Planets", "1", 0, 0.10}},
        {ItemType::AntimatterReactor,{"Antimatter Reactor", 11, "2.1", 2, "v 1.05", "Increases Speed By 50 For 3 Planets. Not Available For Battles.", "Speed +50 For 3 Planets. No Battles", "1", 0, 0.10}},
        {ItemType::WormholeGenerator,{"Wormhole Generator", 12, "2.2", 3, "v 1.05", "Lets You Get Away Quick From A Fight.", "Speed +100 For Battles Only", "1", 0, 0.10}},
        {ItemType::IonThruster,{"Ion Thruster", 13, "2.3", 1, "v 1.05", "Does 20 Damage To Your Opponents.", "Damage +20", "1", 0, 0.10}},
        {ItemType::NebulaCompass,{"Nebula Compass", 14, "2.4", 3, "v 1.05", "Enables 50% More Resources For The Next 5 Planets.", "Resources +50 For 5 Planets", "1", 0, 0.10}},
        {ItemType::StellarMapper,{"Stellar Mapper", 15, "2.5", 4, "v 1.05", "Enables 100% More Resources For The Next Planet.", "Resources +100 For 1 Planet", "1", 0, 0.10}},
        {ItemType::AsteroidDrill,{"Asteroid Drill", 16, "2.6", 4, "v 1.05", "Allows You To Hide From An Alien For 10 Seconds.", "Shield 10 Seconds", "1", 0, 0.10}},
        {ItemType::FusionReactor,{"Fusion Reactor", 17, "2.7", 4, "v 1.05", "Increases Speed By 70 For 5 Planets.", "Speed +70 For 5 Planets", "1", 0, 0.10}},
        {ItemType::CosmicRayDeflector,{"Cosmic Ray Deflector", 18, "2.8", 3, "v 1.05", "Increases Health By 20 For The Next 5 Planets.", "Health +20 For 5 Planets", "1", 0, 0.10}},
        {ItemType::SubspaceCommunicator,{"Subspace Communicator", 19, "2.9", 4, "v 1.05", "Allows You To Communicate With Other Players.", "COMMS = ON", "ALL", 0, 0.30}},
        {ItemType::StasisFieldProjector,{"Stasis Field Projector", 20, "3", 2, "v 1.05", "Increases Health By 10 For The Next 8 Planets.", "Health +10 For 8 Planets", "1", 0, 0.10}}
    };

    ItemType getItemType(const int& i) {
        for (auto& eiou : itemInfoMap) {
            if (i == eiou.second.itemnumber)
                return eiou.first;
        }
        return ItemType::NebulaCompass;
    }
    //break-1
    struct ShipStats {
        int damage = 0;
        int shield = 0;
        int resources = 0;
        int speed = 0;
        int health = 0;
    };

    ShipStats currentStats;

    void applyItemEffect(const ItemInfo& item) {
        std::istringstream iss(item.ability);
        std::string effectType, effectValue;
        iss >> effectType >> effectValue;

        int value = std::stoi(effectValue);

        if (effectType == "Damage") {
            currentStats.damage += value;
        }
        else if (effectType == "Shield") {
            currentStats.shield += value;
        }
        else if (effectType == "Resources") {
            currentStats.resources += value;
        }
        else if (effectType == "Speed") {
            currentStats.speed += value;
        }
        else if (effectType == "Health") {
            currentStats.health += value;
        }

        std::cout << "Applied effect: " << item.ability << std::endl;
        std::cout << "Current stats: Damage=" << currentStats.damage
            << ", Shield=" << currentStats.shield
            << ", Resources=" << currentStats.resources
            << ", Speed=" << currentStats.speed
            << ", Health=" << currentStats.health << std::endl;
    }

    ItemType getRandomItem() {
        std::discrete_distribution<> dist(
            { 0.20, 0.20, 0.20, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10,
             0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.30, 0.10 }
        );
        return static_cast<ItemType>(dist(gen) + 11);  // +11 because enum starts at 11
    }

    void useItem(ItemType item) {
        auto it = itemInfoMap.find(item);
        if (it != itemInfoMap.end()) {
            applyItemEffect(it->second);
        }
    }


    //break-1

    /*std::string getRandomItemTwo() {
            std::uniform_real_distribution<> dis(0, 1);
            double randomValue = dis(gen);
            double cumulativeProbability = 0.0;

            for (const auto& item : possibleItems) {
                cumulativeProbability += item.rarity;
                if (randomValue <= cumulativeProbability) {
                    return item.name;
                }
            }

                 return possibleItems.back().name;
        }*/


    std::pair<std::string, int> getRandomElement(const std::string& elementName) {
        const PlanetElement& element = planetElements.getElement(elementName);
        const auto& options = element.getOptions();
        size_t index = gen() % options.size();
        return options[index];
    }

    bool getRandomChance(double probability) {
        return std::uniform_real_distribution<>(0, 1)(gen) < probability;
    }

    void addItemToInventory(ItemInfo iog) {
        inventory.push_back(iog);
        std::cout << "Added " << iog.name << " to inventory." << std::endl;
    }

    /*void displayInventory() {
        std::cout << "INVENTORY: ";
        for (const auto& item : inventory) {
            std::cout << "[" << itemInfoMap[item].name << "] ";
        }
        std::cout << std::endl;
    }*/

    void useInventoryItem(int index) {
        if (index >= 0 && index < inventory.size()) {
            ItemType item = getItemType(inventory[index].itemnumber);
            useItem(item);
            inventory.erase(inventory.begin() + index);
        }
        else {
            std::cout << "Invalid inventory index." << std::endl;
        }
    }


    void displayInventory() {
        std::cout << "INVENTORY: ";
        for (const auto& item : inventory) {
            std::cout << "[" << item.name << "] ";
        }
        std::cout << std::endl;
    }

    bool battleSequence() {
        int alienHealth = 100;
        int playerHealth = 100;

        std::cout << "Battle initiated! Your health: " << playerHealth << ", Alien health: " << alienHealth << "\n";

        while (alienHealth > 0 && playerHealth > 0) {
            std::cout << "\nChoose your action:\n";
            std::cout << "1. Attack\n";
            std::cout << "2. Defend\n";
            std::cout << "3. Use Item\n";

            int choice;
            std::cin >> choice;

            int damage;
            switch (choice) {
            case 1:
                damage = gen() % 20 + 10;
                alienHealth -= damage;
                std::cout << "You dealt " << damage << " damage to the alien!\n";
                break;
            case 2:
                std::cout << "You brace for the alien's attack.\n";
                break;
            case 3:
                if (!inventory.empty()) {
                    std::cout << "Choose an item to use:\n";
                    for (size_t i = 0; i < inventory.size(); ++i) {
                        std::cout << i + 1 << ". " << inventory[i].name << "\n";
                    }
                    int itemChoice;
                    std::cin >> itemChoice;
                    if (itemChoice > 0 && itemChoice <= static_cast<int>(inventory.size())) {
                        std::cout << "You used " << inventory[itemChoice - 1].name << "!\n";
                        if (inventory[itemChoice - 1].name == "Repair Nanobots") {
                            int heal = gen() % 30 + 20;
                            playerHealth = std::min(100, playerHealth + heal);
                            std::cout << "You healed " << heal << " health!\n";
                        }
                        else {
                            damage = gen() % 30 + 20;
                            alienHealth -= damage;
                            std::cout << "You dealt " << damage << " damage to the alien!\n";
                        }
                        inventory.erase(inventory.begin() + itemChoice - 1);
                    }
                    else {
                        std::cout << "Invalid item choice.\n";
                    }
                }
                else {
                    std::cout << "You have no items to use!\n";
                }
                break;
            default:
                std::cout << "Invalid choice. You hesitated and lost your turn!\n";
            }

            if (alienHealth <= 0) {
                std::cout << "You defeated the alien!\n";
                xp += 200;
                std::cout << "You gained 200 XP!\n";
                return true;
            }

            // Alien's turn
            if (choice == 2) {  // Player defended
                damage = gen() % 10 + 5;
            }
            else {
                damage = gen() % 20 + 10;
            }
            playerHealth -= damage;
            std::cout << "The alien attacks and deals " << damage << " damage to you!\n";

            std::cout << "Your health: " << playerHealth << ", Alien health: " << alienHealth << "\n";
        }

        if (playerHealth <= 0) {
            std::cout << "You were defeated by the alien.\n";
            return false;
        }

        return true;  // This line should never be reached, but it's here to satisfy the compiler
    }

public:
    gameNumber() : xp(0), gen(rd()), roundCount(0) {
        shipName = "STELLER-SHIP"; // Can be customized in settings
        inventory.reserve(9);
    }

    bool mainGameLoop(gameNumber* ge) {
        for (roundCount = 0; roundCount < 20; roundCount++) {
            clearConsole();
            std::cout << "Round " << roundCount + 1 << " of 20\n";
            std::cout << "You are hurtling through space on the " << shipName << ".\n";
            std::cout << "You come across a new planet!\n\n";

            std::string planetName = generatePlanetName();
            std::cout << "Outo Computer: Planet " << planetName << "!\n";
            std::cout << "Outo Computer: Do you want to initialize a scan of the planet? (Y/N): ";
            std::string response;
            std::cin >> response;

            if (response == "Y" || response == "y") {
                auto [biomeName, biomeValue] = getRandomElement("Biome");
                std::cout << "Outo Computer: Biome: " << biomeName << " (ID: " << biomeValue << ")\n";

                auto [atmosphereName, atmosphereValue;] = getRandomElement("Atmosphere");
                std::cout << "Atmosphere: " << atmosphereName << " (ID: " << atmosphereValue << ")\n";

                auto [lifeName, lifeValue] = getRandomElement("Life");
                std::cout << "Life: " << lifeName << "\n";

                bool hasLife = (lifeName == "Yes");
                if (hasLife) {
                    auto [civilizationName, civilizationValue;] = getRandomElement("Civilization");
                    std::cout << "Civilization: " << civilizationName << "\n";
                }
                else {
                    std::cout << "Civilization: No\n";
                }

                std::cout << "Resources: Level " << (gen() % 100 + 1) << "\n\n";

                std::cout << "Outo Computer: Do you want to land? (Y/N): ";
                std::cin >> response;

                if (response == "Y" || response == "y") {
                    std::cout << "Descending into the planet.\n";

                    if (hasLife && getRandomChance(0.25)) {
                        std::cout << "Outo Computer: Aliens are ATTACKING!!!! \n\nBATTLE STATIONS!\n";
                        std::cout << "Outo Computer: Do you want to do evasive maneuvers? (Y/N): ";
                        std::cin >> response;

                        if (response == "Y" || response == "y") {
                            std::cout << "Outo Computer: Hold on!\n";
                            delay(3);
                            if (!getRandomChance(0.25)) {
                                std::cout << "Your ship was damaged but you managed to escape.\n";
                                xp -= 50; // Penalty for retreating
                            }
                            else if (!battleSequence()) {
                                std::cout << "You lost the battle but managed to escape.\n";
                                xp -= 100; // Bigger penalty for losing
                            }
                            else {
                                std::cout << "You won the battle!\n";
                                xp += 200;
                            }
                        }
                        else {
                            std::cout << "You decided not to engage and retreated.\n";
                            xp -= 25; // Small penalty for not engaging
                        }
                    }
                    else {
                        std::cout << "Outo Computer: Collecting resources!\n";
                        delay(3);
                        std::cout << "Done! You've earned 100 XP.\n";
                        xp += 100;
                        if (getRandomChance(0.5)) {
                            ItemType newItem = getRandomItem();
                            auto info = itemInfoMap[newItem];
                            std::cout << "You've found a " << info.name << "! Do you want to equip it? (Y/N): ";
                            std::cin >> response;
                            if (response == "Y" || response == "y") {
                                ge->addItemToInventory(info);
                            }
                        }
                    }
                }
                else {
                    std::cout << "You decided not to land on this planet.\n";
                }
            }
            else {
                std::cout << "You decided to skip this planet.\n";
            }

            std::cout << "\n--- End of Round " << roundCount + 1 << " ---\n";
            displayInventory();
            std::cout << "Current XP: " << xp << std::endl;
            std::cout << "Press Enter to continue to the next round...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        std::cout << "You've completed 20 rounds! Game over.\n";
        return true;
    }
};






class mainMenu {
public:
    void printMenu() {
        std::cout << " \n Welcome \n Press 1 For New Game \n Press 2 For Saved Game \n Press 3 For Settings \n Press 4 For Developer Tools \n Press 5 For The About Page \n";
    }
};

class newGameStart {
public:
    bool printStartOptions() {
        clearConsole();

        int selectedShip = 0;
        std::string shipNames[] = { "The Hyperbole", "The Riser-2", "The Sunrise", "Newark", "Winona" };
        std::string shipDescriptions[] = {
            "Fast, Nimble, Light Armor, Machine Guns.",
            "Strong Shields, Laser Cannons, Slow, Hard To Turn",
            "Medium Shields, Overpowered Engines, Small Cannons, Normally Slow",
            "Quick, Small, Fast Engines, Light Guns",
            "Laser Cannons, Fast Engines, No Shields, Quick"
        };

        while (true) {
            std::cout << "\n---------->>> STARTING <<<-----------\n";
            std::cout << "Press 1 Through 5 To Choose Your Starting Ship\n\n";

            for (int i = 0; i < 5; i++) {
                std::cout << i + 1 << ": " << shipNames[i] << " - " << shipDescriptions[i] << "\n";
            }

            std::cout << "\nPlease Select A Ship (1-5) or 0 to Exit: ";
            std::string input;
            std::cin >> input;

            if (input == "0") {
                std::cout << "Exiting ship selection...\n";
                delay(2);
                return false;
            }

            try {
                selectedShip = std::stoi(input);
                if (selectedShip >= 1 && selectedShip <= 5) {
                    std::cout << "\nYou have selected: " << shipNames[selectedShip - 1] << "\n";
                    std::cout << "Confirm selection? (Y/N): ";
                    std::cin >> input;
                    if (input == "Y" || input == "y") {
                        std::cout << "Ship confirmed! Preparing for launch...\n";
                        delay(2);
                        return true;
                    }
                }
                else {
                    std::cout << "Invalid selection. Please choose a number between 1 and 5.\n";
                }
            }
            catch (std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a number.\n";
            }

            delay(2);
            clearConsole();
        }
    }

};

class GameManager {
private:
    mainMenu menu;
    newGameStart gameStart;
    gameNumber* game;

public:
    GameManager() :game(nullptr) {}
    ~GameManager() { delete game; }


    void run() {
        while (true) {
            clearConsole();
            menu.printMenu();

            std::string mainMenuPrint;
            std::cin >> mainMenuPrint;

            try {
                int choice = std::stoi(mainMenuPrint);

                switch (choice) {
                case 1:
                    if (gameStart.printStartOptions()) {
                        std::cout << "Starting the game...\n";
                        delay(2);
                        while (startGame()) {
                            std::cout << "Restarting game...\n";
                            delay(2);
                        }
                    }
                    break;
                case 2:
                    std::cout << "Loading saved game...\n";
                    std::cout << "This Page Does Not Exist\n";
                    run();
                    break;
                case 3:
                    std::cout << "Opening settings...\n";
                    // Add code for settings
                    std::cout << "This Page Does Not Exist\n";
                    run();
                    break;
                case 4:
                    std::cout << "Accessing developer tools...\n";
                    // Add code for developer tools
                    std::cout << "This Page Does Not Exist\n";
                    run();
                    break;

                case 5:
                    std::cout << "About page loading...\n";
                    //add code for the about page
                    intro::printSkippedIntro();
                    break;

                default:
                    std::cout << "Invalid option. Please enter a number between 1 and 5.\n";
                }
            }
            catch (const std::invalid_argument& e) {
                std::cout << "Invalid input. Please enter a number.\n";
            }
            catch (const std::out_of_range& e) {
                std::cout << "Input out of range. Please enter a number between 1 and 4.\n";
            }

            delay(2);
        }
    }

private:
    bool startGame() {
        if (!game) {
            game = new gameNumber();
        }


        clearConsole();
        std::cout << "Initializing game systems...\n";
        delay(2);
        std::cout << "Preparing ship for launch...\n";
        delay(2);
        std::cout << "3...\n";
        delay(1);
        std::cout << "2...\n";
        delay(1);
        std::cout << "1...\n";
        delay(1);
        std::cout << "Liftoff!\n";
        delay(2);
        clearConsole();

        bool gameResult = game->mainGameLoop(game);

        if (!gameResult) {
            std::cout << "Game Over! Do you want to play again? (Y/N): ";
            std::string response;
            std::cin >> response;
            return (response == "Y" || response == "y");
        }

        return false;
    };
};




