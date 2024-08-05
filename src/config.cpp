#include "../include/configkit/config.h"

namespace configkit
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

    std::string Config::removeComments(const std::string &line)
    {
        const char commentDelimiter = '#';
        size_t commentPosition = line.find(commentDelimiter);
        if (commentPosition != std::string::npos)
        {
            return line.substr(0, commentPosition);
        }
        return line;
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

        line = removeComments(line);

        if (delimiterPosition == std::string::npos)
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Missing delimiter '='");
        }

        std::string leftHandSide = trim(line.substr(0, delimiterPosition));
        std::string rightHandSide = trim(line.substr(delimiterPosition + 1, std::string::npos));

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

    std::string Config::getParameterFromMap(const std::string &parameterName)
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