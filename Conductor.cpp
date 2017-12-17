#include <iostream>
#include <chrono>
#include <ctime>

using std::cin;
using std::cout;

class Conductor {
	public:
		int _bpm;

		Conductor(int bpm) {
			_bpm = bpm;
		}

		void returnCurrentBeat();
};

void Conductor::returnCurrentBeat() {
	auto startTime = std::chrono::high_resolution_clock::now(); 
	auto startTimeT = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
	//auto startTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>((startTime + startTime) - startTime);
	char c;

	while(c = cin.get()) {
		auto newTime = std::chrono::high_resolution_clock::now(); 
		auto newTimeT = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
	//auto newTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>((newTime + newTime) - newTime);
		auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - startTime);
		cout << "Start time: " << startTimeT << '\n' << "New time: " << newTimeT << '\n' << "Time difference: " << timeDiff.count() << '\n';
	}
}

int main() {
	Conductor conduct(100);
	conduct.returnCurrentBeat();
	return 0;
}
