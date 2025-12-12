#include "logger.hpp"
#include <filesystem>

namespace fs = std::filesystem;

Logger *Logger::instance = nullptr;

Logger::Logger(Level level, std::string filePath) : level(level), logFile(nullptr)
{
    if (!filePath.empty())
    {
        {
            try
            {
                fs::path p(filePath);
                auto dir = p.parent_path();
                if (!dir.empty())
                {
                    std::error_code ec;
                    if (!fs::exists(dir) && !fs::create_directories(dir, ec))
                    {
                        std::cerr << "Failed to create log directory: " << dir << " (" << ec.message() << ")." << std::endl;
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Logger: exception while creating directories: " << e.what() << std::endl;
            }
            fileStream = std::make_unique<std::ofstream>(filePath, std::ios::out | std::ios::trunc);
        }
        if (!fileStream->is_open())
        {
            std::cerr << "Failed to open log file: " << filePath << ". Logging to standard output instead." << std::endl;
            logFile.rdbuf(std::cout.rdbuf());
        }
        else
        {
            logFile.rdbuf(fileStream->rdbuf());
        }
    }
    else
    {
        // Default to standard output
        logFile.rdbuf(std::cout.rdbuf());
    }
}

void Logger::initialize(Level level, std::string filePath)
{
    if (instance == nullptr)
    {
        instance = new Logger(level, filePath);
        instance->logFile << std::endl
                          << "Logger initialized. Logging level: " << static_cast<int>(level) << std::endl;
    }
}

void Logger::log(const std::string &message, Level msgLevel)
{
    if (instance == nullptr)
    {
        std::cerr << "Logger not initialized. Call Logger::initialize() first." << std::endl;
        return;
    }

    if (msgLevel >= instance->level)
    {
        switch (msgLevel)
        {
        case DEBUG:
            instance->logFile << "[DEBUG]: " << message << std::endl;
            break;
        case INFO:
            instance->logFile << "[INFO]: " << message << std::endl;
            break;
        case WARNING:
            instance->logFile << "[WARNING]: " << message << std::endl;
            break;
        case ERROR:
            instance->logFile << "[ERROR]: " << message << std::endl;
            break;
        default:
            instance->logFile << "[UNKNOWN LEVEL]: " << message << std::endl;
            break;
        }
    }
}

void Logger::destroy()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}