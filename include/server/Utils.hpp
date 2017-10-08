//
// Created by Clément Péau on 08/10/2017.
//

#ifndef CPP_SPIDER_UTILS_HPP
#define CPP_SPIDER_UTILS_HPP

#include <string>
#include <sstream>
#include "client/SpiderClient.hpp"
#include "boost/asio/streambuf.hpp"
#include "boost/archive/text_iarchive.hpp"


class Utils
{
public:
	static std::string makeStringFromAsioStream(boost::asio::streambuf &buffer)
	{
		std::ostringstream ss;
		std::string string;

		ss << &buffer;
		string = ss.str();
		return (string);
	}


	static void deserialize(t_paquet &paquet, boost::asio::streambuf &buf)
	{
		std::istream is(&buf);
		boost::archive::text_iarchive ar(is);

		ar & paquet;
	}

	static std::string PaquetToString(t_paquet &paquet) {
		std::string c_data(paquet.id);
		t_kbData    *kbData = paquet.kbdata;
		auto timeInfo = new struct tm;

		c_data.append("\n");
		while (kbData != NULL) {
			time_t      rawTime = kbData->timestamp;
			char        *kbBuf;

			c_data.append(kbData->key_code);
			c_data.append(" ");
			(kbData->status == 1 ? c_data.append("DOWN ") : c_data.append("UP "));
			/* Time */
			timeInfo = localtime(&rawTime);
			kbBuf = asctime(timeInfo);
			c_data.append(kbBuf);
			kbData = kbData->next;
		}
		t_mouseData *msData = paquet.msdata;
		while (msData != NULL) {
			time_t      rawTime = msData->timestamp;
			char        *msBuf;

			if (msData->key_code == 1) {
				c_data.append("Right Click at [");
			}
			else if (msData->key_code == 2) {
				c_data.append("Left Click at [");
			}
			else {
				c_data.append("Middle Click at [");
			}
			c_data.append(std::to_string(msData->x));
			c_data.append(";");
			c_data.append(std::to_string(msData->y));
			c_data.append("] DOWN ");
			/* Time */
			timeInfo = localtime(&rawTime);
			msBuf = asctime(timeInfo);
			c_data.append(msBuf);
			msData = msData->next;
		}
		return c_data;
	}
};

#endif //CPP_SPIDER_UTILS_HPP
