#include "../include/config.h"

namespace config
{

    Config::Config(std::string configurationPath)
        : configurationPath(configurationPath)
    {
        loadConfiguration();
        parseConfiguration();
    }

    void Config::parseConfiguration()
    {
        std::istringstream configurationStream(configurationFileContent);
        std::string line;
        const char delimiter = '=';

        int lineNumber = 0;
        while (std::getline(configurationStream, line))
        {
            lineNumber++;
            parseLine(line, lineNumber);
        }
    }

    void Config::parseLine(std::string line, int lineNumber)
    {
        if (line.empty())
        {
            return;
        }

        if (line[0] == '#')
        {
            return;
        }
        const char delimiter = '=';

        size_t delimiterPosition = line.find(delimiter);

        if (delimiterPosition == std::string::npos)
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Missing delimiter '='");
        }

        std::string leftHandSide = trim(line.substr(0, delimiterPosition));
        std::string rightHandSide = trim(line.substr(delimiterPosition + 1));

        // Check for empty keys or values
        if (leftHandSide.empty())
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Empty key found");
        }
        if (rightHandSide.empty())
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Empty value for key '" + leftHandSide + "'");
        }

        configMap[leftHandSide] = rightHandSide;
    }

    std::string Config::getParameter(std::string parameterName)
    {
        if (configMap.find(parameterName) == configMap.end())
        {
            throw std::runtime_error("Parameter not found: " + parameterName);
        }
        return configMap[parameterName];
    }

    void Config::loadConfiguration()
    {
        std::ifstream configFile(configurationPath);
        if (!configFile.is_open())
        {
            throw std::runtime_error("Could not open configuration file: " + configurationPath.string());
        }

        std::string line;
        while (std::getline(configFile, line))
        {
            configurationFileContent += line + "\n";
        }

        configFile.close();
    }

    std::string Config::trim(const std::string &str)
    {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

}