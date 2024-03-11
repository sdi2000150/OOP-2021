#include <iostream>
#include <cstring>
#include "creatures.h"

using namespace std;

//////////////////////////////////////////////////////////
/* Class creature functions*/

    creature::creature(creature_society* deikths, int thesi, string onoma, int L) : pointer(deikths), index(thesi), name(onoma), life(L) {
        cout << "Creating a creature" << endl;
    }
    creature::~creature() {
        cout << "Destroying a creature" << endl;
    }
    creature::creature(creature& c, int thesi) : name(c.name), life(c.life), pointer(c.pointer), index(thesi) {
        cout << "Creating a creature by copying" << endl;
    }

    bool creature::is_a_zobie() const {
        if (life == 0) {
            return true;
        } else {
            return false;
        }
    }
    creature* creature::clone(creature* tobereplaced) {
        cout << "Inside creature::clone" << endl;
        return tobereplaced;
    }
    void creature::beat() {
        cout << "Inside creature::beat" << endl;
        if (is_a_zobie() == false) {
            cout << "   Beating the creature from position " << index << endl;
            life--;
        } else {
            cout << "   Creature in position " << index << " is a zombie. Cannot be beaten" << endl;
        }
    }
    void creature::bless() {
        cout << "Inside creature::bless" << endl;
        if (is_a_zobie() == false) {
            cout << "   Blessing the creature from position " << index << endl;
            life++;
        } else {
            cout << "   Creature in position " << index << " is a zombie. Cannot be blessed" << endl;
        }
    }

    int creature::get_life() const {
        return life;
    }
    int creature::get_index() const {
        return index;
    }
    creature_society* creature::get_pointer() const {
        return pointer;
    }
    
    void creature::print() const {
        cout << "name: " << name << " life: " << life  << endl;
    }

//////////////////////////////////////////////////////////
/* Class good_creature functions*/

    good_creature::good_creature(creature_society* deikths, int thesi, string onoma, int L, int threshold) : creature(deikths,thesi,onoma,L), good_thrsh(threshold){
        cout << "Creating a good_creature" << endl;
    }
    good_creature::~good_creature() {
        cout << "Destroying a good_creature" << endl;
    }
    good_creature::good_creature(good_creature& gd,int thesi) : creature(gd,thesi), good_thrsh(gd.good_thrsh) {
        cout << "Creating a good_creature by copying" << endl;
    }

    void good_creature::bless() {
        cout << "Inside good_creature::bless" << endl;
        creature::bless();
        if (get_life() > good_thrsh) {
            cout << "   Good creature is 'eurwsto', it can be cloned in the next position" << endl;
            get_pointer()->clone_next(get_index());
        }
    }
    bool good_creature::is_a_good() const {
        return true;
    }
    creature* good_creature::clone(creature* tobereplaced) {
        cout << "Inside good_creature::clone" << endl;
        creature::clone(tobereplaced);
        if (is_a_zobie() == false) {
            int thesi = tobereplaced->get_index();
            delete tobereplaced;
            tobereplaced = new good_creature(*this,thesi);
        }
        return tobereplaced;
    }


//////////////////////////////////////////////////////////
/* Class bad_creature functions*/

    bad_creature::bad_creature(creature_society* deikths, int thesi, string onoma, int L, int threshold) : creature(deikths,thesi,onoma,L), bad_thrsh(threshold) {
        cout << "Creating a bad_creature" << endl;
    }
    bad_creature::~bad_creature() {
        cout << "Destroying a bad_creature" << endl;
    }
    bad_creature::bad_creature(bad_creature& gd,int thesi) : creature(gd,thesi), bad_thrsh(gd.bad_thrsh) {
        cout << "Creating a bad_creature by copying" << endl;
    }

    void bad_creature::bless() {
        cout << "Inside bad_creature::bless" << endl;
        creature::bless();
        if (get_life() > bad_thrsh) {
            cout << "   Bad creature is 'eurwsto', it can be cloned in the next continuous positions that contain zombies" << endl;
            get_pointer()->clone_zobies(get_index());
        }
    }
    bool bad_creature::is_a_good() const {
        return false;
    }
    creature* bad_creature::clone(creature* tobereplaced) {
        cout << "Inside bad_creature::clone" << endl;
        creature::clone(tobereplaced);
        if (is_a_zobie() == false) {
            int thesi = tobereplaced->get_index();
            delete tobereplaced;
            tobereplaced = new bad_creature(*this,thesi);
        }
        return tobereplaced;
    }

