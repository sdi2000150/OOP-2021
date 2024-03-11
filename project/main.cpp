#include <iostream>
#include <ctime>
#include "highway.h"

using namespace std;

int main() {

	long curtime = time(NULL);
	srand((unsigned int)curtime);

	/* Give arguments */
	int N;
	cout << "Please give the amount of stages for this simulation!(give N)" << endl;
	cin >> N;
	while (N <= 0) {
	cout << "Bad Input!!!" << endl << "Please give the amount of stages for this simulation!(give N)" << endl;
	cin >> N;
	}
	
	int NSegs;
	cout << endl << "Please give how many segments our highway has!" << endl;
	cin >> NSegs;
	while (NSegs <= 0) {
	cout << "Bad Input!!!" << endl << "Please give how many segments our highway has!" << endl;
	cin >> NSegs;
	}
	
	int K;
	cout << endl << "Please give how many cars can enter from tolls!(give K)" << endl;
	cin >> K;
	while (K <= 0) {
	cout << "Bad Input!!!" << endl << "Please give how many cars can enter from tolls!(give K)" << endl;
	cin >> K;
	}
	
	int Percent;
	cout << endl << "Please give the percentage of cars that will move to the ready phase, in each stage!" << endl;
	cin >> Percent;
	while (Percent <= 0 && Percent > 100) {
	cout << "Bad Input!!!" << endl << "Please give the percentage of cars that will move to the ready phase, in each stage!" << endl;
	cin >> Percent;
	}
	
	int capacity[NSegs];
	for (int i = 0 ; i < NSegs ; i++) {
		cout << endl << "Please give the capacity of segment: " << i+1 << endl;
		cin >> capacity[i];
		while (capacity[i] <= 0) {
			cout << "Bad Input!!!" << endl << "Please give the capacity of segment: " << i+1 << endl;
			cin >> capacity[i];
		}
	}

	/* Fixed arguments(for faster testing) */
	// int N = 5, NSegs = 8, K = 20, Percent = 20;
	// int capacity[NSegs];
	// for (int i = 0 ; i < NSegs ; i++) {
	// 	capacity[i] = 45;
	// }

	string answer;
	cout << endl << "Is it snowing? (yes or no)" << endl;
	cin >> answer;
	if (answer == "yes") {
		cout << "Highway can't operate..." << endl << " ;) " << endl;
	} else {
		Attiki_Odos highway(NSegs, K, Percent, capacity);

		for (int i = 0 ; i < N ; i++) {
			cout << endl << endl << "Simulation round: " << i+1 << endl << endl;
			highway.operate();
			highway.add_vehicles();
		}
	}

	return 0;
}
