#include <iostream>
#include <boost/asio.hpp>
#include "Session.h"
#include "CServer.h"
#include "MsgNode.h"
//using namespace std;
int main()
{
	try {
		
		boost::asio::io_context ioc;
		
		CServer s(ioc, 10086);
		std::cout<<"Server is running on port 10086"<<std::endl;
		ioc.run();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}