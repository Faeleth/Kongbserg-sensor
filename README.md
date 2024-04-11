<h1 align="center">Kongsberg sensor symulator</h1>

<p align="center">
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="https://github.com/Faeleth" target="_blank">Author</a>
</p>

<br>

## :white_check_mark: About The Project 📝 ##

The project allows for the creation of multiple instances of sensor simulators, with the number determined by the sensors configured in the configuration file. Each sensor simulator generates random readings within specified ranges and frequencies.

For example, a configuration file may specify the creation of:

Speed Sensors: Generating readings within the range <-10; 100> with a frequency of 2 Hz.
Position Sensors: Generating readings within the range <-10000; 10000> with a frequency of 1 Hz.
Depth Sensors: Generating readings within the range <0; 255> with a frequency of 10 Hz.

The number and parameters of these sensors are configurable via the configuration file, allowing for flexibility and scalability.

A classifier is implemented to assess the quality of each reading based on predefined intervals.

The simulators transmit readings in a standardized format known as telegrams. Each telegram follows the pattern: $FIX, [ID], [TYPE], [VALUE], [QUALITY]*. For example: $FIX, 3, Depth, 129, Normal*.

Initially, telegrams are displayed directly on the console. However, the program can be modified to send telegrams to receivers instead. Receivers are responsible for receiving, decoding, and presenting telegrams in a readable format. Additionally, telegrams classified as Warning or Alarm are highlighted.

To enhance flexibility and maintainability, the program reads sensor parameters and receiver configurations from separate JSON files (sensorConfig.json and a new configuration file for receivers, respectively).

Finally, the program is designed to be easily extensible, allowing for the addition of new sensors or receivers without significant code modifications. This ensures scalability and ease of maintenance.


## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com), [CMake](https://cmake.org/) and [Boost](https://www.boost.org/) installed. You also need a C++ compiler supporting at least C++14 standard.

For Ubuntu/Debian-based systems, you can install Boost using the following command:

```bash
$ sudo apt-get install libboost-all-dev
```

## :checkered_flag: Starting ##

```bash
# Clone this project
$ git clone https://github.com/Faeleth/Kongbserg-sensor.git

# Access the project directory
$ cd Kongsberg-sensor

# Create a build directory and navigate into it
$ mkdir build && cd build

# Generate the build files using CMake
$ cmake ..

# Build the project
$ cmake --build .

# Run server side
$ ./kongsberg_sensor_server ../config/sensorConfig.json

# Run client side
$ ./kongsberg_sensor_client ../config/receiverConfig.json
```

<a href="#top">Back to top</a>
