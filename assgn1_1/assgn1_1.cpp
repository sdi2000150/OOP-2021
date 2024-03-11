#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

class Book {
        string title;
        string writer;
        int ESBN;
    public:
        Book(string x = "Untitled", string y = "Unnamed", int z = 0) : title(x), writer(y), ESBN(z) { }
        ~Book() { }
        string get_title() const { return title; }
        string get_writer() const { return writer; }
        int get_ESBN() const { return ESBN; }
};

class Shelf {
        Book** biblia;
        int shelfbooks; //counter of the books in the shelf
        int maxnum;
    public:
        Shelf(int);
        ~Shelf();
        bool place_book(Book*);
        bool take_book();
        void print() const;
};

class Closet {
        Shelf mesarafi1;
        Shelf mesarafi2;
    public:
        Closet(int);
        ~Closet();
        void place_book(Book*, int);
        void take_book(int);
        void print() const;
};

class Base {
    public:
        Base() { cout << "Creating a Base" << endl; }
        ~Base() { cout << "Destroying a Base" << endl; }
};

class Bookcase {
        Base basi;
        Closet ntoulapi;
        Shelf rafi1;
        Shelf rafi2;
        Shelf rafi3;
        int N;  //counter of the books in the bookcase 
    public:
        Bookcase(int);
        ~Bookcase();
        void place_book(Book*, int);
        void take_book(int);
        void print() const;
};

/* Random names generator (400 possible combinations) */
string writer_gen() {
    string first[20] = {"James","Robert","John","Michael","William","David","Richard","Joseph","Thomas","Charles",
                    "Mary","Patricia","Jennifer","Linda","Elizabeth","Barbara","Susan","Jessica","Sarah","Karen"};
    string last[20] = {"Smith","Johnson","Williams","Brown","Jones","Garcia","Miller","Davis","Rodriguez","Martinez",
                    "Hernandez","Lopez","Gonzalez","Wilson","Anderson","Thomas","Taylor","Moore","Jackson","Martin"};
    string writer;
    writer = first[rand() % 20];
    writer += " ";
    writer += last[rand() % 20];
    return writer;
}

/* Random titles generator (30 possible options) */
string title_gen() {
    string titles[30] = {"Dinception","No time to di","Mean Busses","The diparted","The Dit Knight","Lesxh:The Missing Pieces","Dinterstellar",
                    "Road to Ptyxio","Ditkirk","Eth. Antistaseos Hooligans","Diango Unchained","Once upon a time in NKUA","Baloo: A Cat's Tale",
                    "Dit Fiction","250:A Bus Odyssey","7 years later","Papagou Drive","Bus Runner 680","The Good, the Bad and the Webmail",
                    "Midnight in Panepistimioupoli","The Grand Zografou Department","The MyStudies Redemption","The Road to Eksetastikh","True Ditective",
                    "The Ghost Programmer","Lock, Stock and 7 xronia gia ptyxio","Children of delos","Motorcycle DIaries","Paths of eClass","The Webex show"};
    string title;
    title = titles[rand() % 30];
    return title;
}

int main(int argc, char *argv[]) {
    int NMax = atoi(argv[1]), L = atoi(argv[2]), K1 = atoi(argv[3]), K2 = atoi(argv[4]);
    cout << "NMax=" << NMax << " L=" << L << " K1=" << K1 << " K2=" << K2 << endl;

    long curtime = time(NULL);      //kaleitai h time gia tin arxikopoihsh tou curtime
    srand((unsigned int) curtime);  // kaleitai h srand (mia fora twra stin arxi - xrisimeuei gia tin rand se diafora merh tou programmatos)

/* a' erwthma */
    Bookcase bibliothiki(NMax);

/* b' erwthma */
    Book** biblio;
    biblio = new Book*[L];
    for (int i = 0 ; i < L ; i++) {
        biblio[i] = new Book(title_gen(), writer_gen(), rand() % 1000 + 1);      
    }

/* g' erwthma */
    cout << endl;
    int index, j = 0, l = 0;
    bool flag = true;
    while ( j < K1 && flag == true) {
        if (l < L) {
            index = rand() % 5 + 1;
            bibliothiki.place_book(biblio[l], index);
            l++;
        } else {
            cout << "No more books to place" << endl;
            flag = false;   //end loop
        }
        j++;
    }
    cout << endl;

/* d' erwthma */
    for (j = 0 ; j < K2 ; j++) {
        index = rand() % 5 + 1;
        bibliothiki.take_book(index);
        l--;
    }
    cout << endl;

/* e' erwthma */
    bibliothiki.print();
    cout << endl;


    for (int i = 0 ; i < L ; i++) {
        delete biblio[i];
    }
    delete[] biblio;

    return 0;
}

/* Class Shelf functions */

Shelf::Shelf(int nmax) : maxnum(nmax) {
    cout << "Creating a Shelf" << endl;
    shelfbooks = 0;
    biblia = new Book*[maxnum];
    for (int i = 0 ; i < maxnum ; i++) {
        biblia[i] = NULL;
    }
}

Shelf::~Shelf() {
    cout << "Destroying a Shelf" << endl;
    delete[] biblia;
}

