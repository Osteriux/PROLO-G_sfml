#include <iostream>
#include <fstream>
#include <memory>
#include <iostream>

class Logger
{
public:
    enum class Level
    {
        DEBUG = 0,
        INFO = 10,
        WARNING = 20,
        ERROR = 30
    };
    static const Level DEBUG = Level::DEBUG;
    static const Level INFO = Level::INFO;
    static const Level WARNING = Level::WARNING;
    static const Level ERROR = Level::ERROR;

    static void initialize(Level level = ERROR, std::string filePath = "");
    static void destroy();
    static void log(const std::string &message, Level level = ERROR);

private:
    Logger(Level level, std::string filePath = "");
    static Logger *instance;

    Level level;
    std::ostream logFile;
    std::unique_ptr<std::ofstream> fileStream;

    Logger(const Logger &) = delete;            // Delete copy constructor
    Logger &operator=(const Logger &) = delete; // Delete copy assignment operator
};