//
// Created by xin on 2023/11/18.
//

#include <memory>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

using namespace std;

class BasicSerailPort {
public:
    using sizeType = unsigned long long;

    //control func
    virtual void Connect() = 0;

    virtual void disConnect() = 0;

    virtual bool isConnect() = 0;

    virtual sizeType Read(void *head, sizeType size) = 0; //虚函数
    virtual sizeType Write(void *head, sizeType size) = 0;

};

class SerialPort : public BasicSerailPort {

    unique_ptr<boost::asio::serial_port> SerialPointer;
    bool isConnected = false;

public:

    //boost::asio::serial_port需要上下文
    SerialPort(boost::asio::io_context &ioContext) :
            SerialPointer(std::move(make_unique<boost::asio::serial_port>(ioContext))) {}

    void Connect() override {
        SerialPointer->open("/dev/ttys004");
        SerialPointer->set_option(
                boost::asio::serial_port::stop_bits(
                        boost::asio::serial_port::stop_bits::one
                        )
                );
        SerialPointer->set_option(boost::asio::serial_port::baud_rate(115200));
        SerialPointer->set_option(
                boost::asio::serial_port::parity(
                        boost::asio::serial_port::parity::none
                        )
                );//校验
        SerialPointer->set_option(boost::asio::serial_port::character_size(8));
        SerialPointer->set_option(
                boost::asio::serial_port::flow_control(
                        boost::asio::serial_port::flow_control::none
                        )
                );


    }

    void disConnect() override {
        SerialPointer->close();
    }

    bool isConnect() override {
        return SerialPointer->is_open();
    }

    sizeType Read(void *head, sizeType size) override {
        return boost::asio::read(*SerialPointer, boost::asio::buffer(head, size));
    }

    sizeType Write(void *head, sizeType size) override {
        return boost::asio::write(*SerialPointer, boost::asio::buffer(head, size));
    }
};


signed main() {

    boost::asio::io_context io_context;
    SerialPort serial_port(io_context);

    char buffer[4]{'a', 'b', 'c', 'd'};

    while(!serial_port.isConnect())
    {
        serial_port.Connect();
    }

    while (true) {
        serial_port.Write(buffer, 4);
        std::this_thread::sleep_for(1s);
    }
    return 0;
}