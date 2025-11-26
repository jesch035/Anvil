#include "Sinks.h"

void CallbackSink::sink_it_(const spdlog::details::log_msg& msg)
{
	spdlog::memory_buf_t buffer;
	formatter_->format(msg, buffer);

	if (m_CallbackFn)
		m_CallbackFn(fmt::to_string(buffer).c_str());
}