#pragma once

#include <glm/glm.hpp>
#include <imgui.h>
#include <sstream>
#include <string>
#include <vector>

namespace blot {

// GLM to ImGui conversions
inline ImVec2 ToImVec2(const glm::vec2 &v) { return ImVec2(v.x, v.y); }
inline ImVec4 ToImVec4(const glm::vec4 &v) {
	return ImVec4(v.x, v.y, v.z, v.w);
}

// ImGui to GLM conversions
inline glm::vec2 ToGLMVec2(const ImVec2 &v) { return glm::vec2(v.x, v.y); }
inline glm::vec4 ToGLMVec4(const ImVec4 &v) {
	return glm::vec4(v.x, v.y, v.z, v.w);
}

// ImVec2 operator overloads for vector math
inline ImVec2 operator+(const ImVec2 &a, const ImVec2 &b) {
	return ImVec2(a.x + b.x, a.y + b.y);
}

inline ImVec2 operator-(const ImVec2 &a, const ImVec2 &b) {
	return ImVec2(a.x - b.x, a.y - b.y);
}

inline ImVec2 operator*(const ImVec2 &a, float s) {
	return ImVec2(a.x * s, a.y * s);
}

inline ImVec2 operator/(const ImVec2 &a, float s) {
	return ImVec2(a.x / s, a.y / s);
}

// Utility functions
inline std::vector<std::string> splitCommaSeparated(const std::string &input) {
	std::vector<std::string> result;
	std::stringstream ss(input);
	std::string item;
	while (std::getline(ss, item, ',')) {
		// Trim whitespace
		size_t start = item.find_first_not_of(" \t");
		size_t end = item.find_last_not_of(" \t");
		if (start != std::string::npos && end != std::string::npos)
			result.push_back(item.substr(start, end - start + 1));
		else if (start != std::string::npos)
			result.push_back(item.substr(start));
		// else skip empty/whitespace-only
	}
	return result;
}

} // namespace blot 