//
// Created by Nathan Hoekstra on 2019-01-14.
//

#ifndef TOPFORCE_LOG_HPP
#define TOPFORCE_LOG_HPP

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace tf{
    class log {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& get_logger() { return s_Logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

// Core log macros
#define TF_TRACE(...)    ::tf::log::get_logger()->trace(__VA_ARGS__)
#define TF_INFO(...)     ::tf::log::get_logger()->info(__VA_ARGS__)
#define TF_WARN(...)     ::tf::log::get_logger()->warn(__VA_ARGS__)
#define TF_ERROR(...)    ::tf::log::get_logger()->error(__VA_ARGS__)
#define TF_FATAL(...)    ::tf::log::get_logger()->fatal(__VA_ARGS__)

#endif //TOPFORCE_LOG_HPP
