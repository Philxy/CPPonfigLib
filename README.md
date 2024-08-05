# CPPonfigLib

CPPonfigLib simplifies managing constants, paths, and parameters for C++ applications, ensuring easy and maintainable configuration.

## Features

- Easy parsing of configuration files
- Support for common data types: int, double, bool, and string
- Simple and intuitive API

## Example Configuration File

Here's an example of what your configuration file might look like:

```
# Important Parameters:
speed_of_light = 299792458     # in meters per second
useGravity = true
pi = 3.14159265359
path = /home/user/data
```

Below is an example of how to use the API with the provided configuration file:

```cpp
#include "configkit/config.h"
#include <string>

int main() {
    // Load configuration file
    configkit::Config configuration("example_configuration.txt");

    // Retrieve and convert parameters
    double pi = configuration.getParameter<double>("pi");
    bool useGravity = configuration.getParameter<bool>("useGravity");
    std::string path = configuration.getParameter<std::string>("path");
    int speedOfLight = configuration.getParameter<int>("speed_of_light");

    // Use the parameters
    std::cout << "Pi: " << pi << std::endl;
    std::cout << "Use Gravity: " << std::boolalpha << useGravity << std::endl;
    std::cout << "Path: " << path << std::endl;
    std::cout << "Speed of Light: " << speedOfLight << " m/s" << std::endl;

    return 0;
}
```
