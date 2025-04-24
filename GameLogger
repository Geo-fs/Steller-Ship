#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class GameLogger {
public:
    static GameLogger& getInstance();

    void log(const std::string& message, LogLevel level = LogLevel::INFO);

    // Delete copy constructor and assignment operator
    GameLogger(const GameLogger&) = delete;
    GameLogger& operator=(const GameLogger&) = delete;

private:
    GameLogger();  // Private constructor
    ~GameLogger();

    std::ofstream logFile;
    std::mutex logMutex;

    std::string getTimestamp();
    std::string logLevelToString(LogLevel level);
};

#endif // GAMELOGGER_H
