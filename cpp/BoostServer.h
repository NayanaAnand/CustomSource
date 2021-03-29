#ifndef BOOSTSERVER_H_
#define BOOSTSERVER_H_

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread.hpp>
#include <boost/asio/error.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <ossie/debug.h>

#include "BoundedBuffer.h"

using boost::asio::ip::tcp;

class Server;

class Session: public boost::enable_shared_from_this<Session> {
ENABLE_LOGGING
public:
    Session(boost::asio::io_service& io_service, Server* s,
            size_t max_sock_read_size, short port = 0);
    tcp::socket& Socket();
    void Start();

private:
    void HandleRead(const boost::system::error_code& error,
            size_t bytes_transferred);

    tcp::socket socket_;
    Server* server_;
    std::vector<char> sock_read_buf_;
    short port_;
};

typedef boost::shared_ptr<Session> SessionPtr;

class Server {
ENABLE_LOGGING
public:
    Server(short port, size_t buffer_len = 64, size_t max_sock_read_size = 64 * 1024);
    Server(short port, size_t buffer_len, size_t max_sock_read_size, bool tcp_nodelay);

    ~Server();

    size_t Read(char* data, size_t size);
    bool is_connected();
    bool is_empty();

    void NewSessionData(char* data, size_t size);
    void CloseSession(SessionPtr ptr);

private:
    void StartAccept();
    void HandleAccept(SessionPtr new_session,
            const boost::system::error_code& error);
    void RunIoService();

    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    std::list<SessionPtr> sessions_;
    boost::mutex sessions_lock_;
    boost::thread* thread_;
    size_t max_sock_read_size_;
    BoundedBuffer<char> pending_buf_;
    short port_;
    bool tcp_nodelay_;
    bool configure_socket;
};

#endif /* BOOSTSERVER_H_ */
