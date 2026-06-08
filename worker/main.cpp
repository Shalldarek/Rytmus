#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "include/Statistics.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
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

    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    sql::Connection* conn(
        driver->connect("tcp://127.0.0.1:3306", "venca_srubar", "Kyloren_2005")
    );
    conn->setSchema("rytmus");

    std::string api_url("http://localhost:8000/logs/");

    cpr::Response r = cpr::Get(cpr::Url{api_url});

    if (r.status_code == 200) {
        try {
            Statistics stats;
            json response_data = json::parse(r.text);

            stats.get_day_statistics(response_data, conn);
            stats.positive_sleeping_streak(response_data);

        } catch (const json::parse_error& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch data. Status code: " << r.status_code << std::endl;
        std::cerr << "Error message: " << r.text << std::endl;
    }

    delete conn;

    return 0;
}
