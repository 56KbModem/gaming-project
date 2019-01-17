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
        inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }
        inline static std::shared_ptr<spdlog::logger>& get_network_logger() { return s_network_logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_core_logger;
        static std::shared_ptr<spdlog::logger> s_network_logger;
    };
}

// Core log macros
#define TF_TRACE(...)    ::tf::log::get_core_logger()->trace(__VA_ARGS__)
#define TF_INFO(...)     ::tf::log::get_core_logger()->info(__VA_ARGS__)
#define TF_WARN(...)     ::tf::log::get_core_logger()->warn(__VA_ARGS__)
#define TF_ERROR(...)    ::tf::log::get_core_logger()->error(__VA_ARGS__)
#define TF_FATAL(...)    ::tf::log::get_core_logger()->fatal(__VA_ARGS__)

// Network log macros
#define NETWORK_TRACE(...)    ::tf::log::get_network_logger()->trace(__VA_ARGS__)
#define NETWORK_INFO(...)     ::tf::log::get_network_logger()->info(__VA_ARGS__)
#define NETWORK_WARN(...)     ::tf::log::get_network_logger()->warn(__VA_ARGS__)
#define NETWORK_ERROR(...)    ::tf::log::get_network_logger()->error(__VA_ARGS__)
#define NETWORK_FATAL(...)    ::tf::log::get_network_logger()->fatal(__VA_ARGS__)

#endif //TOPFORCE_LOG_HPP
