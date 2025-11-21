#include "Exports.h"

void InitWinFormsLog(LogCallbackFn callback)
{
	Logger::Get().m_CallbackFn = callback;

	Logger::Get().m_WinFormsSink = std::make_shared<WinFormsSink>();
	Logger::Get().m_WinFormsLogger = std::make_shared<spdlog::logger>("CoreLogger", Logger::Get().m_WinFormsSink);

	spdlog::set_default_logger(Logger::Get().m_WinFormsLogger);
	spdlog::flush_on(spdlog::level::info);
}

void TestLoggingFunction()
{
	LOG_EDITOR_INFO("Message from dll!");
}