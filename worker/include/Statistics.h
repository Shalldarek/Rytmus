#pragma onca
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Statistics {
    public:
        void get_day_statistics(json data);
};