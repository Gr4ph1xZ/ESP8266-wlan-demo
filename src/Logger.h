#include <Arduino.h>

namespace LoggingUtils {

    enum LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL,
        ALL
    };

    class Logger {
    private:
        LogLevel currentLevel;

        void logging(LogLevel level, const String& message) {
            if (level < currentLevel) return;

            String levelStr;
            switch (level) {
                case ALL: levelStr = ""; break;
                case TRACE: levelStr = "TRACE"; break;
                case DEBUG: levelStr = "DEBUG"; break;
                case INFO: levelStr = "INFO"; break;
                case WARNING: levelStr = "WARNING"; break;
                case ERROR: levelStr = "ERROR"; break;
                case FATAL: levelStr = "FATAL"; break;
            }

            if(levelStr.isEmpty()) {
                Serial.println(message);
            }else {
                Serial.println("[" + levelStr + "] " + message);
            }
        }
    public:
        Logger(LogLevel level = INFO) : currentLevel(level) {}

        void trace(const String& message) { logging(TRACE, message); }
        void debug(const String& message) { logging(DEBUG, message); }
        void info(const String& message) { logging(INFO, message); }
        void warning(const String& message) { logging(WARNING, message); }
        void error(const String& message) { logging(ERROR, message); }
        void fatal(const String& message) { logging(FATAL, message); }
        void log(const String& message) { logging(ALL, message); }
    };
}
