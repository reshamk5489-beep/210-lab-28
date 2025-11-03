#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <random>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void sort_goats(list<Goat> &trip);
void reverse_goats(list<Goat> &trip);
void iterate_goats(list<Goat> &trip);
void find_goat(list<Goat> &trip);
void any_goat_of_color(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);

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
    while (sel != 10) {
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
                cout << "Sorting goats." << endl;
                sort_goats(trip);
                break;
            case 5:
                cout << "Reversing goats." << endl;
                reverse_goats(trip);
                break;
            case 6:
                cout << "Iterating goats and displaying their data." << endl;
                iterate_goats(trip);
                break;
            case 7:
                cout << "Finding goat and displaying its data." << endl;
                find_goat(trip);
                break;
            case 8:
                cout << "Find any goat with given color" << endl;
                any_goat_of_color(trip);
                break;
            case 9:
                cout << "Shuffling goats" << endl;
                shuffle_goats(trip);
                break;
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
    cout << "[4] Sort goats" << endl;
    cout << "[5] Reverse goats" << endl;
    cout << "[6] Iterate goats" << endl;
    cout << "[7] Find goat" << endl;
    cout << "[8] Any goat with given color" << endl;
    cout << "[9] Shuffle goats" << endl;
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 10) {
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
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_goats(list<Goat> &trip)
{
    trip.sort();
}

void reverse_goats(list<Goat> &trip)
{
    trip.reverse();
}

void iterate_goats(list<Goat> &trip)
{
    int i = 1;
    for_each(trip.begin(), trip.end(), [&i](Goat& gt)
    { 
        cout << "\t" 
        << "[" << i++ << "] "
        << gt.get_name() 
        << " (" << gt.get_age() 
        << ", " << gt.get_color() << ")\n"; 
    });
}

void find_goat(list<Goat> &trip)
{
    string goatName;

    cout << "Searching for goat..." << endl;
    cout << "Enter goat name: ";
    cin >> goatName;

    auto it = find_if(trip.begin(), trip.end(), [&goatName](const Goat& gt)
    { 
        return gt.get_name() == goatName;
    });

    if (it != trip.end())
        cout << it->get_name() << " found with age: " << it->get_age() << " and color: " << it->get_color() << endl;
}

void any_goat_of_color(list<Goat> &trip)
{
    string color;

    cout << "Enter goat color: ";
    cin >> color;

    bool hasColor = any_of(trip.begin(), trip.end(), [&color](const Goat& gt)
    { 
        return gt.get_color() == color; 
    });

    cout << "Is there a goat with this color? " << (hasColor ? "Yes" : "No") << endl;
}

void shuffle_goats(list<Goat> &trip)
{
    shuffle(trip.begin(), trip.end(), default_random_engine());
}