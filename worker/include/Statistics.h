#pragma onca
#include <nlohmann/json.hpp>
#include <mysql_driver.h>      
#include <mysql_connection.h>    
#include <cppconn/connection.h>
using json = nlohmann::json;

class Statistics {
    public:
        void get_day_statistics(json data, sql::Connection* conn);
        void positive_sleeping_streak(json data);
};