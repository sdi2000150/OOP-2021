#include <iostream>
#include <cstring>
#include <ctime>
#include "creatures.h"

using namespace std;

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]), M = atoi(argv[2]), L = atoi(argv[3]), good_thrsh = atoi(argv[4]), bad_thrsh = atoi(argv[5]);
    cout << "N=" << N << " M=" << M << " L=" << L << " good_thrsh=" << good_thrsh << " bad_thrsh=" << bad_thrsh << endl;

    long curtime = time(NULL);      //kaleitai h time gia tin arxikopoihsh tou curtime
    srand((unsigned int) curtime);  //kaleitai h srand (mia fora twra stin arxi - xrisimeuei gia tin rand se diafora merh tou programmatos)

    /* a' erwthma */
    creature_society koinothta(N,L,good_thrsh,bad_thrsh);
    // koinothta.print();   //print the society for testing

    /* b' erwthma */
    int seat, action;
    for (int i = 0 ; i < M ; i++) {
        seat = rand() % N;
        action = rand() % 2 + 1;
        if (action == 1) {
            koinothta.beat(seat);
        } else {
            koinothta.bless(seat);
        }
        // koinothta.print();   //print the society for testing
    }

    /* g' erwthma */
    if (koinothta.no_of_good() == N) {
        cout << "Good Dominates in the World!" << endl;
    } else if (koinothta.no_of_zobies() == N) {
        cout << "This is a dead society" << endl;
    } else {
        cout << "Try again to improve the world" << endl;
    }


    // koinothta.print();   //print the society for testing

    return 0;
}