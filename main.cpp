/**
 * Author: Matthias Goldhoorn (matthias.goldhoorn@dfki.de)
 * Company: Deutsches Forschungszentrum für Künstliche Intelligenz - Robotics Innovation Center (DFKI RIC)
 * Year 2010
 * Desc:
 *
*/
#include "dsp3000.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

int main(int argc, char**argv){
	if(argc<2){
		fprintf(stderr,"use \n./ifg_test <device> \n");
		return -1;
	}


	fog_kvh::Dsp3000Driver ifg;
        std::cout << "Trying to open FOG..." << std::endl;
	bool worked = ifg.init(argv[1]);
        if(!worked)
           std::cout << "Could not open FOG on port " << argv[1] << "." << std::endl;
	
        double sum=0;
	timeval last,current;
	int cnt=0;
	double avg=0;
	bool first=true;
	double drift=0;
	double error=0;
	int error_cnt=0;
	double sum_compensated=0;
	static double time=0.010574;//0.01056;
	while(1){
		double delta;
		gettimeofday(&current,0);
		if(!first){
			double gone = (current.tv_sec + current.tv_usec/1000000.0) - (last.tv_sec + last.tv_usec/1000000.0);
			avg+=gone;
			cnt++;
		}
		//iGCInterface::iGCRawData data;
		if(ifg.getState(delta)){
			error_cnt++;
			double drift = -0.00000008098906620711;
			double rot =delta*time;
			double earth_rot = -(sin(53.089480/180.0*M_PI) * 2*M_PI)/ (24.0*60.0*60.0); //in rad/s
			error += rot - earth_rot*time;
			sum_compensated += rot-drift- earth_rot*time;
			sum+=rot - earth_rot*time;
			//printf("delta  %2.2f \t drift: %f (%fh)\tsum: %2.2f Error: %+1.20f \r",delta,sum/(cnt*time),sum/(cnt*time)*60.0*60.0*24.0,sum,error/error_cnt);
			printf("Igc Rotated(normal/compensated): %+1.20f %+1.20f rad, if still then Drift: %+1.20f, avg Update intervall: %+1.10f\r",sum,sum_compensated,error/error_cnt,avg/cnt);
		}
		last=current;
		first=false;
	}

}
