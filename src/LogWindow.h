#pragma once

#include <imgui.h>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include "Window.h"
namespace spdlog {
class logger;
namespace sinks {
class sink;
}
} // namespace spdlog

namespace blot {

enum class LogLevel { Debug, Info, Warning, Error };

struct LogEntry {
	LogLevel level;
	std::string message;
	std::string timestamp;
	LogEntry(LogLevel lvl, const std::string &msg, const std::string &time = "")
		: level(lvl), message(msg), timestamp(time) {}
};

class LogWindow : public Window {
  public:
	LogWindow(const std::string &title = "Log###Log",
			  Flags flags = Flags::None);
	virtual ~LogWindow() = default;

	// spdlog sink integration
	void setupSpdlogSink();
	void setSpdlogSink(std::shared_ptr<spdlog::sinks::sink> sink) {
		m_spdlogSink = sink;
	}
	std::shared_ptr<spdlog::sinks::sink> getSpdlogSink() const {
		return m_spdlogSink;
	}

	// For UI: clear log buffer
	void clearLog();

	// Ensure this class is not abstract
	void renderContents() override;

	// Allow LogWindowSink to access protected/private members
	friend class LogWindowSink;

  private:
	std::vector<LogEntry> m_logEntries;
	std::mutex m_logMutex;
	bool m_scrollToBottom = true;
	bool m_showDebug = true;
	bool m_showInfo = true;
	bool m_showWarning = true;
	bool m_showError = true;
	bool m_showTimestamps = true; // Toggle for timestamp display
	size_t m_maxLogLines = 1000;
	std::shared_ptr<spdlog::sinks::sink> m_spdlogSink;

	// UI methods
	void renderLogEntries();
	void renderFilterControls();
	void renderMenuBar();
	ImVec4 getLogColor(LogLevel level);
	std::string getLogLevelString(LogLevel level);

  protected:
	// Methods needed by LogWindowSink
	void addLogFromSink(LogLevel level, const std::string &message,
						const std::string &timestamp);
	std::string getCurrentTimestamp();
};

} // namespace blot
