#ifndef TIMELIMITED_H_
#define TIMELIMITED_H_

//A timer oriented class
// all units are in milliseconds
class TimeLimited
{
protected:
	unsigned int _startTime;
	unsigned int _duration;
public:
	TimeLimited(unsigned int duration);
	virtual ~TimeLimited();
	void start();
	float getPercentComplete();
	bool isComplete();

	void setMaxTime(unsigned int duration) { _duration = duration; };
};

#endif /*TIMELIMITED_H_*/
