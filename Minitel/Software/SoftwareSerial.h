#ifndef SOFTWARE_SERIAL
#define SOFTWARE_SERIAL

#include <Arduino.h>

/*
 * Emulation of the part of the Arduino API used by Minitel.h/Minitel.cpp
 * Bruno Levy 2022
 */

namespace Serial {
    inline void println(int x) {
	printf("%d\n",x);
    }
}

class SoftwareSerial {
public:

    SoftwareSerial(int rx=-1, int tx=-1) {
	fildes_ = 1;
    }
    
    ~SoftwareSerial() {
	if(fildes_ != -1) {
	    close(fildes_);
	    fildes_ = -1;
	}
    }

    void begin(int bauds) {
    }
    
    byte read() {
	byte b;
	::read(fildes_, &b, 1);
	return b;
    }
   
    void write(byte b) {
        b &= 127; // remove parity bit
	::write(fildes_, &b, 1);
    }
   
    void listen() {
       // TODO
    }
   
   
private:
    int fildes_;
};

#endif
