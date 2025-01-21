#include "log.h"

#include <cassert>
#include <chrono>
#include <cstdarg>
#include <ctime>
#include <format>
#include <sstream>
#include <thread>

namespace core
{

Log log;

namespace
{

std::string TimeToString(std::chrono::system_clock::time_point time)
{
    using namespace std::chrono;

    const int bufsize = 32;

    char replybuf[bufsize];
    char buf_datetime[21];
    char buf_millisec[4];
    char buf_timezone[6];

    auto duration = time.time_since_epoch();
    auto sec = duration_cast<seconds>(duration);
    auto millisec = duration_cast<milliseconds>(duration - sec);
    std::time_t tv_sec = sec.count();
    struct tm now;

    localtime_s(&now, &tv_sec);

    std::snprintf(buf_millisec, sizeof(buf_millisec), "%03d", static_cast<int>(millisec.count()));

    std::strftime(buf_datetime, sizeof(buf_datetime), "%FT%T.", &now);
    std::strftime(buf_timezone, sizeof(buf_timezone), "%z", &now);
    std::snprintf(replybuf, bufsize, "%s%s%s", buf_datetime, buf_millisec, buf_timezone);

    return replybuf;
}

inline std::string LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::kFatal:
        return "FATAL";
    case LogLevel::kError:
        return "ERROR";
    case LogLevel::kWarning:
        return "WARN ";
    case LogLevel::kInfo:
        return "INFO ";
    case LogLevel::kDebug:
        return "DEBUG";
    case LogLevel::kTrace:
        return "TRACE";
    default:
        // Actually we'll never get here
        return "NONE ";
    }
}

inline std::string ThreadIdToString(std::thread::id id)
{
    std::ostringstream stream;
    stream << id;
    return stream.str();
}

} // namespace

Log::Log()
    : m_log_level(LogLevel::kInfo)
    , m_log_file(nullptr)
{
}

Log::~Log()
{
    // Oops! Something went wrong and we ditn't close the log file properly...
    assert(!m_log_file);
}

void Log::Initialize(std::string_view path, LogLevel level)
{
    if (path.empty())
    {
        std::puts("Unable to initialize log, invalid parameter passed");
        assert(!path.empty());
        return;
    }

    std::unique_lock<std::recursive_mutex> lock(m_log_mutex);

    if (IsInitialized())
    {
        if (path == m_log_path)
        {
            // change the log level and continue
            m_log_level = level;
            return;
        }

        // reinitialize
        Shutdown();
    }

    auto file = std::fopen(path.data(), "wb");
    if (file == nullptr)
    {
        std::printf("Unable to open log file, error code is %d", errno);
        assert(file);
        return;
    }

    const std::string time = TimeToString(std::chrono::system_clock::now());
    std::fprintf(file, "---------------- log started at %s ----------------", time.c_str());
    std::fputs("\r\n", file);

    m_log_file = file;
    m_log_path = path;
    m_log_level = level;
}

void Log::Shutdown()
{
    std::unique_lock<std::recursive_mutex> lock(m_log_mutex);

    if (IsInitialized())
    {
        const std::string time = TimeToString(std::chrono::system_clock::now());
        std::fprintf(m_log_file, "---------------- log closed at %s ----------------", time.c_str());
        std::fputs("\r\n", m_log_file);

        std::fclose(m_log_file);

        m_log_file = nullptr;
        m_log_path = {};
        m_log_level = LogLevel::kInfo;
    }
}

bool Log::IsInitialized() const
{
    std::unique_lock<std::recursive_mutex> lock(m_log_mutex);
    return m_log_file != nullptr;
}

void Log::LogMessage(LogLevel level, const char* format, ...)
{
    va_list args;
    std::vector<char> buffer;

    if (level > m_log_level)
    {
        return;
    }

    if (!format || !format[0])
    {
        assert(!"invalid parameter passed");
        return;
    }

    const auto log_level_str = LogLevelToString(level);
    const auto date_time_str = TimeToString(std::chrono::system_clock::now());
    const auto thread_id_str = ThreadIdToString(std::this_thread::get_id());

    std::unique_lock<std::recursive_mutex> lock(m_log_mutex);

    if (!IsInitialized())
    {
        return;
    }

    std::fprintf(m_log_file, "[%s][%s][%s] ",
        date_time_str.c_str(), log_level_str.c_str(), thread_id_str.c_str());

    va_start(args, format);
    std::vfprintf(m_log_file, format, args);
    std::fputs("\r\n", m_log_file);
    std::fflush(m_log_file);
    va_end(args);
}

void Log::LogMessage(const char* source, int line,
                     LogLevel level, const char* format, ...)
{
    va_list args;
    std::vector<char> buffer;

    if (level > m_log_level)
    {
        return;
    }

    if (!format || !format[0])
    {
        assert(!"invalid parameter passed");
        return;
    }

    va_start(args, format);
    int length = _vscprintf(format, args);

    if (source && source[0])
    {
        const int source_length = static_cast<int>(std::strlen(source));
        const int line_length = 16;
        length += source_length + line_length;
        buffer.resize(length);
    }

    int bytes_written = std::vsnprintf(&buffer[0], length, format, args);
    va_end(args);

    if (source && source[0])
    {
        format = " : %s(%d)";
        std::snprintf(&buffer[bytes_written], length - bytes_written, format, source, line);
    }

    LogMessage(level, &buffer[0]);
}

}
