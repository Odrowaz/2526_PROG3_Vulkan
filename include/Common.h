#pragma once
#include <iostream>
#include <format>
#include <vulkan/vulkan.h>

#define CHECK_DIE(x, msg) { \
    if (!(x)) DIE(msg) \
}

#define CHECK_VK(x, msg) { \
    if ((x) != VK_SUCCESS) DIE(msg) \
}

#define DIE(msg) { \
    LOG_ERROR(msg); \
    throw std::runtime_error(msg); \
}

#define LOG_MSG(type, fmt, ...) std::format("[" type "] " fmt "\n" __VA_OPT__(,) __VA_ARGS__);

#define LOG_ERROR(fmt, ...) { \
    auto _log_msg = LOG_MSG("ERROR", fmt, __VA_ARGS__); \
    std::cerr << _log_msg; \
}

#ifdef _DEBUG
#define LOG_DEBUG(fmt, ...) { \
    auto _log_msg = LOG_MSG("DEBUG", fmt, __VA_ARGS__); \
    std::cout << _log_msg; \
}
#else
#define LOG_DEBUG(fmt, ...)
#endif
