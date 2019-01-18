//
// Created by Nathan Hoekstra on 2019-01-14.
//

#ifndef TOPFORCE_LOG_HPP
#define TOPFORCE_LOG_HPP

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace tf{
    class Log {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return sCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& getNetworkLogger() { return sNetworkLogger; }
    private:
        static std::shared_ptr<spdlog::logger> sCoreLogger;
        static std::shared_ptr<spdlog::logger> sNetworkLogger;
    };
}

// Core Log macros
#define TF_TRACE(...)    ::tf::Log::getCoreLogger()->trace(__VA_ARGS__)
#define TF_INFO(...)     ::tf::Log::getCoreLogger()->info(__VA_ARGS__)
#define TF_WARN(...)     ::tf::Log::getCoreLogger()->warn(__VA_ARGS__)
#define TF_ERROR(...)    ::tf::Log::getCoreLogger()->error(__VA_ARGS__)
#define TF_FATAL(...)    ::tf::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Network Log macros
#define NETWORK_TRACE(...)    ::tf::Log::getNetworkLogger()->trace(__VA_ARGS__)
#define NETWORK_INFO(...)     ::tf::Log::getNetworkLogger()->info(__VA_ARGS__)
#define NETWORK_WARN(...)     ::tf::Log::getNetworkLogger()->warn(__VA_ARGS__)
#define NETWORK_ERROR(...)    ::tf::Log::getNetworkLogger()->error(__VA_ARGS__)
#define NETWORK_FATAL(...)    ::tf::Log::getNetworkLogger()->fatal(__VA_ARGS__)

#endif //TOPFORCE_LOG_HPP
