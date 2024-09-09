#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cstdarg>
#include <vector>
#include "memory/LinearAllocator.hpp"


enum class LogLevel {
    TRACE, 
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};



class Logger{

public:

    static Logger& getInstance();
    static Logger& getInstance(LinearAllocator& allocator, LogLevel threshold);

    
    ~Logger() {}

    void log(LogLevel level, const std::string& message);
    void setLogLevel(LogLevel newLevel) {_threshold = newLevel;}

    // Logging and outputting
    template<typename... Args>
    void logf(LogLevel level, const std::string& format, Args... args) {
        if (level >= _threshold) {
            std::stringstream ss;
            ss << "[" << getLevelName(level) << "] " << formatString(format, args...);
            std::cout << ss.str() << std::endl;
        }
    }

private:

    Logger(LinearAllocator& allocator, LogLevel threshold);

    std::string getLevelName(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    static Logger* _instance;
    static bool _instanceCreated;

    LinearAllocator& _allocator;
    LogLevel _threshold;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Custom format function that supports std::string and pointers
    std::string formatString(const std::string& format, ...) {
        std::vector<char> buffer(1024);
        va_list args;
        va_start(args, format);
        int len = vsnprintf(buffer.data(), buffer.size(), format.c_str(), args);
        va_end(args);

        // Resize buffer if needed
        if (len >= buffer.size()) {
            buffer.resize(len + 1);
            va_start(args, format);
            vsnprintf(buffer.data(), buffer.size(), format.c_str(), args);
            va_end(args);
        }

        return std::string(buffer.data());
    }

    // Overload to handle std::string arguments
    std::string formatString(const std::string& format, const std::string& str) {
        std::string formatted = format;
        size_t pos = formatted.find("%s");
        if (pos != std::string::npos) {
            formatted.replace(pos, 2, str);
        }
        return formatted;
    }

    // Overload to handle pointer arguments
    std::string formatString(const std::string& format, void* ptr) {
        std::stringstream ss;
        ss << std::hex << ptr;
        std::string formatted = format;
        size_t pos = formatted.find("%p");
        if (pos != std::string::npos) {
            formatted.replace(pos, 2, ss.str());
        }
        return formatted;
    }

};


// Since each manager will require the logger, I would imagine that this is a fine place to put it (for now)
class Manager {
public:
    Manager() : _logger(Logger::getInstance()) {}

protected:
    Logger& _logger;
};



