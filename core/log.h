/*
    Hoohaha Game Engine
    Copyright (C) 2025 codingdude@gmail.com

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

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

#else

#define HOOHAHA_LOG(level, format, ...)                                            \
    { core::log.LogMessage(__FILE__, __LINE__, level, format, __VA_ARGS__); }      \

#endif // _NDEBUG

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

#endif // HOOHAHA_CORE_LOG_H_
