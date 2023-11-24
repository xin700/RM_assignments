
#include <thread>
#include <chrono>
#include <iostream>
#include <SerialPort.hpp>
#include <TCPConnection.hpp>

char Generate()
{
	// ReSharper disable once StringLiteralTypo
	static constexpr char Message[] = "abcdefghjklmnopqrstuvwxyz";
	static auto index = 0;

	return Message[ index = (index + 1) % sizeof(Message) ];
}

void TestSerial()
{
	using namespace std::chrono_literals;

	boost::asio::io_context io;

	const auto connection = SerialPort::BuildShared(io, {"/dev/ttys002", 115200});
    const auto connectionRead = SerialPort::BuildShared(io,{"/dev/ttys003",115200});

    while (!connectionRead -> IsConnected()){
        connectionRead -> Connect();
        std::this_thread::sleep_for(1s);
    }
	while (!connection->IsConnected())
	{
		connection->Connect();
		std::this_thread::sleep_for(1s);
	}

	char buffer[129]{0};
	const MemoryView buffer_view{buffer, 128};

    char bufferRead[129]{0};
    const MemoryView buffer_viewRead{bufferRead, 128};
	while (true)
	{
		for (auto i = 0; i < 128; i++)
		{
			buffer[i] = Generate();
		}

		connection->Write(buffer_view);
        connectionRead ->Read(buffer_viewRead);
		std::this_thread::sleep_for(1s);

	}
}

void TestTCP()
{
	using namespace std::chrono_literals;

	boost::asio::io_context io;
	const auto tcp = TCPConnection::BuildShared(io, "127.0.0.1", 8989);
	tcp->Connect();

	char buffer[129]{0};
	constexpr auto message = "hello world\n";
	strcpy(buffer, message);
	tcp->Write({buffer, 13});
	memset(buffer, 0 , 13);

	auto index{0};
	do {
		tcp->Read({buffer + index, 1});
	} while (buffer[index++] != 0);
	for (const auto c: buffer)
	{
		if (c == 0)
			break;

		std::cout << c;
	}
	std::cout << std::endl;
}

int main()
{
//	TestSerial();
	TestTCP();
}
