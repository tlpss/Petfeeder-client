// FeederSchedule.h

#ifndef _FEEDERSCHEDULE_h
#define _FEEDERSCHEDULE_h


class FeedMoment {
public: // no getters...
	int hour, minute;
	int amount;
	long time_in_minutes; //size metric
public:
	FeedMoment(int hr, int min, int amount) : hour(hr), minute(min), amount(amount) { 
		time_in_minutes = hour * 60 + minute;
	}

	bool operator<(FeedMoment& m) {
		return this->time_in_minutes < m.time_in_minutes;
	}

};

class FeederSchedule {
 protected:
	 FeedMoment ** moments;
	 int moments_count;
	 int current_moment_index;
	 long last_update_unix;

 public:
	 FeederSchedule();
	 ~FeederSchedule();
	 void add_moment(int hr, int min, int amount);
	 FeedMoment* get_current_moment();
	 FeedMoment** get_moments();
	 int get_moments_count();
	 void next();
	 void reset();
	 int removemoment(int hr, int min);
	 long get_last_update();
	 void set_last_update(long update);
private:
	int check_uniqueness(int hr, int min);
	
};



#endif

