#include "key_values.h"

#include "log.h"

namespace core
{

namespace
{

inline void SkipSpaces(std::string_view::const_iterator& begin,
                       std::string_view::const_iterator end)
{
    while (begin < end && std::strchr(" \r\n\t", *begin))
    {
        begin++;
    }
}

inline void SkipLine(std::string_view::const_iterator& begin,
                     std::string_view::const_iterator end)
{
    while (begin < end && !std::strchr("\n", *begin))
    {
        begin++;
    }
}

} // namespace

bool KeyValues::Hash::operator()(const KeyValues& key_values) const
{
    return std::hash<std::string>{}(key_values.GetKey());
}

KeyValues::KeyValues()
    : m_key("(null)")
    , m_type(Type::kEmpty)
{
}

KeyValues::KeyValues(std::string_view key)
    : m_key(key)
    , m_type(Type::kEmpty)
{
    if (m_key.empty())
    {
        HOOHAHA_LOG_WARN("KeyValues : key name must not be empty");
        m_key = "(null)";
    }
}

void KeyValues::Clear()
{
    m_key.clear();
    m_value = {};
    m_type = Type::kEmpty;
    m_set.clear();
}

bool KeyValues::LoadFromString(std::string_view str)
{
    if (str.empty())
    {
        return false;
    }

    Clear();

    auto begin = str.begin();
    auto end = str.end();

    auto key = ReadToken(begin, end);
    if (key.empty())
    {
        HOOHAHA_LOG_ERROR(
            "Unable to load KeyValues, unvalid parameter passed",
            key.c_str());
        return false;
    }

    auto current = begin;
    if (!SeekControlCharacter(current, end, '{'))
    {
        HOOHAHA_LOG_ERROR(
            "Unable to load KeyValues %s, invalid or corrupted source data",
            key.c_str());
        return false;
    }

    if (!Load(begin, end))
    {
        HOOHAHA_LOG_ERROR("Unable to load KeyValues %s", key.c_str());
        return false;
    }

    m_key = key;

    return true;
}

std::string KeyValues::GetKey() const
{
    return m_key;
}

int KeyValues::GetInt(std::string_view key, int default_value) const
{
    if (key.empty())
    {
        return default_value;
    }

    if (m_type == Type::kInt && key == "/")
    {
        try
        {
            return std::get<int>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted int value for key '%s'",
                m_key.c_str(),
                key.data());
            return default_value;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetInt("/", default_value);
        }
    }

    return default_value;
}

float KeyValues::GetFloat(std::string_view key, float default_value) const
{
    if (key.empty())
    {
        return default_value;
    }

    if (m_type == Type::kFloat && key == "/")
    {
        try
        {
            return std::get<float>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted float value for key '%s'",
                m_key.c_str(),
                key.data());
            return default_value;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetFloat("/", default_value);
        }
    }

    return default_value;
}

std::string KeyValues::GetString(std::string_view key, std::string_view default_value) const
{
    if (key.empty())
    {
        return std::string(default_value);
    }

    if (m_type == Type::kString && key == "/")
    {
        try
        {
            return std::get<std::string>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted string value for key '%s'",
                m_key.c_str(),
                key.data());
            return std::string(default_value);
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetString("/", default_value);
        }
    }

    return std::string(default_value);
}

KeyValues::StringArray KeyValues::GetStringArray(std::string_view key) const
{
    if (key.empty())
    {
        return {};
    }

    if (m_type == Type::kStringArray && key == "/")
    {
        try
        {
            return std::get<StringArray>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted StringArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return {};
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetStringArray("/");
        }
    }

    return {};
}

KeyValues::IntArray KeyValues::GetIntArray(std::string_view key) const
{
    if (key.empty())
    {
        return {};
    }

    if (m_type == Type::kIntArray && key == "/")
    {
        try
        {
            return std::get<IntArray>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted IntArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return {};
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetIntArray("/");
        }
    }

    return {};
}

KeyValues::FloatArray KeyValues::GetFloatArray(std::string_view key) const
{
    if (key.empty())
    {
        return {};
    }

    if (m_type == Type::kFloatArray && key == "/")
    {
        try
        {
            return std::get<FloatArray>(m_value);
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted FloatArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return {};
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetFloatArray("/");
        }
    }

    return {};
}

int KeyValues::GetStringArraySize(std::string_view key) const
{
    if (key.empty())
    {
        return 0;
    }

    if (m_type == Type::kStringArray && key == "/")
    {
        try
        {
            return static_cast<int>(
                std::get<StringArray>(m_value).size());
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted StringArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return 0;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetStringArraySize("/");
        }
    }

    return 0;
}

