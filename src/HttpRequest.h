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
        HEAD
    };

    HttpRequest();
    ~HttpRequest();

    Method GetMethod() const;
    void SetMethod(Method method);
    std::string GetPath() const;
    void SetPath(const std::string& path);
    std::string GetVersion() const;
    void SetVersion(const std::string& version);

    std::string GetMethodText() const;

private:
    Method m_Method;
    std::string m_Path;
    std::string m_Version;

    static std::unordered_map<Method, std::string> s_MethodTextMap;
};

}