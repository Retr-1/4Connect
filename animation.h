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

template <typename T> 
class QuadraticAnimation : public LinearAnimation<T> {
public:
	float velocity = 0;
	//float total_elapsed = 0.5;

	using LinearAnimation<T>::LinearAnimation;

	void update(float fElapsedTime) {
		this->progress += velocity * fElapsedTime;
		velocity += this->speed * fElapsedTime;
		//std::cout << velocity << " vl\n";
		//this->progress += std::pow(5, total_elapsed);
		//total_elapsed += fElapsedTime;
	}
};