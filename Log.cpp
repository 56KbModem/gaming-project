//
// Created by Nathan Hoekstra on 2019-01-14.
//

#include "Log.hpp"

namespace tf{
    std::shared_ptr<spdlog::logger> Log::sCoreLogger;
    std::shared_ptr<spdlog::logger> Log::sNetworkLogger;
    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        sCoreLogger = spdlog::stdout_color_mt("TopForce");
        sCoreLogger->set_level(spdlog::level::trace);

        sNetworkLogger = spdlog::stdout_color_mt("Network");
        sNetworkLogger->set_level(spdlog::level::trace);
    }
}

