#include <TCPConnection.hpp>

TCPConnection
::TCPConnection(boost::asio::io_context& ioContext,
                boost::asio::ip::tcp::endpoint remote):
	Endpoint(std::move(remote)),
	RemoteEndpoint(fmt::format("{}:{}", remote.address().to_string(), remote.port())),
	Socket(std::make_unique<boost::asio::ip::tcp::socket>(ioContext))
{
}

void
TCPConnection
::RefreshConnection(boost::system::error_code& result)
{
	spdlog::info("TCPConnection({})> Refreshing connection", RemoteEndpoint);
	Socket->connect(Endpoint, result);
	if (result.failed())
	{
		spdlog::warn("TCPConnection({})> Cannot connect: {}", RemoteEndpoint, result.what());
	}
}

std::shared_ptr<TCPConnection>
TCPConnection
::BuildShared(boost::asio::io_context& ioContext, std::string address, unsigned port)
{
	spdlog::info("Building Shared TCPConnection({}:{})", address, port);
	auto ptr = std::shared_ptr<TCPConnection>(new TCPConnection{
		ioContext,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port)
	});
	spdlog::info("Finished building TCPConnection({}:{})", address, port);
	return ptr;
}

TCPConnection
::~TCPConnection()
{
	spdlog::info("TCPConnection({})> Trying closing", RemoteEndpoint);
	Disconnect();
	spdlog::info("TCPConnection({})> Closed", RemoteEndpoint);
}

void
TCPConnection
::Connect()
{
	boost::system::error_code result;
	RefreshConnection(result);
	if (result.failed())
	{
		spdlog::warn("TCPConnection({})> Cannot connect: {}", RemoteEndpoint, result.what());
		Connected = false;
		return;
	}

	Connected = true;
}

bool
TCPConnection
::IsConnected()
{
	return Connected;
}

void
TCPConnection
::Disconnect()
{
	boost::system::error_code result;
	Socket->close(result);
	if (result.failed())
	{
		spdlog::warn("TCPConnection({})> Cannot close tcp connection: {}", RemoteEndpoint, result.what());
	}

	Connected = false;
}

MemoryView::SizeType
TCPConnection
::Read(const MemoryView& view)
{
	boost::system::error_code result{};
	auto bytes = read(*Socket, view.ToBuffer(), result);
	spdlog::info(
		"TCPConnection({})> Read {}:{} bytes, failed({}), failure({})",
		RemoteEndpoint,
		bytes,
		view.Size,
		result.failed(),
		result.what()
	);

	//TODO failure counter and exception processor

	return bytes;
}

MemoryView::SizeType
TCPConnection
::Write(const MemoryView& view)
{
	boost::system::error_code result{};
	auto bytes = write(*Socket, view.ToBuffer(), result);
	spdlog::info(
		"TCPConnection({})> Write {}:{} bytes, failed({}), failure({})",
		RemoteEndpoint,
		bytes,
		view.Size,
		result.failed(),
		result.what()
	);

	return bytes;
}
