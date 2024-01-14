#include <niu2x/logger.h>

namespace niu2x {

Logger& default_logger = *Logger::get();
Logger& logger = default_logger;
}