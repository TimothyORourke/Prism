#pragma once

#include <string>

namespace Prism
{

class HttpHeader 
{
public:
    HttpHeader() {}
    HttpHeader(const std::string& name, const std::string& value) : m_Name(name), m_Value(value) {}
    ~HttpHeader() {}

    inline std::string GetName() const { return m_Name; }
    inline std::string GetValue() const { return m_Value; }
    inline void SetName(const std::string& name) { m_Name = name; }
    inline void SetValue(const std::string& value) { m_Value = value; }

    inline std::string ToString() const { return m_Name + ": " + m_Value; }

private:
    std::string m_Name;
    std::string m_Value;
};

}