bool Shelf::place_book(Book* biblio) {
    if (shelfbooks < maxnum) {
        biblia[shelfbooks] = biblio;
        shelfbooks++;
        cout << "   Title: " << biblio->get_title() << " ,Writer: " << biblio->get_writer() << " ,ESBN: " << biblio->get_ESBN() << endl;
        return true;
    } else {
        return false;
    }
}

bool Shelf::take_book() {
    if (shelfbooks > 0 ) {
        biblia[shelfbooks] = NULL;
        shelfbooks--;
        return true;
    } else {
        return false;
    }
}

void Shelf::print() const{
    if (shelfbooks > 0) {
        for (int i = 0 ; i < shelfbooks ; i++) {
            cout << "   Title: " << biblia[i]->get_title() << " ,Writer: " << biblia[i]->get_writer() << " ,ESBN: " << biblia[i]->get_ESBN() << endl;
        }
    } else {
        cout << "   " << "Nothing to print! Shelf is empty" << endl;
    }
}

/* Class Closet functions */

Closet::Closet(int nmax) : mesarafi1(nmax), mesarafi2(nmax) {
    cout << "Creating a Closet" << endl;
}

Closet::~Closet() {
    cout << "Destroying a Closet" << endl; 
}

void Closet::place_book(Book* biblio, int number) {
    switch(number) {
        case 1 :    if (mesarafi1.place_book(biblio) == false) {
                        cout << "Couldn't place! 1st INNER shelf is full" << endl;
                    }
                    break;
        case 2 :    if (mesarafi2.place_book(biblio) == false) {
                        cout << "Couldn't place! 2nd INNER shelf is full" << endl;
                    }
                    break;
    }
}

void Closet::take_book(int number) {
    switch(number) {
        case 1 :    if (mesarafi1.take_book() == false) {
                        cout << "Couldn't take! 1st INNER self is empty" << endl;
                    }
                    break;
        case 2 :    if (mesarafi2.take_book() == false) {
                        cout << "Couldn't take! 2nd INNER self is empty" << endl;
                    }
                    break;
    }
}

void Closet::print() const{
    cout << "Printing the books from 1st INNER shelf:" << endl;
    mesarafi1.print();
    cout << "Printing the books from 2nd INNER shelf:" << endl;
    mesarafi2.print();
}

/* Class Bookcase functions */

Bookcase::Bookcase(int nmax) : ntoulapi(nmax), rafi1(nmax), rafi2(nmax), rafi3(nmax) {
    cout << "Creating a Bookcase" << endl;
    N = 0;
}

Bookcase::~Bookcase() {
    cout << "Destroying a Bookcase" << endl;
}

void Bookcase::place_book(Book* biblio, int number) {
    switch(number) {
        case 1 :    cout << "Placing book in 1st OUTER self:" << endl;
                    if (rafi1.place_book(biblio) == false) {
                        cout << "Couldn't place! 1st OUTER shelf is full" << endl;
                    }
                    N++;
                    break;
        case 2 :    cout << "Placing book in 2nd OUTER self:" << endl;
                    if (rafi2.place_book(biblio) == false) {
                        cout << "Couldn't place! 2nd OUTER shelf is full" << endl;
                    }
                    N++;
                    break;
        case 3 :    cout << "Placing book in 3rd OUTER self:" << endl;
                    if (rafi3.place_book(biblio) == false) {
                        cout << "Couldn't place! 3rd OUTER shelf is full" << endl;
                    }
                    N++;
                    break;
        case 4 :    cout << "Placing book in 1st INNER self:" << endl;
                    ntoulapi.place_book(biblio, 1);
                    N++;
                    break;
        case 5 :    cout << "Placing book in 2nd INNER self:" << endl;
                    ntoulapi.place_book(biblio, 2);
                    N++;
                    break;
        default  : cout << "Please give 1,2,3,4 or 5!" << endl;
    }
}

void Bookcase::take_book(int number) {
    switch(number) {
        case 1 :    cout << "Taking book from 1st OUTER self" << endl;
                    if (rafi1.take_book() == false){
                        cout << "Couldn't take! 1st OUTER self is empty" << endl;
                    }
                    N--;
                    break;
        case 2 :    cout << "Taking book from 2nd OUTER self" << endl;
                    if (rafi2.take_book() == false){
                        cout << "Couldn't take! 2nd OUTER self is empty" << endl;
                    }
                    N--;
                    break;
        case 3 :    cout << "Taking book from 3rd OUTER self" << endl;
                    if (rafi3.take_book() == false){
                        cout << "Couldn't take! 3rd OUTER self is empty" << endl;
                    }
                    N--;
                    break;
        case 4 :    cout << "Taking book from 1st INNER self" << endl;
                    ntoulapi.take_book(1);
                    N--;
                    break;
        case 5 :    cout << "Taking book from 2nd INNER self" << endl;
                    ntoulapi.take_book(2);
                    N--;
                    break;
        default  : cout << "Please give 1,2,3,4 or 5!" << endl;
    }
}

void Bookcase::print() const{
    cout << "Printing the bookcase:" << endl;
    ntoulapi.print();
    cout << "Printing the books from 1st OUTER shelf:" << endl;
    rafi1.print();
    cout << "Printing the books from 2nd OUTER shelf:" << endl;
    rafi2.print();
    cout << "Printing the books from 3rd OUTER shelf:" << endl;
    rafi3.print();
}