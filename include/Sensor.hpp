#pragma once

#include <string>

//Generates random numbers from given range with given type
class Sensor {
    int min;
    int max;
    unsigned int frequency;
    unsigned int id;
    std::string type;

    static unsigned int sensor_counter;

    enum class Quality {
        Alarm,
        Warning,
        Normal
    };

    std::string quality_to_string(Quality quality) const;

    public:
        Sensor(int _min, int _max, unsigned int _freq, std::string _type, unsigned int _id): min(_min), max(_max), frequency(_freq), type(_type), id(_id){};
        int generate_value() const;
        std::string classify_value(int value) const;

        std::string to_string() const;
        std::string to_string_broadcast() const;
        int get_id() const { return id; };
        unsigned int getFrequency() const { return frequency; };
};