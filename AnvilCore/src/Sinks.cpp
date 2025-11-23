#include "Sinks.h"

void EditorSink::sink_it_(const spdlog::details::log_msg& msg)
{
	spdlog::memory_buf_t buffer;
	formatter_->format(msg, buffer);

	SendMessageToEditor(fmt::to_string(buffer).c_str());
}

void EditorSink::SendMessageToEditor(const std::string& msg)
{
	if (m_CallbackFn)
		m_CallbackFn(msg.c_str());
}