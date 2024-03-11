#include <cstring>
#include <vector>

using namespace std;

class Vehicle {
		int exit_node;  									//exit node
		int inside_seg;        								//current segment where it moves in
		bool ready;     									//ready indicator

		/* extra data */
		string lp;      									//license plate
	public:
		Vehicle(string, int, int);

		Vehicle(const Vehicle&);
		
		/* extra functions */
		string get_lp() const;
		
		int get_exit() const;

		int get_seg() const;
		
		void set_ready();

		bool is_ready() const;

		void just_passed();

		~Vehicle();
};


class Toll {
		vector <Vehicle*> vehicles; 						//vector of vehicles waiting to enter

		/* extra data */
		int toll_id;										//toll id
		int vehicles_toll_sum; 								//vehicles currently waiting in tolls
		int K; 				    							//K
		Vehicle* veh_to_transfer;   						//vehicle to be transfered from toll to segment
	public:
		Toll(int, int, int, int);

		void add_vehicles(int, int, int, int);						//prostithentai oxhmata sto diodio

		bool remove_vehicle();								//afairountai oxhmata apo to diodio

		/* extra functions */
		void create_vehicles(int, int);

		int get_exit(int, int) const;

		virtual bool is_physical();

		Vehicle* get_veh_to_transfer() const;

		void sort_vehicles(vector <Vehicle*>);
		
		int get_no_of_vehicles() const;

		virtual ~Toll();
};


class Physical_Toll : public Toll {
	public:
		Physical_Toll(int, int, int, int);

		bool is_physical();									//returns true

		~Physical_Toll();
};


class Electronic_Toll : public Toll {
	public:
		Electronic_Toll(int, int, int, int);

		bool is_physical();									//returns false
		
		~Electronic_Toll();
};

class Segment; 												//class forwarding

class Entrance {
		string name; 
		Toll **tolls;       								//array containing tolls

		/* extra data */
		int ptoll_num;      								//number of tolls with employer
		int etoll_num; 	    								//number of electronic tolls
		int toll_num; 	    								//total amount of tolls
		int K; 		    									//K, but its value can be subject to changes
		int Kconst; 										//const K
		bool delays;
	public:		
		Entrance(int, int, int, int);

		void operate(int, Segment*);						//afairountai oxhmata apo tin eisodo

		void add_vehicles(int, int);						//prostithentai tyxaia oxhmata sta diodia ths

		/* extra functions */
		void create_tolls(int, int, int);
		
		int get_no_of_vehicles() const;
		
		void check_delays(int);
		
		bool get_delays() const;

		~Entrance();
};

class Segment {
		Entrance *entrance; 								//segment entrance
		Vehicle **vehicles; 								//vehicles currently inside the segment
		int capacity; 	    								//segment's capacity
		Segment *prev_seg;  								//previous segment
		Segment *next_seg;  								//next segment

		/* extra data */
		int seg_id;             							//current segment
		int vehicles_seg_sum;   							//number of vehicles currently inside the segment
		int NSegs;          								//amount of this highway's segments
		int Percent;
	public:
		Segment(int, int, Segment*, Segment*, int, int, int);

        void enter(int);

		void exit(int);

		void pass(int);

		int get_no_of_vehicles() const;

        void operate();

		/* extra functions */
		void set_previous(Segment*);

		void set_next(Segment*);
		
		void create_vehicles();

		void ready_vehicles();
		
		int get_exit() const;

		void transfer_vehicle(Vehicle*);

		int get_capacity() const;

		void sort_vehicles();

		void add_vehicles(int, int);
		
		void check_delays();
		
		~Segment();
};

class Attiki_Odos {
		Segment **segments;									//highway's (NSegs) segments
		int total_vehicles; 								//amount of vehicles currently using the highway

        /* extra data */
		int NSegs;          								//amount of highway's segments
	public:
		Attiki_Odos(int, int, int, int*);

		void operate();

		/* extra functions */
		void add_vehicles();

		int get_total_vehicles();
		
		~Attiki_Odos();
};