int KeyValues::GetIntArraySize(std::string_view key) const
{
    if (key.empty())
    {
        return 0;
    }

    if (m_type == Type::kIntArray && key == "/")
    {
        try
        {
            return static_cast<int>(
                std::get<IntArray>(m_value).size());
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted IntArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return 0;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetIntArraySize("/");
        }
    }

    return 0;
}

int KeyValues::GetFloatArraySize(std::string_view key) const
{
    if (key.empty())
    {
        return 0;
    }

    if (m_type == Type::kFloatArray && key == "/")
    {
        try
        {
            return static_cast<int>(
                std::get<FloatArray>(m_value).size());
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted FloatArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return 0;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetFloatArraySize("/");
        }
    }

    return 0;
}

const std::string* KeyValues::GetStringArrayPtr(std::string_view key) const
{
    if (key.empty())
    {
        return nullptr;
    }

    if (m_type == Type::kStringArray && key == "/")
    {
        try
        {
            return std::get<StringArray>(m_value).data();
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted StringArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return nullptr;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetStringArrayPtr("/");
        }
    }

    return nullptr;
}

const int* KeyValues::GetIntArrayPtr(std::string_view key) const
{
    if (key.empty())
    {
        return nullptr;
    }

    if (m_type == Type::kIntArray && key == "/")
    {
        try
        {
            return std::get<IntArray>(m_value).data();
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted IntArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return nullptr;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetIntArrayPtr("/");
        }
    }

    return nullptr;
}

const float* KeyValues::GetFloatArrayPtr(std::string_view key) const
{
    if (key.empty())
    {
        return nullptr;
    }

    if (m_type == Type::kFloatArray && key == "/")
    {
        try
        {
            return std::get<FloatArray>(m_value).data();
        }
        catch (const std::bad_variant_access&)
        {
            HOOHAHA_LOG_ERROR(
                "KeyValues '%s' : inconsistent or corrupted FloatArray value for key '%s'",
                m_key.c_str(),
                key.data());
            return nullptr;
        }
    }

    if (m_type == Type::kSet)
    {
        auto key_value_iterator = FindKeyValues(key);
        if (key_value_iterator != nullptr)
        {
            return key_value_iterator->GetFloatArrayPtr("/");
        }
    }

    return nullptr;
}

const KeyValues* KeyValues::FindKeyValues(
    std::string_view key) const
{
    std::size_t offset = 1;
    std::string first_key, rest_key;

    if (key.size() < 2 || key[0] != '/')
    {
        return nullptr;
    }

    std::size_t new_offset = key.find_first_of('/', offset);
    if (new_offset != std::string_view::npos)
    {
        first_key = key.substr(offset, new_offset - offset);
        rest_key = key.substr(new_offset);
    }
    else
    {
        first_key = key.substr(offset);
    }

    auto key_values_iterator = m_set.find(KeyValues(first_key));
    if (key_values_iterator == m_set.end())
    {
        return nullptr;
    }

    if (rest_key.empty() || rest_key == "/")
    {
        return &(*key_values_iterator);
    }
    
    auto new_key_values_iterator =
        key_values_iterator->FindKeyValues(rest_key);
    if (new_key_values_iterator == nullptr)
    {
        return nullptr;
    }

    return new_key_values_iterator;
}

KeyValues::ConstIterator KeyValues::Begin() const
{
    return m_set.begin();
}

KeyValues::ConstIterator KeyValues::End() const
{
    return m_set.end();
}

KeyValues::ConstIterator KeyValues::begin() const
{
    return m_set.begin();
}

KeyValues::ConstIterator KeyValues::end() const
{
    return m_set.end();
}

bool KeyValues::operator < (const KeyValues& rhs) const
{
    return m_key < rhs.m_key;
}

bool KeyValues::operator > (const KeyValues& rhs) const
{
    return m_key > rhs.m_key;
}

bool KeyValues::operator == (const KeyValues& rhs) const
{
    return m_key == rhs.m_key;
}

bool KeyValues::operator != (const KeyValues& rhs) const
{
    return m_key != rhs.m_key;
}

