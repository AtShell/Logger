#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<chrono>

class LoggerStrategy {
public:
    virtual void write(const std::string& message) = 0;
};

class LogContext {
private:
    LoggerStrategy* strategy;
public:
    void setStrategy(LoggerStrategy* strategy) {
        this->strategy = strategy;
    }
    void executeStrategy(std::string& message) {
        strategy->write(message);
    }
};

class ConsoleLogger : public LoggerStrategy
{
public:
    void write(const std::string& message) override {
        std::cout << message << "\n";
    }
};

class SimpleFileLogger : public LoggerStrategy
{
    void write(const std::string& message) override {
        std::ofstream LogFile;
        LogFile.open("Log.txt", std::ios::app);
        if (LogFile.is_open())
            LogFile << message << "\n";
        LogFile.close();
    }
};

class TimedFileLogger : public LoggerStrategy
{
    void write(const std::string& message) override {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        std::ofstream LogFile;
        LogFile.open("Log.txt", std::ios::app);
        if (LogFile.is_open())
            LogFile <<message << " DateTime: " << std::ctime(&t_c) << "\n";
        LogFile.close();
    }
};
int main()
{
    std::string message = "This message for log";
    LogContext context;
    ConsoleLogger logConsole;
    SimpleFileLogger logSimpleFile;
    TimedFileLogger logTimedFile;

    context.setStrategy(&logConsole);
    context.executeStrategy(message);

    context.setStrategy(&logSimpleFile);
    context.executeStrategy(message);

    context.setStrategy(&logTimedFile);
    context.executeStrategy(message);
    return 0;
}