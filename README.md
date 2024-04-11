<h1 align="center">Kongsberg sensor symulator</h1>

<p align="center">
  <a href="#memo-About The Project">About The Project</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="https://github.com/Faeleth" target="_blank">Author</a>
</p>

<br>

## :memo: About The Project ##

The project allows for the creation of multiple instances of sensor simulators, with the number determined by the sensors configured in the configuration file. Each sensor simulator generates random readings within specified ranges and frequencies.

For example, a configuration file may specify the creation of:

Speed Sensors: Generating readings within the range <-10; 100> with a frequency of 2 Hz.
Position Sensors: Generating readings within the range <-10000; 10000> with a frequency of 1 Hz.
Depth Sensors: Generating readings within the range <0; 255> with a frequency of 10 Hz.

The number and parameters of these sensors are configurable via the configuration file, allowing for flexibility and scalability.

A classifier is implemented to assess the quality of each reading based on predefined intervals.

The simulators transmit readings in a standardized format known as telegrams. Each telegram follows the pattern: $FIX, [ID], [TYPE], [VALUE], [QUALITY]*. For example: $FIX, 3, Depth, 129, Normal*.

Telegrams are directly transmitted to receivers via the TCP protocol. Once received, they undergo decoding and are then presented in a readable format. Furthermore, telegrams classified as Warning or Alarm are specially highlighted to aid easy identification.

To enhance flexibility and ease of maintenance, the program retrieves sensor parameters and receiver configurations from separate JSON files. Sensor parameters are fetched from 'sensorConfig.json', while receiver configurations are sourced from a dedicated file 'receiverConfig.json'.


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
