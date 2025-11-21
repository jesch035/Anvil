#include "Log.h"

void WinFormsSink::sink_it_(const spdlog::details::log_msg& msg)
{
	spdlog::memory_buf_t buffer;
	formatter_->format(msg, buffer);

	if (Logger::Get().m_CallbackFn)
		Logger::Get().m_CallbackFn(fmt::to_string(buffer).c_str());
}