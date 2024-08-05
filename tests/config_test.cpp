#include "../include/config.h"
#include <cassert>

namespace config
{
    class UnitTest
    {
    public:
        void testConfig();
    };

    void UnitTest::testConfig()
    {
        // Test case 1: Check if configuration file is loaded correctly
        config::Config configuration("config.txt");

        double piConverted = config::convertToType<double>(configuration.getParameter("pi"));

        int NConverted = config::convertToType<int>(configuration.getParameter("N"));

        bool useGravityConverted = config::convertToType<bool>(configuration.getParameter("useGravity"));

        std::cout << "pi = " << piConverted << std::endl;
        std::cout << "N = " << NConverted << std::endl;
        std::cout << "useGravity = " << useGravityConverted << std::endl;
        std::cout << "speed_light = " << configuration.getParameter("speed_light") << std::endl;

        assert(configuration.configMap.size() == 4); // Assuming there are 3 key-value pairs in the config file

        // Test case 2: Check if parameter values are retrieved correctly
        assert(configuration.configMap.at("pi") == "3.14159265359");
        assert(configuration.configMap.at("useGravity") == "true");
        assert(configuration.configMap.at("speed_light") == "299792458.0");

        // Test case 3: Check if parameter values are converted correctly
        double pi = convertToType<double>(configuration.configMap.at("pi"));
        assert(pi == 3.14159265359);

        int N = convertToType<int>(configuration.configMap.at("N"));
        assert(N == 1);

        bool useGravity = convertToType<bool>(configuration.configMap.at("useGravity"));
        assert(useGravity == true);
    }
}

int main()
{
    config::UnitTest test;
    test.testConfig();
    return 0;
}