//////////////////////////////////////////////////////////
/* Class creature_society functions*/

    creature_society::creature_society(int N, int L, int good_thrsh, int bad_thrsh) : ni(N) {
        cout << "Creating a creature_society" << endl;
        string kala_plasmata[30] = {"good_Steve","good_Alex","good_Villager","good_Sheep","good_Cow","good_Fox","good_Bat","good_Chicken","good_Cod","good_Ocelot",
                            "good_Pig","good_Rabbit","good_Salmon","good_Mooshroom","good_Squid","good_Strider","good_Turtle","good_Pufferfish","good_Axolotl",
                            "good_Donkey","good_Horse","good_Cat","good_Parrot","good_Mule","good_Dolphin","good_Wolf","good_Goat","good_Trader","good_Panda",
                            "good_Giant"};

        string kaka_plasmata[30] = {"bad_Herobrine","bad_Dragon","bad_Notch","bad_Wither","bad_Pillager","bad_Spider","bad_Enderman","bad_Piglin","bad_Pigman",
                            "bad_Evoker","bad_Vindicator","bad_Ravager","bad_Vex","bad_Endermite","bad_Guardian","bad_Shulker","bad_Husk","bad_Stray",
                            "bad_Phantom","bad_Blaze","bad_Creeper","bad_Ghast","bad_Silverfish","bad_Skeleton","bad_Slime","bad_Drowned","bad_Witch",
                            "bad_Hoglin","bad_Zoglin","bad_Warden"};
        string onoma;
        int eidos;
        pinakas = new creature*[ni];
        for (int i = 0 ; i < ni ; i++) {
            eidos = rand() % 2 + 1;
            if (eidos == 1) {
                onoma = kala_plasmata[rand() % 30] + to_string(i);
                pinakas[i] = new good_creature(this,i,onoma,L,good_thrsh);
            } else {
                onoma = kaka_plasmata[rand() % 30] + to_string(i);
                pinakas[i] = new bad_creature(this,i,onoma,L,bad_thrsh);
            }
        }
    }  
    creature_society::~creature_society() {
        cout << "Destroying a creature_society" << endl;
        for (int i = 0 ; i < ni ; i++) {
            delete pinakas[i];
        }
        delete[] pinakas;
    }

    void creature_society::beat(int i) {
        cout << "Inside creature_society::beat" << endl;
        pinakas[i]->beat();
    }
    void creature_society::bless(int i) {
        cout << "Inside creature_society::bless" << endl;
        pinakas[i]->bless();
    }
    void creature_society::clone_next(int i) {
        cout << "Inside creature_society::clone_next" << endl;
        if (i < ni-1) {  //e.g.: if N==20(ni==20) => society positions are 0,1,2,...,18,19 => i needs to be <19(ni-1) in order to clone at i+1 position
            cout << "   Cloning creature from position " << i << " in position " << i+1 << endl;
            pinakas[i+1] = pinakas[i]->clone(pinakas[i+1]);
        } else {        //else clone at position 0
            cout << "   Cloning creature from position " << i << " in position " << 0 << endl;
            pinakas[0] = pinakas[i]->clone(pinakas[0]);
        }
    }
    void creature_society::clone_zobies(int i) {
        cout << "Inside creature_society::clone_zobies" << endl;
        if (i < ni-1) { //e.g.: if N==20(ni==20) => society positions are 0,1,2,...,18,19 => i needs to be <19(ni-1) in order to clone at i+1,... positions
            int j = i+1;
            bool flag = true;
            while((j <= ni-1) && (flag == true)) { //cont e.g.: if i==17 => clone is done at positions 18,19(i+1,...,ni-1) positions(while there are zombies)
                if (pinakas[j]->is_a_zobie() == true) {
                    cout << "   Cloning creature from position " << i << " in position " << j << endl;
                    pinakas[j] = pinakas[i]->clone(pinakas[j]);
                } else {
                    cout << "   No other next continious position has a zombie" << endl;
                    flag = false; //end loop
                }
                j++;
            }
        } else {    //else i==ni(i is the last position) so it cannot clone
            cout << "   Cannot clone. Creature to be cloned is at last position" << endl;
        }
    }
    int creature_society::no_of_good() const {
        int goods = 0;
        for (int i = 0 ; i < ni ; i++) {
            if (pinakas[i]->is_a_good() == true && pinakas[i]->is_a_zobie() == false) { //we assume a good creature as a non-zombie one
                goods++;
            }
        }
        return goods;
    }
    int creature_society::no_of_zobies() const {
        int zobies = 0;
        for (int i = 0 ; i < ni ; i++) {
            if (pinakas[i]->is_a_zobie() == true) {
                zobies++;
            }
        }
        return zobies;
    }

    void creature_society::print() const {
        cout << "   Printing the creature_society" << endl;
        for (int i = 0 ; i < ni ; i++) {
            cout << "   Creature in position " << i << ": ";
            pinakas[i]->print();
        }
    }

//////////////////////////////////////////////////////////