/**
 * Author: Matthias Goldhoorn (matthias.goldhoorn@dfki.de)
 * Company: Deutsches Forschungszentrum für Künstliche Intelligenz - Robotics Innovation Center (DFKI RIC)
 * Year 2010
 * Desc:
 *
*/
#include "dsp3000.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <cstdio>
#include <math.h>

namespace fog_kvh{

Dsp3000Driver::Dsp3000Driver():
	IODriver(512,false){

}

bool Dsp3000Driver::init(std::string const &port){
		return openSerial(port,38400);
}

Dsp3000Driver::~Dsp3000Driver() {

}

int Dsp3000Driver::getReadFD() {
	return getFileDescriptor();
}


bool Dsp3000Driver::toRate(){
	uint8_t buff[3];
	buff[0] = 'R';
	buff[1] = '\n';
	buff[2] = 0;
	return writePacket(buff,2,80);
}

bool Dsp3000Driver::toIncremental(){
	uint8_t buff[3];
	buff[0] = 'A';
	buff[1] = '\n';
	buff[2] = 0;
	return writePacket(buff,2,80);
}

bool Dsp3000Driver::toIntegradted(){
	uint8_t buff[3];
	buff[0] = 'P';
	buff[1] = '\n';
	buff[2] = 0;
	return writePacket(buff,2,80);
}


bool Dsp3000Driver::reset(){
	uint8_t buff[3];
	buff[0] = 'Z';
	buff[1] = '\n';
	buff[2] = 0;
	return writePacket(buff,2,80);
}

bool Dsp3000Driver::getState(double &delta){
    try {
	int bufsize = 512;
	uint8_t packed[bufsize];
	if(readPacket(packed,bufsize,80,80) != 21){
		fprintf(stderr,"Cannot parse packed, unknown length\n");
		printf("Packed kaputt\n");	
		return false;
	}
	int pos=0;
	while(packed[pos+1] == 0x20 && pos<21)pos++;
	if(pos>=21) return false;

	float i=0;
	sscanf((const char*)packed+pos,"%f",&i);
	i = i/180.0*M_PI;
	delta = -i;
	return true;
    } catch (timeout_error) { return false; }
}


int Dsp3000Driver::extractPacket(uint8_t const* buffer, size_t buffer_size) const {
		if(buffer_size<21){
			return 0; //Packed is never complete yet complete yet
		}
		if(buffer[19] == '\r' && buffer[20] == '\n'){
			return 21;
		}
		return -1;
}

}
