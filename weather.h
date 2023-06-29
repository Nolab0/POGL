#ifndef WEATHER_VISUALIZER_WEATHER_H
#define WEATHER_VISUALIZER_WEATHER_H

#include <curl/curl.h>
#include <iostream>

#include "json.hpp"

class WeatherInfo {
public:
    bool rain;
    bool snow;
    int temperature;
    int visibility;

    WeatherInfo(bool rain, bool snow, int temperature, int visibility) {
        this->rain = rain;
        this->snow = snow;
        this->temperature = temperature;
        this->visibility = visibility;
    }
};

WeatherInfo getWeatherData(std::string latitude, std::string longitude);
void setWeatherDisplay(WeatherInfo weatherInfo);

#endif //WEATHER_VISUALIZER_WEATHER_H
