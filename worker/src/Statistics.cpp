#include "../include/Statistics.h"
#include <iostream>
#include <iomanip>

void Statistics::get_day_statistics(json data) {
    for (const auto& daily_log : data) {
        int score = 0;
        
        if (daily_log.value("sleep_hours", 0.0) >= 7.0) score += 20;
        if (daily_log.value("night_awakenings", 0) <= 1) score += 10;

        if (daily_log.value("stress_level", 10) <= 4) score += 15;
        if (daily_log.value("mood_level", 0) >= 7) score += 15;

        if (daily_log.value("water_liters", 0.0) >= 2.5) score += 10;
        if (daily_log.value("coffees", 10) <= 2) score += 10;
        if (daily_log.value("screen_time_hours", 100.0) <= 4.0) score += 5;

        if (daily_log.value("workout", false) == true) score += 15;

        std::string log_date = daily_log.value("log_date", "Unknown Date");
        std::cout << "Your score for day " << log_date << " is " << score << " points!" << std::endl;
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

    std::cout << "Sleeping Streak: " << streak << std::endl;
}