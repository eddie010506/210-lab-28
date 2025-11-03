#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>       
#include <algorithm>    
#include <vector>       
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;
void sort_by_name(list<Goat> &trip);
void sort_by_age(list<Goat> &trip);
void reverse_list(list<Goat> &trip);
void find_goat(const list<Goat> &trip);
void count_goats(const list<Goat> &trip);




int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                sort_by_name(trip);
                break;
            case 5:
                sort_by_age(trip);
                break;
            case 6:
                reverse_list(trip);
                break;
            case 7:
                find_goat(trip);
                break;
            case 8:
                count_goats(trip);
                break;
            case 9:
            case 10:
            case 11:
    
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort by Name (list::sort)\n";
    cout << "[5] Sort by Age (list::sort)\n";
    cout << "[6] Reverse list (list::reverse)\n";
    cout << "[7] Find Goat by Name (std::find)\n";
    cout << "[8] Count Goats Over Age (std::count)\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}


void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
void sort_by_name(list<Goat> &trip) {// milestone 1
    cout << "Sorting goats by name\n";
    trip.sort(); 
    display_trip(trip);
}
void sort_by_age(list<Goat> &trip) {// milestone 2
    cout << "Sorting goats by age\n";
    // using lambda
    trip.sort([](const Goat& a, const Goat& b) {
        return a.get_age() < b.get_age();
    });
    display_trip(trip);
}
void reverse_list(list<Goat> &trip) {
    cout << "Reversing the list\n";
    trip.reverse();
    display_trip(trip);
}
void find_goat(const list<Goat> &trip) {
    string name;
    cout << "Enter name to find: ";
    cin >> name;

    // using std::find_if with a lambda
    auto it = find_if(trip.begin(), trip.end(), [name](const Goat& g) {
        return g.get_name() == name;
    });

    if (it != trip.end()) {
        cout << "Found! " << it->get_name() << " (" << it->get_age() 
             << ", " << it->get_color() << ")\n";
    } 
    else {
        cout << "Could not find a goat named " << name << ".\n";
    }
}
void count_goats(const list<Goat> &trip) {
    int age;
    cout << "Count goats older than: ";
    cin >> age;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "No Goat older than that, Try Again: ";
        cin >> age;
    }

    // using std::count_if with a lambda
    int count = count_if(trip.begin(), trip.end(), [age](const Goat& g) {
        return g.get_age() > age;
    });

    cout << "Found " << count << " goats older than " << age << ".\n";
}