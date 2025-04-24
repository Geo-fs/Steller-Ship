#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include "GameLogger.h"
static void delay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


class intro {
public:
    void printIntro() {
        std::cout << "Skipping intro...\n";
        delay(2);
    }
    static void printSkippedIntro() {
        std::cout << "Continuing with intro in 3 seconds...\n";
        delay(3);

        std::cout << "Starting Intro sequence...\n";
        delay(1);
        std::cout << "Preparing for launch...\n";
        delay(1);
        std::cout << "Welcome, in this game, the Y and N Keys will be the most used. \n The number keys will control your 10 inventory slots. \n";
        delay(1);
        std::cout << "To fire a weapon, you can press the F key. To drop bombs, you can press the B key.\n";
        delay(1);
        std::cout << "Get Ready For Liftoff! \n \n";
        delay(1);
        std::cout << "You Are A Space Explorer. You Pilot Your Trusty Ships With The Help Of The Outo Computer.\n";
        std::cout << "You Will Start As A Cadet And Slowly Make Your Way To General In The Space Alliance! \n";
        delay(1);
        std::cout << "When You Get To A Planet, Outo Will Ask You What You Want To Do.\n";
        std::cout << "Occasionally, You Will Be Greeted By Alien Ships. When This Happens, Quick Timing Is Key!\n";
        delay(8);

        clearConsole();

        std::cout << "Make Sure To Resize Your Game Console Window To The Center Of The Screen\n \n";
        delay(1);
        std::cout << "I Can't Stay Long.... Good Luck Cadet. \n We All Depend On You. \n Liftoff In: \n";
        delay(1);
        std::cout << "3...\n";
        delay(1);
        std::cout << "2...\n";
        delay(1);
        std::cout << "1...\n";
        delay(3);
        clearConsole();
        std::cout << "*Welcome To Space! I'm Outo The Computer. Lets Go!!! \n";
        delay(3);
    }
    void printMainIntro() {
        std::cout << "Downloading....\n" << std::endl;

        delay(1);

        std::cout << "Awaiting Input: \n" << std::endl;

        delay(1);

        std::string input;
        std::cin >> input;

        std::cout << "Starting: " << input << std::endl;
        delay(1);
        std::cout << "\n Welcome To STELLER-SHIP!!!\n" << std::endl;
        std::cout << "Press 'Y' and enter if you wish to skip the Intro. If not, press any other key and hit enter! Space Exploration Awaits!\n";
    }
};
