#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <vector>
#include <type_traits>

namespace configkit
{
    class Config
    {
        std::string configurationFileContent;
        std::filesystem::path configurationPath;
        void readConfigurationFile();
        void populateConfigMap();
        std::string trim(const std::string &str);
        void parseLine(std::string line, int lineNumber);
        std::unordered_map<std::string, std::string> configMap;
        friend class UnitTest;
        std::string removeComments(const std::string &line);
        std::string getParameterFromMap(const std::string &parameterName);
        void initialize();

        const std::unordered_set<char> commentDelimiters = {'#', '[', ';'};
        const char delimiter = '=';

    public:
        Config(std::string configurationPath);
        template <typename T>
        T getParameter(const std::string &parameterName);
    };

    template <typename T>
    struct is_vector : std::false_type
    {
    };

    template <typename T, typename Alloc>
    struct is_vector<std::vector<T, Alloc>> : std::true_type
    {
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
        else if constexpr (is_vector<T>::value)
        {
            using ElementType = typename T::value_type;
            std::vector<ElementType> result;

            // Use a string stream to split the value string into tokens
            std::istringstream stream(value);
            std::string token;

            // Split the string by spaces and convert each token
            while (stream >> token)
            {
                // Convert each token to the vector's element type and add to the vector
                result.push_back(convertToType<ElementType>(token));
            }
            return result;
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