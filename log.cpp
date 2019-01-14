//
// Created by Nathan Hoekstra on 2019-01-14.
//

#include "log.hpp"

namespace tf{
    std::shared_ptr<spdlog::logger> log::s_Logger;
    void log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_Logger = spdlog::stdout_color_mt("TopForce");
        s_Logger->set_level(spdlog::level::trace);
    }
}

