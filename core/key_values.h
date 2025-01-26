#ifndef HOOHAHA_CORE_KEY_VALUES_H_
#define HOOHAHA_CORE_KEY_VALUES_H_

#include <unordered_set>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace core
{

class KeyValues
{
public:
    using Set = std::unordered_set<KeyValues>;
    using ConstIterator = Set::const_iterator;

    using StringArray = std::vector<std::string>;
    using IntArray = std::vector<int>;
    using FloatArray = std::vector<float>;

public:
    KeyValues(std::string_view key);
    KeyValues(const KeyValues&) = delete;
    KeyValues(KeyValues&&) = delete;

    bool LoadFromString(std::string_view str);

    std::string GetKey() const;

    int GetInt(std::string_view key, int default_value) const;
    float GetFloat(std::string_view key, float default_value) const;
    std::string GetString(std::string_view key, std::string_view default_value) const;

    StringArray GetStringArray(std::string_view key) const;
    IntArray GetIntArray(std::string_view key) const;
    FloatArray GetFloatArray(std::string_view key) const;

    int GetStringArraySize(std::string_view key) const;
    int GetIntArraySize(std::string_view key) const;
    int GetFloatArraySize(std::string_view key) const;

    const std::string* GetStringArrayPtr(std::string_view key) const;
    const int* GetIntArrayPtr(std::string_view key) const;
    const float* GetFloatArrayPtr(std::string_view key) const;

    ConstIterator FindKey(std::string_view key) const;
    ConstIterator Begin() const;
    ConstIterator End() const;

    // for backward compatibility with range based iterators
    ConstIterator begin() const;
    ConstIterator end() const;

    KeyValues& operator = (const KeyValues&) = delete;
    KeyValues& operator = (KeyValues&&) = delete;

    bool operator < (const KeyValues& rhs) const;
    bool operator > (const KeyValues& rhs) const;
    bool operator == (const KeyValues& rhs) const;
    bool operator != (const KeyValues& rhs) const;

private:
    std::string ReadToken(std::string_view::const_iterator& begin,
                          std::string_view::const_iterator end) const;

private:
    using Variant = std::variant<
        std::string,
        int,
        float,
        StringArray,
        IntArray,
        FloatArray>;

    enum class Type
    {
        kSet,
        kString,
        kInt,
        kFloat,
        kStringArray,
        kIntArray,
        kFloatArray
    };

    std::string m_key;

    Type    m_type;
    Variant m_value;
    Set     m_set;
};

}

#endif // HOOHAHA_CORE_KEY_VALUES_H_
