//
// Created by Nathan Hoekstra on 2019-01-14.
//

#include "log.hpp"

namespace tf{
    std::shared_ptr<spdlog::logger> log::s_core_logger;
    std::shared_ptr<spdlog::logger> log::s_network_logger;
    void log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_core_logger = spdlog::stdout_color_mt("TopForce");
        s_core_logger->set_level(spdlog::level::trace);

        s_network_logger = spdlog::stdout_color_mt("Network");
        s_network_logger->set_level(spdlog::level::trace);
    }
}

