#include "cub3d.h"

long get_time()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec - g_start_time.tv_sec) * 1000000) 
		+ (curr_time.tv_usec - g_start_time.tv_usec);
}

void count_frame_per_sec()
{
	static struct timeval start_time;
	static int count; 
	struct timeval curr_time;
	long res;
	
	if (count == 0)
		gettimeofday(&start_time, NULL);
	count++;
	gettimeofday(&curr_time, NULL);
	res = ((curr_time.tv_sec - start_time.tv_sec) * 1000000) 
		+ (curr_time.tv_usec - start_time.tv_usec);
	if (res >= 1000000)
	{
		printf("%d\n", count);
		count = 0;
	}
}

void limit_frame_speed()
{
	static int render;
	long sleep;
	long time;

	time = get_time();
	sleep = 1000000 / FRAME_PER_SEC;
	sleep = (sleep * render) - time;
	if (sleep > 0 && sleep < 1000000 / FRAME_PER_SEC)
		usleep(sleep);
	if (render == FRAME_PER_SEC)
	{
		render = 0;
		gettimeofday(&g_start_time, NULL);
	}
	render++;
}
