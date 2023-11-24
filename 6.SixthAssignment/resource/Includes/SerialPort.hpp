#pragma once

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "Connection.hpp"
#include "SerialPortInfo.hpp"

class SerialPort final : public Connection
{
	std::unique_ptr<boost::asio::serial_port> UniqueSerialPort;

	SerialPortInfo Info;

	explicit SerialPort(boost::asio::io_context& ioContext, SerialPortInfo info);

	void ApplyOption(boost::system::error_code& result) const;

	void RefreshConnection(boost::system::error_code& result);

public:
	static std::shared_ptr<SerialPort> BuildShared(boost::asio::io_context& ioContext, const SerialPortInfo& info);

	SerialPort() = delete;

	~SerialPort() override;

	void Connect() override;

	[[nodiscard]] bool IsConnected() override;

	void Disconnect() override;

	[[nodiscard]] const SerialPortInfo& GetInfo() const;

	MemoryView::SizeType Read(const MemoryView& view) override;

	MemoryView::SizeType Write(const MemoryView& view) override;
};
