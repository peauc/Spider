//
// Created by lavigne on 10/5/17.
//

#ifndef TEST_SPIDER_H
#define TEST_SPIDER_H

typedef struct 	s_paquet
{
    char 		opcode;
    void		*data;
}				t_paquet;


typedef struct  s_kbData
{
    int         timestamp;
    int         key_code;
}		        t_kbData;

typedef struct  s_mouseData
{
    int         timestamp;
    int         key_code;
    int         x;
    int         y;
}               t_mouseData;

#endif //TEST_SPIDER_H_H
