#ifndef HOOHAHA_CORE_LOG_H_
#define HOOHAHA_CORE_LOG_H_

#include <cstdio>
#include <mutex>
#include <string>

namespace core
{

enum class LogLevel
{
    kFatal,
    kError,
    kWarning,
    kInfo,
    kDebug,
    kTrace
};

class Log final
{
public:
    Log();
    Log(Log&& other) = delete;
    Log(const Log&) = delete;
    ~Log();

    void Initialize(std::string_view path, LogLevel level);
    void Shutdown();

    bool IsInitialized() const;

    Log& operator=(Log&&) = delete;
    Log& operator=(const Log&) = delete;

    void LogMessage(LogLevel level, const char* format, ...);
    void LogMessage(const char* source, int line,
                    LogLevel level, const char* format, ...);

private:
    std::string                   m_log_path;
    LogLevel                      m_log_level;
    FILE*                         m_log_file;
    mutable std::recursive_mutex  m_log_mutex;
};

extern Log log;

}

#ifdef NDEBUG

#define HOOHAHA_LOG(level, format, ...)                                            \
    { core::log.LogMessage(level, format, __VA_ARGS__); }                          \

#define HOOHAHA_LOG_FATAL(format, ...)                                             \
    HOOHAHA_LOG(core::LogLevel::kFatal, format, __VA_ARGS__)                       \

#define HOOHAHA_LOG_ERROR(format, ...)                                             \
    HOOHAHA_LOG(core::LogLevel::kError, format, __VA_ARGS__)                       \

#define HOOHAHA_LOG_WARN(format, ...)                                              \
    HOOHAHA_LOG(core::LogLevel::kWarning, format, __VA_ARGS__)                     \

#define HOOHAHA_LOG_INFO(format, ...)                                              \
    HOOHAHA_LOG(core::LogLevel::kInfo, format, __VA_ARGS__)                        \

#define HOOHAHA_LOG_DEBUG(format, ...)                                             \
    HOOHAHA_LOG(core::LogLevel::kDebug, format, __VA_ARGS__)                       \

#define HOOHAHA_LOG_TRACE(format, ...)                                             \
    HOOHAHA_LOG(core::LogLevel::kTrace, format, __VA_ARGS__)                       \

#else

#define HOOHAHA_LOG(level, format, ...)                                            \
    { core::log.LogMessage(__FILE__, __LINE__, level, format, __VA_ARGS__); }      \

#define HOOHAHA_LOG_FATAL(format, ...)                                             \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kFatal, format, __VA_ARGS__)   \

#define HOOHAHA_LOG_ERROR(format, ...)                                             \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kError, format, __VA_ARGS__)   \

#define HOOHAHA_LOG_WARN(format, ...)                                              \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kWarning, format, __VA_ARGS__) \

#define HOOHAHA_LOG_INFO(format, ...)                                              \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kInfo, format, __VA_ARGS__)    \

#define HOOHAHA_LOG_DEBUG(format, ...)                                             \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kDebug, format, __VA_ARGS__)   \

#define HOOHAHA_LOG_TRACE(format, ...)                                             \
    HOOHAHA_LOG(__FILE__, __LINE__, core::LogLevel::kTrace, format, __VA_ARGS__)   \

#endif // _NDEBUG

#endif // HOOHAHA_CORE_LOG_H_
