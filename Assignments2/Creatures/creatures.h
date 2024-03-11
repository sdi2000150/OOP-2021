#include <cstring>

using namespace std;

class creature_society;

class creature {
        string name;
        int life; //L

/* extra private data */
        int index; //thesi stin akolouthia tis koinothtas
        creature_society* pointer; //deikths stin koinothta pou anoikei
    public:
        creature(creature_society*, int, string, int);
        virtual ~creature(); //einai virtual wste otan diagrafei ena kalo/kako plasma na kalestei prwta o destructor tis antistoixhs paragwghs klashs
        creature(creature&, int);

        bool is_a_zobie() const;
        virtual bool is_a_good() const = 0; //einai virtual efoson metathetei ton elegxo stis paragwges klaseis(pure virtual wste na ginei h klash abstract)
        virtual creature* clone(creature*); //einai virtual wste otan ginei clone kapoio kalo/kako plasma na kalestei h antistoixh clone
        void beat();
        virtual void bless(); //einai virtual wste otan ginei bless kapoio kalo/kako plasma na kalestei h antistoixh bless

/* extra public functions */
        int get_life() const;
        int get_index() const;
        creature_society* get_pointer() const;

        void print() const; //print the creature's name and life(for testing)
};

class good_creature : public creature {
        int good_thrsh;
    public:
        good_creature(creature_society*, int, string, int, int);
        ~good_creature();
        good_creature(good_creature&, int);

        void bless();
        bool is_a_good() const ;
        creature* clone(creature*); //pairnei san orisma to creature pou tha antikatastathei apo to trexon kai epistrefei to neo auto creature(klono tou trexontos)
};

class bad_creature : public creature {
        int bad_thrsh;
    public:
        bad_creature(creature_society*, int, string, int, int);
        ~bad_creature();
        bad_creature(bad_creature&,int);

        void bless();
        bool is_a_good() const;
        creature* clone(creature*); //pairnei san orisma to creature pou tha antikatastathei apo to trexon kai epistrefei to neo auto creature(klono tou trexontos)
};

class creature_society {
        int ni; //N
        creature** pinakas; //akolouthia deiktwn se plasmata
    public:
        creature_society(int, int, int, int);
        ~creature_society();
        
        void beat(int); //pairnei san orisma tin thesi tou plasmatos pou tha ginei beat
        void bless(int);        //pairnei san orisma tin thesi tou plasmatos pou tha ginei bless
        void clone_next(int);   //pairnei san orisma tin thesi tou plasmatos pou tha klonopoihthei
        void clone_zobies(int); //pairnei san orisma tin thesi tou plasmatos pou tha klonopoihthei
        int no_of_good() const; //epistrefei ton plithos twn kalwn plasmatwn(pou den einai zombie)
        int no_of_zobies() const; //epistrefei to plithos twn zombie

        void print() const; //print the society(for testing)
};