#define ASIO_STANDALONE

#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>


using namespace boost;

class MyAsioFunctionsTest {
  public:
  
  asio::io_context ctx;
  
  MyAsioFunctionsTest(){}


};