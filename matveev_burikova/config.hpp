#pragma once

#include "graph.hpp"

#include <iostream>

namespace uni_course_cpp {
namespace config {
inline constexpr int kInitialDepth = 1;
inline constexpr const char* kTempDirectoryPath = "./temp/";

inline const std::string kLogFilename = "log.txt";
inline const std::string kLogFilePath = kTempDirectoryPath + kLogFilename;

}  // namespace config
}  // namespace uni_course_cpp