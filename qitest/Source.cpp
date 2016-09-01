#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

int main(int argc, char** argv)
{
	qi::ApplicationSession app(argc, argv);
	app.startSession(); // connect the session
	qi::SessionPtr session = app.session();

	qi::AnyObject tts = session->service("ALTextToSpeech");
	tts.call<void>("say", std::string("test"));

	return 0;
}