#ifndef NIU2X_LOGGER_H
#define NIU2X_LOGGER_H

#include <iostream>
#include <niu2x/singleton.h>
#include <niu2x/std_alias.h>
#include <niu2x/convention.h>

namespace niu2x {

class Logger : public Singleton<Logger> {
public:
    Logger() { }
    Logger& operator<<(const String& value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(const char* value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(bool value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(int value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(NR value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(uint32_t value)
    {
        std::cerr << value;
        return *this;
    }

    Logger& operator<<(double value)
    {
        std::cerr << value;
        return *this;
    }
};

extern Logger& default_logger;

} // namespace niu2x

#endif