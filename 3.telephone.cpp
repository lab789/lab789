#include <iostream>
#include <string>
using namespace std;


const int SIZE = 10;


struct Client {
    string name;
    long long phone;
    bool occupied;
    Client() {
        name = "";
        phone = 0;
        occupied = false;
    }
};


class HashTable {
    Client table[SIZE];


public:
    int hash1(long long key) { return key % SIZE; }
    int hash2(long long key) { return 7 - (key % 7); }


    void insertLinear(string name, long long phone) {
        int index = hash1(phone);
        int start = index;
        while (table[index].occupied) {
            index = (index + 1) % SIZE;
            if (index == start) return;
        }
        table[index].name = name;
        table[index].phone = phone;
        table[index].occupied = true;
        cout << "Inserted (Linear): " << name << " " << phone << endl;
    }


    void insertQuadratic(string name, long long phone) {
        int index = hash1(phone);
        int i = 0;
        while (table[(index + i * i) % SIZE].occupied && i < SIZE) i++;
        if (i == SIZE) return;
        index = (index + i * i) % SIZE;
        table[index].name = name;
        table[index].phone = phone;
        table[index].occupied = true;
        cout << "Inserted (Quadratic): " << name << " " << phone << endl;
    }


    void insertDoubleHash(string name, long long phone) {
        int index = hash1(phone);
        int step = hash2(phone);
        int i = 0;
        while (table[(index + i * step) % SIZE].occupied && i < SIZE) i++;
        if (i == SIZE) return;
        index = (index + i * step) % SIZE;
        table[index].name = name;
        table[index].phone = phone;
        table[index].occupied = true;
        cout << "Inserted (Double Hashing): " << name << " " << phone << endl;
    }


    void search(long long phone) {
        int index = hash1(phone);
        int start = index;
        int i = 0;
        while (table[index].occupied && i < SIZE) {
            if (table[index].phone == phone) {
                cout << "Found: " << table[index].name << " -> " << table[index].phone << endl;
                return;
            }
            index = (index + 1) % SIZE;
            i++;
        }
        cout << "Phone number not found!\n";
    }


    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " : ";
            if (table[i].occupied)
                cout << table[i].name << " (" << table[i].phone << ")";
            else
                cout << "----";
            cout << endl;
        }
    }
};


int main() {
    HashTable ht;
    int choice;
    string name;
    long long phone;


    do {
        cout << "\n1. Insert (Linear Probing)\n2. Insert (Quadratic Probing)\n3. Insert (Double Hashing)";
        cout << "\n4. Search\n5. Display\n0. Exit\nEnter choice: ";
        cin >> choice;


        switch(choice) {
            case 1:
                cout << "Enter name: "; cin >> name;
                cout << "Enter phone: "; cin >> phone;
                ht.insertLinear(name, phone);
                break;
            case 2:
                cout << "Enter name: "; cin >> name;
                cout << "Enter phone: "; cin >> phone;
                ht.insertQuadratic(name, phone);
                break;
            case 3:
                cout << "Enter name: "; cin >> name;
                cout << "Enter phone: "; cin >> phone;
                ht.insertDoubleHash(name, phone);
                break;
            case 4:
                cout << "Enter phone number to search: "; cin >> phone;
                ht.search(phone);
                break;
            case 5:
                ht.display();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 0);


    return 0;
}

