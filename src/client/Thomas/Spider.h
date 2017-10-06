//
// Created by lavigne on 10/5/17.
//

#ifndef TEST_SPIDER_H
#define TEST_SPIDER_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>

typedef struct s_kbData t_kbData;
typedef struct s_mouseData t_mouseData;

typedef struct 	s_paquet
{
    char 		    opcode;
    t_kbData	    *kbData;
    t_mouseData     *mouseData;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & opcode;
        ar & kbData;
        ar & mouseData;
    }
}				t_paquet;


struct  s_kbData
{
    unsigned int    timestamp;
    int             key_code;
    struct s_kbData *next;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & timestamp;
        ar & key_code;
        ar & next;
    }
};

struct  s_mouseData
{
    int         timestamp;
    int         key_code;
    int         x;
    int         y;
    struct s_mouseData  *next;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & timestamp;
        ar & key_code;
        ar & x;
        ar & y;
        ar & next;
    }
};

#endif //TEST_SPIDER_H_H
