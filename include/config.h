#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <algorithm>

namespace config
{
    class Config
    {
        std::string configurationFileContent;
        std::filesystem::path configurationPath;
        void loadConfiguration();
        void parseConfiguration();
        std::string trim(const std::string &str);
        void parseLine(std::string line, int lineNumber);
        std::unordered_map<std::string, std::string> configMap;
        friend class UnitTest;
        std::string removeComments(const std::string &line);
        std::string getParameterFromMap(const std::string &parameterName);

    public:
        Config(std::string configurationPath);
        template <typename T>
        T getParameter(const std::string &parameterName);
    };

    template <typename T>
    T convertToType(std::string value)
    {
        if constexpr (std::is_same<T, int>::value)
        {
            return std::stoi(value);
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            return std::stod(value); // TODO: check if there is rounding error
        }
        else if constexpr (std::is_same<T, bool>::value)
        {
            return value == "true";
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            return value;
        }
        else
        {
            throw std::runtime_error("Unsupported type");
        }
    }

    template <typename T>
    T Config::getParameter(const std::string &parameterName)
    {
        return convertToType<T>(getParameterFromMap(parameterName));
    }

}