
#include "HeaderFiles/FeederSchedule.h"

FeederSchedule::FeederSchedule(){
	moments_count = 0;
	current_moment_index = -1;
}

FeederSchedule::~FeederSchedule(){
	delete[] moments;
}

void FeederSchedule::add_moment(int hr, int min, int amount){
	if (hr > 23 || hr < 0 || min >59 || min < 0 || amount < 0) return;
	if (!check_uniqueness(hr, min)) return;
	FeedMoment* new_moment = new FeedMoment(hr, min, amount);
	if (moments_count == 0) {
		moments = new FeedMoment*[1];
		moments_count++;
		current_moment_index++;
		moments[0] = new_moment;
		return;
	}
	int index = 0;
	FeedMoment** new_moments = new FeedMoment*[moments_count + 1];

	while (index < moments_count && moments[index]->time_in_minutes < new_moment->time_in_minutes) {
		new_moments[index] = moments[index];
		index++;
	}
	new_moments[index] = new_moment;
	for (int i = index+1; i < moments_count; i++) {
		new_moments[i] = moments[i - 1];
	}
	delete moments;
	moments = new_moments;
	moments_count++;
	if (current_moment_index > index) current_moment_index++;

}

FeedMoment * FeederSchedule::get_current_moment(){
	if (current_moment_index == -1) return 0;
	return moments[current_moment_index];
}

FeedMoment ** FeederSchedule::get_moments(){
	return this->moments;
}

int FeederSchedule::get_moments_count(){
	return moments_count;
}

void FeederSchedule::next(){
	current_moment_index++;
	current_moment_index %= moments_count;
}

void FeederSchedule::reset(){
	for (int i = 0; i < moments_count; i++) {
		delete moments[i];
	}
	delete moments;
	moments_count = 0;
	current_moment_index = 0;
}

int FeederSchedule::removemoment(int hr, int min){
	int remove_index = -1;

	for (int i = 0; i < moments_count; i++) {
		if (moments[i]->minute == min && moments[i]->hour== hr) {
			remove_index = i;
		}
	}
	if (remove_index < 0)
		return remove_index;
	FeedMoment** new_moments = new FeedMoment*[moments_count-1];
	for (int i = 0; i < remove_index; i++) {
		new_moments[i] = moments[i];
	}
	for (int i = remove_index+1; i < moments_count; i++) {
		new_moments[i-1] = moments[i];
	}
	delete moments[remove_index];
	delete[] moments;
	moments = new_moments;
	moments_count--;
	if (current_moment_index > remove_index) current_moment_index--;
	return remove_index;
}

int FeederSchedule::check_uniqueness(int hr, int min){
	for (int i = 0; i < moments_count; i++) {
		if (moments[i]->time_in_minutes == (24 * hr + min)) return 0;
	}
	return 1;
}

void FeederSchedule::set_last_update(long update) {
	last_update_unix = update;
}

long FeederSchedule::get_last_update(){
	return last_update_unix;
}