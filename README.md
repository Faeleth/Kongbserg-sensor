<h1 align="center">Kongsberg sensor symulator</h1>

<p align="center">
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="https://github.com/Faeleth" target="_blank">Author</a>
</p>

<br>

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com), [CMake](https://cmake.org/) and [Boost](https://www.boost.org/) installed. You also need a C++ compiler supporting at least C++11 standard.

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
