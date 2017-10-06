#pragma once
#ifndef KBDATA_HPP_
#define KBDATA_HPP_

#include <ctime>


/*
 * Data Structure for Keyboard datas
*/
struct KBData
{
public:
	int keycode;
	int status; // 1 = down , up = 2;
	std::time_t time;

	KBData()
	{

	}

	KBData(int k, int s, std::time_t t)
	{
		this->keycode = k;
		this->time = t;
		this->status = s;
	}
};

#endif