#include "Logger.hpp"


// Initializing static members
Logger* Logger::_instance = nullptr;
bool Logger::_instanceCreated = false;


Logger::Logger(LinearAllocator& allocator, LogLevel threshold) : _allocator(allocator), _threshold(threshold) {}

void Logger::log(LogLevel level, const std::string& message) {
    if (level >= _threshold) {
        std::cout<<"["<<getLevelName(level)<<"] "<<message<<std::endl;
    }
}


Logger& Logger::getInstance() {
    if (!_instanceCreated) {
        throw std::runtime_error("Logger has not been initialized with an allocator!");
    }
    return *_instance;
}

Logger& Logger::getInstance(LinearAllocator& allocator, LogLevel threshold) {
    if (!_instanceCreated) {
        void* LoggerMemory = allocator.allocate(sizeof(Logger));
        _instance = new (LoggerMemory) Logger(allocator, threshold);
        _instanceCreated = true;
    }
    return *_instance;
}

