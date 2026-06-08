#include "../include/Statistics.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

void Statistics::get_day_statistics(json data, sql::Connection* conn) {
    for (const auto& daily_log : data) {
        int score = 0;
        float sleep_hours        = daily_log.value("sleep_hours", 0.0);
        int   night_awakenings   = daily_log.value("night_awakenings", 0);
        int   stress_level       = daily_log.value("stress_level", 10);
        int   mood_level         = daily_log.value("mood_level", 0);
        float water_liters       = daily_log.value("water_liters", 0.0);
        int   coffees            = daily_log.value("coffees", 10);
        float screen_time_hours  = daily_log.value("screen_time_hours", 100.0);
        bool  workout            = daily_log.value("workout", false);
        std::string log_date     = daily_log.value("log_date", "Unknown Date");

        if (sleep_hours >= 7.0)       score += 20;
        if (night_awakenings <= 1)    score += 10;
        if (stress_level <= 4)        score += 15;
        if (mood_level >= 7)          score += 15;
        if (water_liters >= 2.5)      score += 10;
        if (coffees <= 2)             score += 10;
        if (screen_time_hours <= 4.0) score += 5;
        if (workout)                  score += 15;

        std::cout << "Your score for day " << log_date
                  << " is " << score << " points!" << std::endl;

        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
                "INSERT INTO day_statistics "
                "(log_date, sleep_hours, night_awakenings, stress_level, "
                " mood_level, water_liters, coffees, screen_time_hours, workout, score) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
            ));

            pstmt->setString(1, log_date);
            pstmt->setDouble(2, sleep_hours);
            pstmt->setInt   (3, night_awakenings);
            pstmt->setInt   (4, stress_level);
            pstmt->setInt   (5, mood_level);
            pstmt->setDouble(6, water_liters);
            pstmt->setInt   (7, coffees);
            pstmt->setDouble(8, screen_time_hours);
            pstmt->setBoolean(9, workout);
            pstmt->setInt   (10, score);

            pstmt->executeUpdate();

    } catch (sql::SQLException& e) {
            std::cerr << "MySQL error: " << e.what()
                      << " (code " << e.getErrorCode() << ")" << std::endl;
        }
    }
}

void Statistics::positive_sleeping_streak(json data) {
    int streak = 0;

    for (const auto& log : data) {

        if (log["sleep_hours"] >= 7) {
            streak++;
        } else {
            streak = 0;
        }
    }

    std::cout << "Sleeping Streak: " << streak << " days!"<< std::endl;
}