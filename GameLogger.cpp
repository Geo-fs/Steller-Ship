
#include "GameLogger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

GameLogger::GameLogger() {
    logFile.open("Savedgame/GameLog.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

GameLogger::~GameLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

GameLogger& GameLogger::getInstance() {
    static GameLogger instance;
    return instance;
}

void GameLogger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] "
            << "[" << logLevelToString(level) << "] "
            << message << std::endl;
    }
}

std::string GameLogger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf;
#ifdef _WIN32
    localtime_s(&buf, &in_time_t);
#else
    localtime_r(&in_time_t, &buf);
#endif
    std::ostringstream ss;
    ss << std::put_time(&buf, "%Y-%m-%d %X");
    return ss.str();
}

std::string GameLogger::logLevelToString(LogLevel level) {
    switch (level) {
    case LogLevel::INFO:    return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERROR:   return "ERROR";
    case LogLevel::DEBUG:   return "DEBUG";
    default:                return "UNKNOWN";
    }
}
