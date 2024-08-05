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
        config::Config configuration("example_configuration.txt");

        // Test case 2: Assuming there are 3 key-value pairs in the config file
        assert(configuration.configMap.size() == 4);

        // Test case 3: Check if parameter values are retrieved correctly
        assert(configuration.configMap.at("pi") == "3.14159265359");
        assert(configuration.configMap.at("useGravity") == "true");
        assert(configuration.configMap.at("speed_of_light") == "299792458");
        assert(configuration.configMap.at("path") == "/home/user/data");

        // Test case 4: Check if parameter values are converted correctly
        double pi = convertToType<double>(configuration.configMap.at("pi"));
        assert(pi == 3.14159265359);

        bool useGravity = convertToType<bool>(configuration.configMap.at("useGravity"));
        assert(useGravity == true);

        std::string path = convertToType<std::string>(configuration.configMap.at("path"));
        assert(path == std::string("/home/user/data"));

        int speedOfLight = convertToType<int>(configuration.configMap.at("speed_of_light"));
        assert(speedOfLight == 299792458);

        // Test case 5: Check if the public api works correctly
        assert(configuration.getParameter<double>("pi") == 3.14159265359);
        assert(configuration.getParameter<bool>("useGravity") == true);
        assert(configuration.getParameter<std::string>("path") == std::string("/home/user/data"));
        assert(configuration.getParameter<int>("speed_of_light") == 299792458);

        std::cout << "All tests passed!" << std::endl;
    }
}

int main()
{
    config::UnitTest test;
    test.testConfig();
    return 0;
}