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
