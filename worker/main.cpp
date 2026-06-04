#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>

using json = nlohmann::json;

std::string get_today_date() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}

int main() {
    std::cout << "--- Rytmus C++ Worker ---" << std::endl;

    std::string target_date = get_today_date();
    std::string api_url = "http://localhost:8000/logs/" + target_date;

    std::cout << "Fetching data for: " << target_date << " from " << api_url << std::endl;

    cpr::Response r = cpr::Get(cpr::Url{api_url});

    if (r.status_code == 200) {
        std::cout << "Data retrieved successfully!" << std::endl;
        std::cout << "Raw JSON response:\n" << r.text << std::endl;
        std::cout << "---------------------------" << std::endl;

        try {
            json response_data = json::parse(r.text);

            std::cout << "Parsed Data Extraction:" << std::endl;
            std::cout << "Sleep Hours: " << response_data["sleep_hours"] << std::endl;
            std::cout << "Stress Level: " << response_data["stress_level"] << std::endl;
            std::cout << "Mood level: " << response_data["mood_level"] << std::endl;
            std::cout << "Coffees: " << response_data["coffees"] << std::endl;

            auto workout = response_data["workout"];

            if (workout) 
                std::cout << "I did excercices" << std::endl;
            else {
                std::cout << "I didn't do excercices" << std::endl;
            }

            if (response_data["mood_level"] > 7) 
                std::cout << "Such a wonderful day I had" << std::endl;


        } catch (const json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch data. Status code: " << r.status_code << std::endl;
        std::cerr << "Error message: " << r.text << std::endl;
    }

    return 0;
}