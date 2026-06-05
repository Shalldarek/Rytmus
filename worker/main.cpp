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

            int total_coffees = 0;
            int total_days = 0;

            for (const auto& daily_log : response_data) {
                total_coffees += daily_log["coffees"].get<int>();
                total_days++;
            }

            int avg_coffees = total_coffees / total_days;

            std::cout << "In average I drunk " << avg_coffees << " coffees" << std::endl;

        } catch (const json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch data. Status code: " << r.status_code << std::endl;
        std::cerr << "Error message: " << r.text << std::endl;
    }

    return 0;
}