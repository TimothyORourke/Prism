#pragma once

#include <string>
#include <unordered_map>

namespace Prism
{

class HttpRequest
{
public:

    enum Method {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        INVALID
    };

    HttpRequest() {}
    ~HttpRequest() {}

    inline Method GetMethod() const { return m_Method; }
    inline std::string GetPath() const { return m_Path; }
    inline std::string GetVersion() const { return m_Version; }
    inline void SetMethod(Method method) { m_Method = method; }
    inline void SetPath(const std::string& path) { m_Path = path; }
    inline void SetVersion(const std::string& version) { m_Version = version; }

    std::string GetMethodText() const { return s_MethodTextMap[m_Method]; }
    static std::string GetMethodText(Method method) { return s_MethodTextMap[method]; }

private:
    Method m_Method;
    std::string m_Path;
    std::string m_Version;

    static std::unordered_map<Method, std::string> s_MethodTextMap;
};

}