#include "../include/configkit/config.h"

namespace configkit
{

    Config::Config(std::string configurationPath)
        : configurationPath(configurationPath)
    {
        initialize();
    }

    void Config::initialize()
    {
        readConfigurationFile();
        populateConfigMap();
    }

    void Config::populateConfigMap()
    {
        std::istringstream configurationStream(configurationFileContent);
        std::string line;
        int lineNumber = 0;

        std::function<void(const std::string &)> processLine = [this, &lineNumber](const std::string &line)
        {
            lineNumber++;
            parseLine(line, lineNumber);
        };

        while (std::getline(configurationStream, line))
        {
            processLine(line);
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
        line = trim(line); // Remove leading and trailing whitespaces

        if (line.empty())
        {
            return;
        }

        if (commentDelimiters.find(line[0]) != commentDelimiters.end())
        {
            return;
        }

        line = removeComments(line);

        size_t delimiterPosition = line.find(delimiter);

        if (delimiterPosition == std::string::npos)
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Missing delimiter '" + delimiter + "' in line: '" + line + "'");
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

        // Check for duplicate keys
        if (configMap.find(leftHandSide) != configMap.end())
        {
            throw std::runtime_error("Error in configuration file at line " + std::to_string(lineNumber) + ": Duplicate key '" + leftHandSide + "' found");
        }

        configMap[leftHandSide] = rightHandSide;
    }

    std::string Config::getParameterFromMap(const std::string &parameterName)
    {
        try
        {
            return configMap.at(parameterName);
        }
        catch (const std::out_of_range &)
        {
            throw std::runtime_error("Parameter not found: " + parameterName);
        }
    }

    void Config::readConfigurationFile()
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