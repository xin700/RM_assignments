#pragma once

#include <string>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "Connection.hpp"


class TCPConnection final : public Connection
{
	volatile bool Connected{false};
	boost::asio::ip::tcp::endpoint Endpoint;
	std::string RemoteEndpoint;
	std::unique_ptr<boost::asio::ip::tcp::socket> Socket;

	TCPConnection(boost::asio::io_context& ioContext, boost::asio::ip::tcp::endpoint remote);

	void RefreshConnection(boost::system::error_code& result);

public:
	TCPConnection() = delete;

	static std::shared_ptr<TCPConnection> BuildShared(boost::asio::io_context& ioContext, std::string address,
	                                                  unsigned port);

	~TCPConnection() override;

	void Connect() override;

	[[nodiscard]] bool IsConnected() override;

	void Disconnect() override;

	MemoryView::SizeType Read(const MemoryView& view) override;

	MemoryView::SizeType Write(const MemoryView& view) override;
};
