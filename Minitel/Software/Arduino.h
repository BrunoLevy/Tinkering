#ifndef ARDUINO_H
#define ARDUINO_H

/*
 * Emulation of the part of the Arduino API used by Minitel.h/Minitel.cpp
 * Bruno Levy 2022
 */

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/times.h>

class String : public std::string {
public:
    
    String(const char* c) : std::string(c) {
    }

    char charAt(int i) const {
	return (*this)[i];
    }
    
    int lastIndexOf(char c) const {
	for(int i=length()-1; i>0; --i) {
	    if((*this)[i] == c) {
		return i;
	    }
	}
	return -1;
    }
    
    int indexOf(char c) const {
	for(int i=0; i<length(); ++i) {
	    if((*this)[i] == c) {
		return i;
	    }
	}
	return -1;
    }
};

typedef uint8_t byte;
typedef bool boolean;


inline void delay(unsigned long milliseconds) {
    usleep(useconds_t(milliseconds)*1000);
}

inline unsigned long millis() {
    tms now_tms;
    return times(&now_tms) * 10.0;
}


inline int bitRead(byte b, int bit) {
    return b & (byte(1u) << bit);
}

inline void bitWrite(byte& b, int bit, int val) {
    b |= (byte(1u) << bit);
}


#endif
