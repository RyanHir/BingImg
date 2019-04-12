#include <sstream>
#include <fstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int main(int argc, char *argv[])
{
	char url[] = "https://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&mkt=en-US";
 
	rapidjson::Document d;

	curlpp::Easy request;
	curlpp::Easy img;

	std::stringstream ahh;
	std::ofstream myfile;
	try {
		request.setOpt(new curlpp::options::WriteStream(&ahh));
		request.setOpt(new curlpp::options::Url(url));

		request.perform();

		d.Parse(ahh.str().c_str());
		std::string date = d["images"][0]["startdate"].GetString();
		std::string parsed = std::string("https://www.bing.com") + d["images"][0]["url"].GetString();

		myfile.open(date + ".jpg");

		img.setOpt(new curlpp::options::WriteStream(&myfile));
		img.setOpt(new curlpp::options::Url(parsed));

		img.perform();

		myfile.close();
		return EXIT_SUCCESS;
	}
	catch ( curlpp::LogicError & e ) {
		std::cout << e.what() << std::endl;
	}
	catch ( curlpp::RuntimeError & e ) {
		std::cout << e.what() << std::endl;
	}

	return EXIT_FAILURE;
}
