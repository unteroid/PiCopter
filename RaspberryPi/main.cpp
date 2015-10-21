#include <iostream>
#include <time.h>
#include <cstdint>
#include <unistd.h>

using namespace std;

int main() {
	float dt;
	timespec curTime, oldTime;
	clock_gettime(CLOCK_REALTIME, &curTime);	
	
	for(int64_t i = 100000; i < 10000000; i=i+100000) {
		oldTime = curTime;
		clock_gettime(CLOCK_REALTIME, &curTime);
		dt = ( (static_cast<int64_t>(curTime.tv_sec)*1000000000 + static_cast<int64_t>(curTime.tv_nsec)) - (static_cast<int64_t>(oldTime.tv_sec)*1000000000 + static_cast<int64_t>(oldTime.tv_nsec)) ) /1000000000.0;
		usleep(i);
		cout << dt << endl;
		cout.precision(22);
		cout << dt << endl;
		//cout << dt << endl;
		
		
		
}

	
	return 0;
}
