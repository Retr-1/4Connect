#pragma once
template <typename T>
class LinearAnimation {
public:
	int start;
	int end;
	float progress = 0;
	float speed;
	bool finished = false;
	T data;

	LinearAnimation(int start, int end, float speed, T data) {
		this->start = start;
		this->end = end;
		this->speed = speed;
		this->data = data;
		this->progress = start;
	}

	void update(float fElapsedTime) {
		progress += speed * fElapsedTime;
	}

	int get() {
		if (progress >= end) {
			progress = end;
			finished = true;
		}
		//return (end - start) * progress + start;
		return progress;
	}
};