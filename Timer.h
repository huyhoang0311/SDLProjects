#pragma once
#ifndef TIMER_H
#define TIMER_H
class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();


	bool is_paused();
	bool is_started();


private:
	int start_tick_;
	int paused_tick;


	bool is_paused_;
	bool is_started_;
};








#endif