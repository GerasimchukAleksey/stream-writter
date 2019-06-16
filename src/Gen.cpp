// #include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <numeric>

class Gen {
public:
	//----------------------------------
	//! Constructor
	//----------------------------------
	Gen(std::string source) : source(source), speed(0), pos(0), prev_time(std::chrono::system_clock::now()){
		std::ifstream ist{ get_source() };
		if (!ist) {
			std::cout << "CAN'T OPEN FILE" << std::endl;
			return;
		}
		uint8_t data;
		while (ist >> data) {
			buf.push_back(data);
		}
	}

	//----------------------------------
	//! Destructor
	//----------------------------------
	~Gen() {}

	//----------------------------------
	//! Cyclic reading from file
	//----------------------------------
	int read(uint8_t *dest, int size) {
		int buf_size = buf.size();
		if (buf_size == 0)
			return 0;
		int i = 0;
		while(i < size) {
			dest[i] = buf[pos];
			++i;
			if (++pos == buf_size)
				pos = 0;
		}

		//time
		std::chrono::duration<double> speed_time(speed);
		std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end_time - prev_time;
		while (diff < speed_time) {
			end_time = std::chrono::system_clock::now();
			diff = end_time - prev_time;
		}
		prev_time = end_time;
		return i;
	}

	//----------------------------------
	//! File source setter
	//----------------------------------
	void set_source(std::string s) {
		source = s;
	}

	//----------------------------------
	//! File source getter
	//----------------------------------
	std::string get_source() {
		return source;
	};

	//----------------------------------
	//! Reading speed setter
	//----------------------------------
	void set_speed(double s) {
		speed = s;
	};

	//----------------------------------
	//! Reading speed getter
	//----------------------------------
	double get_speed() {
		return speed;
	};

//private:
	std::string source;												//source file
	double speed;													//read speed in seconds
	std::vector<uint8_t> buf;										//uint8_t buffer
	int pos;														//read position
	std::chrono::time_point<std::chrono::system_clock> prev_time;	//previous reading time
};