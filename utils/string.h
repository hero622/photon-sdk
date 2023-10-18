#pragma once

#include <string>

namespace utils {
	namespace string {
		std::string ssprintf(const char *fmt, ...);
		bool replace(std::string &str, const std::string &from, const std::string &to);
	}  // namespace string
}  // namespace utils