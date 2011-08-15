/**
 * Author: Matthias Goldhoorn (matthias.goldhoorn@dfki.de)
 * Company: Deutsches Forschungszentrum für Künstliche Intelligenz - Robotics Innovation Center (DFKI RIC)
 * Year 2010
 * Desc:
 *
*/
#ifndef _DSP3000DRIVER_H_
#define _DSP3000DRIVER_H_ 

#include <iodrivers_base.hh>

namespace fog_kvh{

class Dsp3000Driver : public IODriver 
{

public:

	Dsp3000Driver();
	~Dsp3000Driver();
	int getReadFD();
	bool init(std::string const &port);
	/**
	 * Returns the rotation value in radians default in Rate.
	 * See KVH DSP 3000 Manual
	 */
	bool getState(double &delta);
	/*
	 * May need to send more than 1 times, sorry no way to figure out in wich mode we are
	 */
	bool toIntegradted();
	/*
	 * May need to send more than 1 times, sorry no way to figure out in wich mode we are
	 */
	bool toRate();
	/*
	 * May need to send more than 1 times, sorry no way to figure out in wich mode we are
	 */
	bool toIncremental();
	/*
	 * May need to send more than 1 times, sorry no way to figure out in wich mode we are
	 */
	bool reset();

private:
	static const int MAX_PACKET_SIZE = 256;
	virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;

};

};

#endif
