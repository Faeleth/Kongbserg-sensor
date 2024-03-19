#include <Sensor.hpp>
#include <random>

unsigned int Sensor::sensorCounter = 0;

std::string Sensor::to_string() const {
    return "Sensor: " + std::to_string(id) + " type: " + type + " min: " + std::to_string(min) + " max: " + std::to_string(max) + " frequency: " + std::to_string(frequency);
}

std::string Sensor::to_string_broadcast() const {
    return std::to_string(id) + ", " + type;
}

int Sensor::generate_value() const {
    // modern c++ random number generation
    // source - https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

std::string Sensor::quality_to_string(Quality quality) const {
    switch (quality) {
        case Quality::Alarm:
            return "Alarm";
        case Quality::Warning:
            return "Warning";
        case Quality::Normal:
            return "Normal";
        default:
            return "Unknown";
    }
}

std::string Sensor::classify_value(int value) const {
    int range = max - min;
    int alarmRange = range * 0.1;
    int warningRange = range * 0.15;

    int alarm_min = min + alarmRange;
    int alarm_max = max - alarmRange;

    int warning_min = alarm_min + warningRange;
    int warning_max = alarm_max - warningRange;

    if(value <= alarm_min || value >= alarm_max){
        return quality_to_string(Quality::Alarm);
    } else if( value <= warning_min && value > alarm_min || value >= warning_max && value < alarm_max){
        return quality_to_string(Quality::Warning);
    } else {
        return quality_to_string(Quality::Normal);
    }
}