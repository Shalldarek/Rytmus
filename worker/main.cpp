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

    std::string api_url = "http://localhost:8000/logs/";

    cpr::Response r = cpr::Get(cpr::Url{api_url});

    if (r.status_code == 200) {
        std::cout << "Data retrieved successfully!" << std::endl;
        std::cout << "Raw JSON response:\n" << r.text << std::endl;
        std::cout << "---------------------------" << std::endl;

        try {
            json response_data = json::parse(r.text);

            int score = 0;

            for (const auto& daily_log : response_data) {
                if (daily_log["sleep_hours"].get<double>() >= 7.0) score += 20;
                if (daily_log["night_awakenings"].get<int>() <= 1) score += 10;

                if (daily_log["stress_level"].get<int>() <= 4) score += 15;
                if (daily_log["mood_level"].get<int>() >= 7) score += 15;

                if (daily_log["water_liters"].get<double>() >= 2.5) score += 10;
                if (daily_log["coffees"].get<int>() <= 2) score += 10;
                if (daily_log["screen_time_hours"].get<double>() <= 4.0) score += 5;

                if (daily_log["workout"].get<bool>() == true) score += 15;

                std::cout << "Your score for day " << daily_log["log_date"] << ": is " << score << " points!" << std::endl;
            }

        } catch (const json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch data. Status code: " << r.status_code << std::endl;
        std::cerr << "Error message: " << r.text << std::endl;
    }

    return 0;
}