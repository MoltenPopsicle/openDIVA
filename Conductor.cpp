#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

using std::cin;
using std::cout;

double getCurrentBeat(int timeDiffInMs, int bpm) {
	
	auto timeDiffInMin = (double) timeDiffInMs / 1000 / 60;
	return timeDiffInMin * bpm;
}

double getTotalBeats(double lengthInS, int bpm) {
	return (lengthInS / 60) * bpm;
}

class Conductor {
	int _bpm;
	int _offsetInMs;
	double _lengthInS;
	
	void refreshMembers();	

	public:
		std::chrono::high_resolution_clock::time_point startTime;
		std::chrono::high_resolution_clock::time_point currTime;
		std::chrono::milliseconds timeDiff;
		double totalBeats;
		double offsetBeats;
		double currBeat;

		Conductor(int bpm, double lengthInS, int offsetInMs) {
			_bpm = bpm;
			_lengthInS = lengthInS;
			_offsetInMs = offsetInMs;
			startTime = std::chrono::high_resolution_clock::now(); 
			totalBeats = getTotalBeats(_lengthInS, _bpm) - offsetBeats; 
			offsetBeats = getTotalBeats((double) _offsetInMs / 1000, _bpm);
		}

		void conduct();
};

void Conductor::refreshMembers() {
	currTime = std::chrono::high_resolution_clock::now(); 
	timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - startTime);
	currBeat = getCurrentBeat(timeDiff.count(), _bpm) - offsetBeats;
}

void Conductor::conduct() {
	auto startTimeT = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
	time_t currTimeT;
	while(timeDiff.count() / 1000 < _lengthInS) {
		refreshMembers();
		currTimeT = std::chrono::system_clock::to_time_t(currTime);
		cout << "Start time (s): " << startTimeT;
		cout << "\nCurrent time (s): " << currTimeT;
		cout << "\nOffset (ms): " << _offsetInMs;
		cout << "\nTime (s): " << (double) timeDiff.count() / 1000 << " / " << _lengthInS;
		cout << "\nOffset beats: " << offsetBeats;
		cout << "\nCurrent beat: " << currBeat << " / " << totalBeats << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		std::system("clear");
	}
}

int main(int argc, char **argv) {
	int bpm = std::stoi(argv[1]);
	double lengthInS = std::stod(argv[2], NULL);
	int offsetInMs = std::stoi(argv[3]);

	Conductor conductor(bpm, lengthInS, offsetInMs);
	conductor.conduct();
	return 0;

}
