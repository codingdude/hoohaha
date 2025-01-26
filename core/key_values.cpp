#include "key_values.h"

#include "log.h"

namespace core
{

bool KeyValues::Hash::operator()(const KeyValues& key_values) const
{
    return std::hash<std::string>{}(key_values.GetKey());
}

KeyValues::KeyValues(std::string_view key)
    : m_key(key)
    , m_type(Type::kSet)
{
    if (m_key.empty())
    {
        HOOHAHA_LOG_WARN("KeyValues : key name must not be empty");
        m_key = "(null)";
    }
}

bool KeyValues::LoadFromString(std::string_view str)
{
    HOOHAHA_LOG_FATAL("Unimplemented");
    return false;
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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

    if (m_type == Type::kInt && key == "/")
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
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
        if (key_value_iterator != End())
        {
            return key_value_iterator->GetFloatArrayPtr("/");
        }
    }

    return nullptr;
}

KeyValues::ConstIterator KeyValues::FindKeyValues(
    std::string_view key) const
{
    std::size_t offset = 1;
    std::string first_key, rest_key;

    auto end_iterator = End();

    if (key.size() < 2)
    {
        return end_iterator;
    }

    if (key[0] != '/')
    {
        offset = key.find_first_of('/');
        if (offset == std::string_view::npos)
        {
            return end_iterator;
        }

        first_key = key.substr(0, offset);
        if (first_key != m_key ||
            (key.length() - first_key.length()) < 2)
        {
            return end_iterator;
        }

        offset++;
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
    if (key_values_iterator == end_iterator)
    {
        return key_values_iterator;
    }

    if (rest_key.empty() || rest_key == "/")
    {
        return key_values_iterator;
    }
    
    auto new_key_values_iterator =
        key_values_iterator->FindKeyValues(rest_key);
    if (new_key_values_iterator == key_values_iterator->End())
    {
        return end_iterator;
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
    HOOHAHA_LOG_FATAL("Unimplemented");
    return {};
}

}
