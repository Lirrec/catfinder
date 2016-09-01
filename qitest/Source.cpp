#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

int main(int argc, char** argv)
{
	qi::ApplicationSession app(argc, argv);
	app.startSession(); // connect the session
	qi::SessionPtr session = app.session();

	qi::AnyObject danceManager = session->service("ALTextToSpeech");
	danceManager.call<void>("say", "test");

	return 0;
}