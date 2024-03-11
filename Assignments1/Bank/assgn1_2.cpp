#include <iostream>
#include <cstring>

using namespace std;

class Cashier {
        bool open_flag;
        bool serving_flag;
        int customers_served;

/* extra private data */
        int limit;  //L
    public:
        Cashier(int);
        ~Cashier();
        void open();
        void close();
        void serve();
        bool free();
        bool is_open() const;
        bool is_free() const;
};

class Bank {
        int last_customer;  //xartaki-arithmos proteraiothtas aytounou pou tha mpei teleutaios
        int curr_serving;   //pinakida-autos pou tha eksypiretithei
        Cashier* tameio[5]; //5 tameia(pinakas deiktwn se Cashier wste na mporesei na perastei to L sto kathe tameio mesw constructor)

/* extra private data */
        int ith;    //next cashier to serve
        int next;   //next cashier to be opened
        int kappa;  //K

/* private functions */
        bool check_to_open() const;
        void open(int);
        bool check_to_close() const;
        void close(int);
        void exit();
        int waiting_customers() const;
        int open_cashiers() const;
    public:
        Bank(int, int);
        ~Bank();
        bool enter();
        void serve();
};

int main(int argc, char *argv[]) {
    int K = atoi(argv[1]), M = atoi(argv[2]), N = atoi(argv[3]), L = atoi(argv[4]);
    cout << "K=" << K << " M=" << M << " N=" << N << " L=" << L << endl;

/* a' erwthma */
    Bank trapeza(L,K);

/* b' erwthma */
    int waiting_to_enter = 0;
    int w1;
    for (int j = 0 ; j < M ; j++) { //h diadikasia epanalamvanetai M fores
        w1 = 0;
        for (int i = 0 ; i < N ; i++) {     //N pelates
            if (trapeza.enter() == false) { //eiserxontai, kai osoi den kataferoun na eiselthoun
                waiting_to_enter++;         //tous metrame se enan synoliko metrhth,
                w1++;                       //tous metrame kai se enan metrhth pou afora tin sygkekrimenh megalh for(tou M)
            }
        }
        for (int k = 0 ; k < N - w1 ; k++) {    //N-w1 pelates, diladi osoi ekanan enter stin sygkekrimenh megalh for(tou M)
            trapeza.serve();                    //ginontai serve
        }
    }

/* g' erwthma */
    cout << endl << "Waiting to enter: " << waiting_to_enter << endl;   //synolikos metrhths autwn pou den kataferan na eiselthoun
    if (waiting_to_enter > 0) {
        cout << "Entering and serving these waiting customers:" << endl << endl;
    }

    int w2;
    do {
        w2 = 0;
        for (int i = 0 ; i < waiting_to_enter ; i++) {
            if (trapeza.enter() == false) {
                w2++;
            }
        }
        for (int k = 0 ; k < waiting_to_enter - w2 ; k++) {
            trapeza.serve();
        }
        waiting_to_enter = w2;  
    } while (w2 > 0);   //epanalamvanoume mexri na kanoun enter kai serve oloi oi pelates

    cout << endl << "Everybody was served" << endl << endl;

    return 0;
}

/* Class Cashier functions */

Cashier::Cashier(int L) {
    open_flag = false;
    serving_flag = false;
    limit = L;
    cout << "Creating a cashier" << endl;
}

Cashier::~Cashier() {
    cout << "Destroying a cashier" << endl;
}

void Cashier::open() {
    open_flag = true;
    customers_served = 0;
}

void Cashier::close() {
    open_flag = false;
}

void Cashier::serve() {
    serving_flag = true;
}

bool Cashier::free() {
    serving_flag = false;
    customers_served++;
    if (customers_served == limit) { //limit = L
        cout << "The cashier overworked, it's closing now" << endl;
        return false; //open_flag = false;
    } else {
        return true;
    }
}

bool Cashier::is_open() const {
    return open_flag;
}

bool Cashier::is_free() const {
    return !serving_flag;
}

/* Class Bank functions */

bool Bank::check_to_open() const {
    if (waiting_customers() > open_cashiers()*kappa) { //kappa = K
        return true;
    } else {
        return false;
    }
}

void Bank::open(int index) {
    tameio[index]->open();
    cout << "Cashier no: " << index+1 << " opened" << endl;
}

bool Bank::check_to_close() const {
    if (waiting_customers() <= (open_cashiers()-1)*kappa) { //kappa = K
        return true;
    } else {
        return false;
    }
}

void Bank::close(int index) {
    tameio[index]->close();
    if (open_cashiers() == 0) {
        next = 0;   //an ola ta tameia ekleisan, tote to next cashier to be opened ginetai to 1o
    }
    cout << "Cashier no: " << index+1 << " closed" << endl;
}

void Bank::exit() {
    curr_serving++;
    if (check_to_close() == true) {             //an ta tameia pleonazoun
        int i = 0;
        bool flag = false;
        while (i < 5 && flag == false) {        //apo to 1o mexri to 5o tameio
            if (tameio[i]->is_open() == true) { //kleinei to prwto anoixto tameio pou tha vrei
                close(i);
                flag = true;
            }
            i++;
        }
    }
}

int Bank::waiting_customers() const {
    return (last_customer - curr_serving);
}

int Bank::open_cashiers() const {
    int anoixta = 0;
    for (int i = 0 ; i < 5 ; i++) {
        if (tameio[i]->is_open() == true) {
            anoixta++;
        }
    }
    return anoixta;
}

Bank::Bank(int L, int K) {
    for (int i = 0 ; i < 5 ; i++) {
        tameio[i] = new Cashier(L);
    }
    last_customer = 1;
    curr_serving = 1;
    kappa = K;
    ith = 0;    //next cashier to serve ginetai to 1o
    cout << "Creating a bank" << endl << endl;
    open(0);    //anoigei to 1o tameio
    next = 1;   //next cashier to be opened ginetai to 2o
}

Bank::~Bank() {
    for (int i = 0 ; i < 5 ; i++) {
        delete tameio[i];
    }
    cout << "Destroying a bank" << endl;
}

bool Bank::enter() {
    if (check_to_open() == false) {
        last_customer++;
    } else {
        if (open_cashiers() == 5) {
            cout << "Sorry you cannot enter until some customers are served!" << endl;
            return false;
        } else {
            open(next); //anoigei to tameio next
            last_customer++;
            if (next < 4) {
                next++;     //next cashier to be opened ginetai to epomeno
            } else {
                next = 0;   //h to 1o an anoikse to 5o
            }
        }
    }
    return true;
}

void Bank::serve() {
    if (open_cashiers() == 0) {
        open(0);    //anoigei to 1o tameio
        next = 1;   //next cashier to be opened ginetai to 2o
        cout << "Customer no: " << curr_serving << " served by cashier no: " << 1 <<endl;
        tameio[0]->serve();
        if (tameio[0]->free() == false) {
            close(0);
        }
        ith = 1;    //next cashier to serve ginetai to 2o
    } else {
        int i = 0;
        bool flag = false;
        while (i < 5 && flag == false) {
            if ((tameio[ith]->is_open() == true) && (tameio[ith]->is_free() == true)) {
                cout << "Customer no: " << curr_serving << " served by cashier no: " << ith+1 <<endl;
                tameio[ith]->serve();
                if (tameio[ith]->free() == false) {
                    close(ith);
                }
                flag = true;
            }
            if (ith < 4) {
                ith++;      //next cashier to serve ginetai to epomeno
            } else {
                ith = 0;    //h to 1o an ekane serve to 5o
            }
            i++;
        }
    }
    exit();
}