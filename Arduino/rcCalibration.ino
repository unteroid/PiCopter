
void rcDeadZone(int* uncalib_time, float* percent) 
{
// adding dead zone
	if ((*uncalib_time >= (RC_MID - DEAD_ZONE) ) && (*uncalib_time <= (RC_MID + DEAD_ZONE) )) 
	{
		*uncalib_time = RC_MID; 
	} 
	else if (*uncalib_time > (RC_MID + DEAD_ZONE) ) 
	{
		*uncalib_time = *uncalib_time - DEAD_ZONE;
	} 
	else if (*uncalib_time < (RC_MID - DEAD_ZONE) ) 
	{
		*uncalib_time = *uncalib_time + DEAD_ZONE; 
	}

	//convertation to percent
	*percent = (float)(*uncalib_time - RC_MIN)/(RC_MAX - RC_MIN)*100;
	//setting a saturation of 0 and 100 %
	if (*percent < 0) 
	{
		*percent = 0;
	}
	else if (*percent > 100) 
	{
		*percent = 100;
	}
}

