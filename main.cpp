#include <sstream>
#include <fstream>
#include <algorithm>

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

	std::stringstream ahhOne;
	request.setOpt(new curlpp::options::WriteStream(&ahhOne));
	request.setOpt(new curlpp::options::Url(url));

	request.perform();

	d.Parse(ahhOne.str().c_str());

	rapidjson::Value &ahh = d["images"];

	for(rapidjson::Value::ConstValueIterator x=ahh.Begin(); x != ahh.End(); x++) {
		std::ofstream myfile;
		curlpp::Easy img;

		const rapidjson::Value &imgData = (*x);

		std::string parsed = std::string("https://www.bing.com") + imgData["url"].GetString();

		std::string title = imgData["title"].GetString();

		myfile.open(title + std::string(".jpg"));

		img.setOpt(new curlpp::options::WriteStream(&myfile));
		img.setOpt(new curlpp::options::Url(parsed));

		img.perform();

		myfile.close();
	}

	return EXIT_SUCCESS;
}