std::string KeyValues::ReadToken(std::string_view::const_iterator& begin,
                                 std::string_view::const_iterator end) const
{
    std::string buffer;
    bool is_quotted = false;

    SkipSpaces(begin, end);

    for (;;)
    {
        if (begin == end)
        {
            HOOHAHA_LOG_ERROR(
                "Unexpected buffer end while parsing KeyValues '%s'",
                m_key.c_str());
            return "";
        }

        if (*begin == '\"')
        {
            if (is_quotted)
            {
                if (*(begin - 1) != '\\')
                {
                    begin++;
                    return buffer;
                }

                buffer.pop_back();
            }
            else
            {
                is_quotted = true;
                begin++;
                continue;
            }
        }

        if (!is_quotted)
        {
            if (std::strchr(" \r\n{=},", *begin))
            {
                return buffer;
            }

            if (*begin == '/')
            {
                begin++;
                if (begin != end && *begin == '/')
                {
                    SkipLine(begin, end);
                    SkipSpaces(begin, end);
                    continue;
                }

                begin--;
            }
        }

        buffer += *begin++;
    }

    return buffer;
}

bool KeyValues::SeekControlCharacter(std::string_view::const_iterator& begin,
                                     std::string_view::const_iterator end,
                                     char control_char) const
{
    SkipSpaces(begin, end);

    if (begin == end)
    {
        return false;
    }

    while (begin != end && *begin == '/')
    {
        begin++;
        if (begin != end && *begin == '/')
        {
            SkipLine(begin, end);
            SkipSpaces(begin, end);
        }
        else
        {
            return false;
        }
    }

    if (begin == end || *begin != control_char)
    {
        return false;
    }

    begin++;
    return true;
}

bool KeyValues::Load(std::string_view::const_iterator& begin,
                     std::string_view::const_iterator end) const
{
    if (begin == end)
    {
        return false;
    }

    if (SeekControlCharacter(begin, end, '{'))
    {
        Set set;
        while (begin < end)
        {
            auto key = ReadToken(begin, end);
            if (key.empty())
            {
                break;
            }

            if (set.find(KeyValues(key)) != set.end())
            {
                HOOHAHA_LOG_ERROR(
                    "An error occurred while parsing KeyValue '%s',"
                    " key name must be unique",
                    m_key.c_str());
                return false;
            }

            auto nested = set.emplace(key).first;
            if (!nested->Load(begin, end))
            {
                set.clear();
                return false;
            }
        }

        m_type = Type::kSet;
        m_set = std::move(set);
    }
    else if (SeekControlCharacter(begin, end, '='))
    {
        Type prev_type = Type::kEmpty;
        Type next_type = Type::kEmpty;
        
        StringArray str_array;
        IntArray int_array;
        FloatArray flt_array;

        do
        {
            auto token = ReadToken(begin, end);

            if (token.empty())
            {
                return false;
            }

            char *int_ptr, *flt_ptr;
            auto int_val = static_cast<int>(std::strtol(token.c_str(), &int_ptr, 10));
            auto flt_val = std::strtof(token.c_str(), &flt_ptr);

            if (flt_ptr == int_ptr && flt_ptr != token.data())
            {
                int_array.push_back(int_val);
                next_type = Type::kInt;
            }
            else if (int_ptr != token.data())
            {
                flt_array.push_back(flt_val);
                next_type = Type::kFloat;
            }
            else
            {
                str_array.push_back(token);
                next_type = Type::kString;
            }

            if (prev_type == Type::kEmpty)
            {
                prev_type = next_type;
            }

            if (prev_type != next_type)
            {
                HOOHAHA_LOG_ERROR(
                    "An error occurred while parsing KeyValue '%s',"
                    " arrays of different types not supported",
                    m_key.c_str());
                return false;
            }
        }
        while (SeekControlCharacter(begin, end, ','));

        const auto str_array_size = str_array.size();
        const auto int_array_size = int_array.size();
        const auto flt_array_size = flt_array.size();

        if (str_array_size)
        {
            if (str_array_size > 1)
            {
                m_value = str_array;
                m_type = Type::kStringArray;
            }
            else
            {
                m_value = str_array.front();
                m_type = Type::kString;
            }
        }

        if (int_array_size)
        {
            if (int_array_size > 1)
            {
                m_value = int_array;
                m_type = Type::kIntArray;
            }
            else
            {
                m_value = int_array.front();
                m_type = Type::kInt;
            }
        }

        if (flt_array_size)
        {
            if (flt_array_size > 1)
            {
                m_value = flt_array;
                m_type = Type::kFloatArray;
            }
            else
            {
                m_value = flt_array.front();
                m_type = Type::kFloat;
            }
        }
    }

    return true;
}

}
