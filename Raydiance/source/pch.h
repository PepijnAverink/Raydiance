#pragma once

// Core includes
#include "./core/error/logger.h"
#include "./core/container/types.h"

#if defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

// STL containers
#include <string>
#include <string_view>
#include <stack>
#include <deque>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// Memory / utilities
#include <memory>
#include <utility>
#include <optional>
#include <variant>
#include <any>

// ALgorithm / utilities
#include <algorithm>
#include <functional>

// Type utilities
#include <type_traits>
#include <typeindex>
#include <typeinfo>

// Numerics
#include <limits>
#include <cmath>
#include <numeric>

// Time
#include <chrono>

// Threading / sync
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <condition_variable>

// Streams / formatting
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

// Error handling
#include <exception>
#include <stdexcept>

// C headers
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// C++20 features
#include <span>
#include <filesystem>
#include <bit>
#include <charconv>
#include <format>