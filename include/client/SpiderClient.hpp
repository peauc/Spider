//
// Created by lavigne on 10/5/17.
//

#ifndef SPIDERCLIENT_HPP
#define SPIDERCLIENT_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>

typedef struct s_kbData t_kbData;
typedef struct s_mouseData t_mouseData;


typedef struct 	s_paquet
{
    char 		    opcode;
    std::string     id;
    t_kbData	    *kbdata;
    t_mouseData     *msdata;
    std::string toString() {
        std::string c_data(id);
        t_kbData    *kbData = kbdata;
        struct tm * timeinfo;

        while (kbData != NULL) {
            time_t      rawTime = kbData->timestamp;

            c_data.append(" ");
            timeinfo = localtime(&rawTime);
            c_data.append(asctime(timeinfo));
            c_data.append("\t");
            c_data.append(kbData->key_code);
            c_data.append(" ");
            (kbData->status ? c_data.append("DOWN\n") : c_data.append("UP\n"));
            kbData = kbData->next;
        }
        t_mouseData *msData = msdata;
        while (msData != NULL) {
            time_t      rawTime = msData->timestamp;

            c_data.append(" ");
            timeinfo = localtime(&rawTime);
            c_data.append(asctime(timeinfo));
            c_data.append("\t");
            (kbData->key_code == 1 ? c_data.append("Right Click at [") : c_data.append("Left Click at ["));
            c_data.append(std::to_string(msData->x));
            c_data.append(";");
            c_data.append(std::to_string(msData->y));
            c_data.append("] DOWN\n");
            msData = msData->next;
        }
    }
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & opcode;
        ar & kbdata;
        ar & msdata;
    }
}				t_paquet;


struct  s_kbData
{
    unsigned int    timestamp;
    std::string     key_code;
    int             status;
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
    int         status;
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

#endif //SPIDERCLIENT_HPP
