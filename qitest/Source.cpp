#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

qi::AnyReference testCallback(const std::vector<qi::AnyReference>& params);

int main(int argc, char** argv)
{
	std::list<qi::AnyObject> _subscriberList;

	try {
		std::shared_ptr<qi::Session> session(new qi::Session);
		qi::Future<void> connectionFuture = session->connect("10.215.255.187");
		connectionFuture.wait();

		qi::AnyObject alm = session->service("ALMemory");

		qi::AnyObject subscriber = alm.call<qi::AnyObject>("subscriber", "ChestButtonPressed");

		qi::SignalSubscriber sigSub(qi::AnyFunction::fromDynamicFunction(boost::bind(&testCallback, _1)));

		qi::Future<qi::SignalLink> f = subscriber.connect("signal", sigSub);
		f.wait();

		if (f.hasError()) {
			std::cout << "Error on signal connect: " << f.error() << std::endl;
		}

		std::cout << "signal connected" << std::endl;
		_subscriberList.push_back(subscriber);

		std::getchar();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

	return 0;
}

qi::AnyReference testCallback(const std::vector<qi::AnyReference>& params) {
	std::cout << "NAOevent!" << std::endl;
	//returntype needs to be anyreference. this solution was taken form official libqi examples
	return qi::AnyReference();// nullptr;
}