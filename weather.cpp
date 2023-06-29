#include <ctime>

#include "init.h"
#include "weather.h"

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

WeatherInfo getWeatherData(std::string latitude, std::string longitude) {
    CURL* curl;
    CURLcode res;
    std::string apiResponse;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    WeatherInfo weatherInfo = WeatherInfo(false, false, 0, 25000);

    std::string apiCall = "https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude + "&hourly=temperature_2m,rain,snowfall,visibility&forecast_days=1";

    if (curl)
    {
        // Get the meteo info from Paris
        curl_easy_setopt(curl, CURLOPT_URL, apiCall.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Failed to perform API request: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            json data = json::parse(apiResponse);
            json hourly = data["hourly"];
            json rain = hourly["rain"];
            json snow = hourly["snowfall"];
            json visibility = hourly["visibility"];

            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);
            int currentHour = localTime->tm_hour;
            weatherInfo.temperature = hourly["temperature_2m"][currentHour];

            for (int i = 0; i < rain.size(); i++) {
                if (rain[i] > 0) {
                    weatherInfo.rain = true;
                }
                if (snow[i] > 0) {
                    weatherInfo.snow = true;
                    weatherInfo.rain = false;
                }
                if (visibility[i] < weatherInfo.visibility) {
                    weatherInfo.visibility = visibility[i];
                }
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return weatherInfo;
}

void setWeatherDisplay(WeatherInfo weatherInfo) {
    temperature = weatherInfo.temperature;
    if (weatherInfo.snow) {
        set_snow();
    }
    else if (weatherInfo.rain) {
        set_rain();
    }
    else {
        set_sun();
    }
    fogStartDistance = ((float)weatherInfo.visibility / 24000.0f) * 25;
    if (fogStartDistance < 5.0) {
        fogStartDistance = 5.0;
    }
    updateTemp();
    updateFog();
}