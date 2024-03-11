#include <iostream>
#include <algorithm>
#include "highway.h"

using namespace std;

/* function for creating random vehicle license plates(extra Vehicle data) */
string gen_random_plate() {
    string tmp_s = "";
    static const char caps[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char nums[] =
        "0123456789";
    for (int i=0; i<3; ++i) {
	   tmp_s += caps[rand() % (sizeof(caps) - 1)];
    }
    tmp_s += " ";
    for (int i=0; i<4; ++i) {
	   tmp_s += nums[rand() % (sizeof(nums) - 1)];
    }
	return tmp_s;    
}


//////////////////////////////////////////////////////////
/* Class Vehicle functions*/

	Vehicle::Vehicle(string name, int exit, int seg_no) {
		if (seg_no == -1) {
			//cout << "    Creating a new Vehicle waiting in a Toll." << endl;
		} else {
			//cout << "  Creating a new Vehicle inside Segment no" << seg_no+1 << "." << endl;
		}
		lp = name;
		exit_node = exit;
		inside_seg = seg_no;
		ready = false;
	}

	Vehicle::Vehicle(const Vehicle& v) {
		this->exit_node = v.exit_node;
		this->inside_seg = v.inside_seg;
		this->ready = v.ready;
		this->lp = v.lp;
		//cout << "  I just created a Vehicle by copying... " << endl;
	}
	
	string Vehicle::get_lp() const {
		return lp;
	}
	
	int Vehicle::get_exit() const {
		return exit_node;
	}

	int Vehicle::get_seg() const {
		return inside_seg;
	}
	
	void Vehicle::set_ready() {
		ready = true;
	}

	bool Vehicle::is_ready() const {
		return ready;
	}

	void Vehicle::just_passed(){
		ready = false;
	}

	Vehicle::~Vehicle() {
		if (inside_seg == -1) {
			//cout << "    Destroying a Vehicle from Toll" << endl;
		} else {
			//cout << "  Destroying a Vehicle from Segment no" << inside_seg+1 << "." << endl;
		}
	}	


//////////////////////////////////////////////////////////
/* Class Toll functions*/

	Toll::Toll(int toll_no, int k, int seg_no, int NSegs) {
		// cout << "   Creating a new Toll!" << endl;
		toll_id = toll_no;
		K = k;
		vehicles_toll_sum = rand() % K/2; 										//randmoly generated amount of waiting cars, based on k
		create_vehicles(NSegs, seg_no);
	}

	void Toll::add_vehicles(int NSegs, int seg_no, int tollnum, int etollnum) {
		Vehicle *v;
		vector <Vehicle*> vtemp;
		int vnum;
		
		if (is_physical()) {
			vnum = rand() % K/4 + ((K/tollnum)/2);
		} else {
			vnum = rand() % K/4 + (2*K/etollnum);
		}
		
		for (int i = 0 ; i < vnum ; i++) {
			v = new Vehicle(gen_random_plate(), get_exit(NSegs, seg_no), -1);
			vtemp.push_back(v);
		}
		
		this->sort_vehicles(vtemp);
		vtemp.clear();
	}

	bool Toll::remove_vehicle() { 										    	//remove one vehicle
		if (!vehicles.empty()) {                                            	//if vector is not empty
			//cout << " Vehicle " << vehicles[vehicles_toll_sum-1]->get_lp() << " entering from toll no" << toll_id+1 << " to segment." << endl;
			veh_to_transfer = new Vehicle(*vehicles.back());                	//copy vehicle in order to be entered
			delete vehicles.back();                                         	//delete vehicle
			vehicles.pop_back();                                            	//and remove it
			vehicles_toll_sum--;
			return true;
		} else {
			//cout << " Toll no" << toll_id+1 << " has no other vehicles waiting." << endl;
			return false;
		}
	}

	void Toll::create_vehicles(int NSegs, int seg_no){
		Vehicle *v;
		for(int i = 0 ; i < vehicles_toll_sum ; i++){
			v=new Vehicle(gen_random_plate(), get_exit(NSegs, seg_no), -1);
			vehicles.push_back(v);
		}
		reverse(vehicles.begin(), vehicles.end());
	}

	int Toll::get_exit(int NSegs, int seg_no) const {
		int r = rand() % NSegs;
		while (r < seg_no) {
			r = rand() % NSegs;
		}
		return r;
	}

	bool Toll::is_physical() {

	}

	Vehicle* Toll::get_veh_to_transfer() const {
		return veh_to_transfer;
	}

	void Toll::sort_vehicles(vector <Vehicle*> vtemp) {
		Vehicle *v;
		
		reverse(vehicles.begin(), vehicles.end());
		vehicles.insert(vehicles.end(), vtemp.begin(), vtemp.end());
		/* manual way of the .insert */
		// for (int i = 0 ; i < vtemp.size() ; i++) {
		// 	Vehicle* v = new Vehicle(*vtemp[i]);
		// 	delete vtemp[i];
		// 	vehicles.push_back(v);
		// }
		reverse(vehicles.begin(), vehicles.end());
		vehicles_toll_sum=vehicles.size();
	}
	

	
	int Toll::get_no_of_vehicles() const {
		return vehicles_toll_sum;
	}

	Toll::~Toll() {
		// cout << "   Destroying a Toll!" << endl;
		for (int i = 0 ; i < get_no_of_vehicles() ; i++){
			delete vehicles.back();
			vehicles.pop_back();
		}
		vehicles.clear();
	}


//////////////////////////////////////////////////////////
/* Class Physical_Toll functions*/

	Physical_Toll::Physical_Toll(int toll_no, int k, int seg_no, int NSegs) : Toll(toll_no,k,seg_no,NSegs) {
		//cout << "   Creating a Physical Toll!" << endl;
	}

	bool Physical_Toll::is_physical() {
		return true;
	}

	Physical_Toll::~Physical_Toll() {
		// cout << "   Destroying a Physical Toll!" << endl;
	}


//////////////////////////////////////////////////////////
/* Class Electronic_Toll functions*/

	Electronic_Toll::Electronic_Toll(int toll_no, int k, int seg_no, int NSegs) : Toll(toll_no,k,seg_no,NSegs) {
		//cout << "   Creating an Electronic Toll!" << endl;
	}

	bool Electronic_Toll::is_physical() {
		return false;
	}
	
	Electronic_Toll::~Electronic_Toll() {
		// cout << "   Destroying an Electronic Toll!" << endl;
	}


//////////////////////////////////////////////////////////
/* Class Entrance functions*/

	Entrance::Entrance(int seg_no, int capacity, int k, int NSegs) {
		// cout << "  Creating a new Entrance";
		
		name = "Entrance no" + to_string(seg_no);
		// cout << " with name: " << name << endl;
		K = k;
		Kconst = k;
		ptoll_num = 0;
		etoll_num = 0;
		create_tolls(capacity, seg_no, NSegs);
		toll_num = ptoll_num + etoll_num;
		delays=false;
	}

    void Entrance::operate(int empty_seats, Segment* current_seg) {
		int i = 0; 
		int count = 0; 															//counter containing the amount of vehicles that enter the segment
		bool flag1 = true; 														//condition on wether the physical tolls have allowed K vehicles to enter, or there are no more vehicles waiting
		bool flag2 = true; 														//condition on wether the electronic tolls have allowed 2K vehicles to enter, or there are no more vehicles waiting
		bool flag = true; 														//condition on wether the tolls have allowed 3K vehicles to enter, or there are no more vehicles waiting
		int kappa = 0; 															//counter containing the amount of vehicles that enter the segment from physical tolls 
		int twokappa = 0; 														//counter containing the amount of vehicles that enter the segment from electronic tolls
		while (count < empty_seats && flag == true) {
			if (tolls[i]->is_physical() == true) {
				if (kappa < K) {
					if (tolls[i]->remove_vehicle() == true) {
						kappa++;
						count++;
						Vehicle* v = new Vehicle(*tolls[i]->get_veh_to_transfer());
						delete tolls[i]->get_veh_to_transfer();
						current_seg->transfer_vehicle(v);
					} else {
						int s1 = 0;
						for (int j = 0 ; j < ptoll_num ; j++) {
							s1 += tolls[j]->get_no_of_vehicles();
						}
						if (s1 == 0) {
							flag1 = false;
						}
					}
				} else {
					flag1 = false;
				}
				if (ptoll_num == toll_num && flag1 == false) {
					flag = false;
				}
			} else {
				if (twokappa < 2*K) {
					if (tolls[i]->remove_vehicle() == true) {
						twokappa++;
						count++;
						Vehicle* v = new Vehicle(*tolls[i]->get_veh_to_transfer());
						delete tolls[i]->get_veh_to_transfer();
						current_seg->transfer_vehicle(v);
					} else {
						int s2 = 0;
						for (int j = ptoll_num ; j < etoll_num ; j++) {
							s2 += tolls[j]->get_no_of_vehicles();
						}
						if (s2 == 0) {
							flag2 = false;
						}
					}
				} else {
					flag2 = false;
				}
				if (etoll_num == toll_num && flag2 == false) {
					flag = false;
				}
			}
			if ((flag1 == false) && (flag2 == false)) {
				flag = false;
			}
			if (i < toll_num-1) {												//vehicles enter from tolls in a circular way
				i++;
			} else {
				i = 0;
			}
		}
		if (count < empty_seats) {
			K--;
			if (K < 1) {                                                 		//extreme case if K is decreased a lot
				K = 1;                                                   		//we dont want it to become negative, so we set it as the (minimum) 1
			}
		} else {    															//if count == empty_seats
			K++;
		}
		check_delays(count);
    }

	void Entrance::add_vehicles(int NSegs, int seg_no) {
		for (int i = 0 ; i < toll_num ; i++) {
			tolls[i]->add_vehicles(NSegs, seg_no, toll_num, etoll_num);
		}
	}

	void Entrance::create_tolls(int capacity, int seg_no, int NSegs) {
		int tollstocreate, l;
		if (Kconst == 1) {
			l = 1;																//to avoid division with 0
		} else {
			l = Kconst/2; 															//half of K
		}
		tollstocreate = capacity/l; 											//amount of tolls we will create(something that depends on capacity and K)
		
		if(tollstocreate<2){
			tollstocreate=2;
		}
		
		tolls = new Toll*[tollstocreate];
		if (tollstocreate%2 == 0) {
			int count = 0;
			for (int i = 0 ; i <= (tollstocreate*8)/10 ; i++) {
				tolls[i] = new Physical_Toll(i, Kconst, seg_no, NSegs);
				this->ptoll_num++;
				count++;
			}
			for (int i = count ; i < tollstocreate ; i++) {
				tolls[i] = new Electronic_Toll(i, Kconst, seg_no, NSegs);
				this->etoll_num++;
			}
		} else {
			int count = 0;
			for (int i = 0 ; i <= (tollstocreate*6)/10 ; i++) {
				tolls[i] = new Physical_Toll(i, Kconst, seg_no, NSegs);
				this->ptoll_num++;
				count++;
			}
			for (int i = count ; i < tollstocreate ; i++) {
				tolls[i] = new Electronic_Toll(i, Kconst, seg_no, NSegs);
				this->etoll_num++;
			}
		}
	}
	
	int Entrance::get_no_of_vehicles() const {
		int sum = 0;
		for(int i = 0 ; i < toll_num ; i++) {
			sum += tolls[i]->get_no_of_vehicles();
		}
		return sum;
	}
	
	void Entrance::check_delays(int c) {
		if (c < get_no_of_vehicles()) {
			delays = true;
		} else {
			delays = false;
		}
	}
	
	bool Entrance::get_delays() const {
		return delays;
	}		

	Entrance::~Entrance() {
		// cout << "  Destroying an Entrance with name: " << name << endl;
		for (int i = 0 ; i < toll_num ; i++) {
			delete tolls[i];
		}
		delete[] tolls;
	}


//////////////////////////////////////////////////////////
/* Class Segment functions*/

	Segment::Segment(int seg_no, int cap, Segment *prev, Segment *next, int K, int percent, int nsegs) {
		// cout << " Creating a new Segment(no" << seg_no+1 << ")" << endl;
		seg_id = seg_no;
		capacity = cap;
		prev_seg = prev;
		next_seg = next;
		NSegs = nsegs;
		Percent = percent;

		entrance = new Entrance(seg_id, capacity, K, NSegs);
		
		vehicles=new Vehicle*[capacity];
		create_vehicles();
	}

    void Segment::enter(int empty_seats) {							    		//vehicles are entering from tolls as long as the capacity isn't being compromised
	    entrance->operate(empty_seats,this);
    }

    void Segment::exit(int i) {
	    //cout << " Vehicle " << vehicles[i]->get_lp() << " exiting highway!" << endl;
		delete vehicles[i];
		vehicles[i] = NULL; 													//in order to not have a random value
		vehicles_seg_sum--;
    }

    void Segment::pass(int i) {  												//vehicle leaves this segment and goes on to the next, so it is removed from this segment's vehicle array and this segment's sum is reduced by 1
	    if (this->next_seg != NULL) {
			int p = next_seg->get_no_of_vehicles();
			//cout << " Vehicle " << vehicles[i]->get_lp() << " attempts to pass to segment no" << next_seg->seg_id+1 << "." << endl;
			if (p < next_seg->get_capacity()) {
				next_seg->vehicles[p] = new Vehicle(*vehicles[i]);
				next_seg->vehicles_seg_sum++;
				delete vehicles[i];
				vehicles[i] = NULL;
				vehicles_seg_sum--;
				//cout << " Vehicle " << next_seg->vehicles[p]->get_lp() << " passed successfuly!" << endl;
				next_seg->vehicles[p]->just_passed(); 							//as a result, in the next segment it is not ready
			} else {
				//cout << " Vehicle " << vehicles[i]->get_lp() << " cannot proceed!" << endl;
			}
		} else {
			//cout << "Segment doesnt exist!" << endl;
		}
    }

    int Segment::get_no_of_vehicles() const {
        return vehicles_seg_sum;
    }

    void Segment::operate() {
		cout << endl << "Segment no" << seg_id+1 << " has: " << this->get_no_of_vehicles() << " vehicles." << endl << endl;
		int j = get_no_of_vehicles();
		bool flag = false;
		for (int i = 0 ; i < j ; i++) {
			if (vehicles[i]->is_ready()) {										//(==true)
				if (vehicles[i]->get_exit() == seg_id) {
					exit(i);
					flag = true;
				}
			}
		}
		
		if (flag) { 															//if we had at least one vehicle exit the highway, sort the vehicle array
			cout << "Sorting vehicles after exits..." << endl;
			sort_vehicles();
			cout << "Segment no" << seg_id+1 << " now has: " << this->get_no_of_vehicles() << " vehicles." << endl << endl;
		}

		if (seg_id != 0) {                                                   	//if we are at first segment we cannot pass from the previous one(it doesnt exist)
			int l = prev_seg->get_no_of_vehicles();
			bool flag2 = false;
			for (int i = 0 ; i < l ; i++) {
				if (prev_seg->vehicles[i]->is_ready() && prev_seg->vehicles[i]->get_exit() != seg_id-1) {
					prev_seg->pass(i);
					flag2=true;
				}
			}
			if (flag2) {
				cout << "Sorting vehicles after passes..." << endl;
				prev_seg->sort_vehicles();
				cout << "Segment no" << seg_id+1 << " now has: " << this->get_no_of_vehicles() << " vehicles." << endl << endl;
			} else {
				cout << "No vehicle was ready to pass to segment no" << seg_id+1 << "." << endl;
				cout << "Segment no" << seg_id+1 << " now has: " << this->get_no_of_vehicles() << " vehicles." << endl << endl;
			}
		}

		/*trying to enter vehicles from tolls*/
		cout << "Trying to enter vehicles from tolls to segment no" << seg_id+1 << endl;
		int empty_seats = get_capacity() - get_no_of_vehicles();
		if (empty_seats > 0) {
			enter(empty_seats);
		} else {
			cout << "No space inside segment. Vehicles cannot enter from tolls." << endl;
			entrance->check_delays(0);
		}
		check_delays();
		cout << "Segment no" << seg_id+1 << " now has: " << this->get_no_of_vehicles() << " vehicles." << endl << endl;
    }


	void Segment::set_previous(Segment* prev) {
		prev_seg = prev;
	}

	void Segment::set_next(Segment* next) {
		next_seg = next;
	}
	
	void Segment::create_vehicles() {
		vehicles_seg_sum = rand() % capacity/2;
		for (int i = 0 ; i < vehicles_seg_sum ; i++) {
			vehicles[i] = new Vehicle(gen_random_plate(), get_exit(), this->seg_id);
		}
	}

	void Segment::ready_vehicles() {
		int ready = get_no_of_vehicles() * ((float)Percent/100);
		for (int i = 0 ; i < ready ; i++) { 									//vehicles that are ready are at the front of the array
			vehicles[i]->set_ready();
		}
	}
	
	int Segment::get_exit() const {
		int r = rand() % NSegs;
		while (r < this->seg_id) {
			r = rand() % NSegs;
		}
		return r;
	}

	void Segment::transfer_vehicle(Vehicle* v) {
		vehicles[get_no_of_vehicles()] = new Vehicle(*v);
		delete v;
		vehicles_seg_sum++;
	}

	int Segment::get_capacity() const {
		return capacity;
	}

	void Segment::sort_vehicles() {
		int count = 0;
		int i = 0;
		if (vehicles_seg_sum != 0) {
			while ((i < this->capacity) && (count < vehicles_seg_sum)) {
				if (vehicles[i] == NULL) {
					int j = i+1;
					while (j < this->capacity) {
						if (vehicles[j] != NULL) {
							vehicles[i] = new Vehicle(*vehicles[j]);
							delete vehicles[j];
							vehicles[j] = NULL;
							j = this->capacity;
						}
						j++;
					}
					count++;
				} else {
					count++;
				}
				i++;
			}
		}
	}

	void Segment::add_vehicles(int nsegs, int pos) {
		entrance->add_vehicles(nsegs, pos);
	}
	
	void Segment::check_delays() {
		cout << endl;
		bool flag1 = false;
		if (entrance->get_delays()) {
			cout << " Delays at the entrance of node '" << this->seg_id << "'." << endl;
			flag1 = true;
		}
		if (seg_id != 0) {
			int i = 0;
			int l = prev_seg->get_no_of_vehicles();
			bool flag2 = false;
			while (i < l && !flag2) {
				if (prev_seg->vehicles[i]->is_ready() && (prev_seg->vehicles[i]->get_exit() != seg_id-1)){
					cout << " Delays after node '" << this->seg_id << "'." << endl;
					flag1 = true;
					flag2 = true;
				}
				i++;
			}
		}

		if (!flag1) {
			cout << " Maintain safety distances at segment after node '" << this->seg_id << "'." << endl;
		}
	}		
	
	Segment::~Segment() {
		// cout << " Destroying a Segment(no" << seg_id+1 << ")" << endl;
		delete entrance;

		for (int i = 0 ; i < get_no_of_vehicles() ; i++) {
			delete vehicles[i];
		}
		delete[] vehicles;
	}


//////////////////////////////////////////////////////////
/* Class Attiki_Odos functions*/

	Attiki_Odos::Attiki_Odos(int nsegs, int K, int Percent, int capacity[]) {
		cout << endl;
		cout << "Creating a new Highway!" << endl;
		cout << "Highway has " << nsegs << " segments." << endl;
		NSegs = nsegs;
		segments = new Segment*[NSegs];
		for (int i = 0 ; i < NSegs ; i++) {
			segments[i]=new Segment(i, capacity[i], NULL, NULL, K, Percent, NSegs);
		}
		for (int i = 0 ; i < NSegs ; i++) {
			if (i == 0 && NSegs == 1) {											//case NSegs==1
				segments[i]->set_previous(NULL);
				segments[i]->set_next(NULL);
			} else if (i == 0) {
				segments[i]->set_previous(NULL);
				segments[i]->set_next(segments[i+1]);
			} else if (i == NSegs-1) {
				segments[i]->set_previous(segments[i-1]);
				segments[i]->set_next(NULL);
			} else {
				segments[i]->set_previous(segments[i-1]);
				segments[i]->set_next(segments[i+1]);
			}
		}
		total_vehicles = get_total_vehicles();
		
		cout << endl;
		cout << "Highway is operational!!" << endl;
		cout << endl;
	}

    void Attiki_Odos::operate() {
		for (int i = NSegs-1 ; i >= 0 ; i--) {
	        segments[i]->ready_vehicles();
	    }
		for (int i = NSegs-1 ; i >= 0 ; i--) {
	        segments[i]->operate();
	    }
	    cout << "Vehicles inside the highway: " << get_total_vehicles() << endl;
    }

	void Attiki_Odos::add_vehicles() {
		cout <<  "Adding random vehicles waiting at the segments' entrances..." << endl;
		for (int i = NSegs-1 ; i >= 0 ; i--) {
	        segments[i]->add_vehicles(NSegs,i);
	    }
	}

	int Attiki_Odos::get_total_vehicles() {
		total_vehicles = 0;
		for (int i = NSegs-1 ; i >= 0 ; i--) {
            total_vehicles += segments[i]->get_no_of_vehicles();
        }
		return total_vehicles;
	}
	
	Attiki_Odos::~Attiki_Odos() {
		cout << endl;
		cout << "Destroying a Highway!" << endl;
	
		for(int i = 0 ; i < NSegs ; i++) {
			delete segments[i];
		}
		delete[] segments;

		cout << endl;
		cout << "Highway has closed!!" << endl;
		cout << endl;
	}

//////////////////////////////////////////////////////////
