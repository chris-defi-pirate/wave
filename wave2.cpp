#include <iostream>
using namespace std;
class Car {

private:
    string make;
    string model;
    int cur_speed;
    int key;

public:
    //default constructor
    Car();
    Car(const Car&);
    //destructor
    ~Car();

    //pointer to next in list
    Car* next;
    Car* prev;

    //set
    bool set_make(string);
    bool set_model(string);
    bool set_speed(int);
    bool set_key(int);

    //get
    string get_make();
    string get_model();
    int get_speed();
    int get_key();

    //display
    void display();
    void display_speed();
    void display_key();

    //movement
    int accelerate();
    int decelerate();

    //overloading
    //copy
    Car& operator=(const Car&);
    //comparison
    bool operator==(const Car&) const;
    //faster
    bool operator>(const Car&) const;
    //slower
    bool operator<(const Car&) const;
};
//this link always point to first Link
Car* head = NULL;
//this link always point to last Link
Car* last = NULL;
Car* current = NULL;
//is list empty
bool isEmpty() {
    return head == NULL;
}
int length() {
    int length = 0;
    Car* current;
    for (current = head; current != NULL; current = current->next) {
        length++;
    }
    return length;
}
//display the list in from first to last
void displayForward() {
    //start from the beginning
    Car* ptr = head;
    //navigate till the end of the list
    while (ptr != NULL) {
        ptr->display();
        ptr = ptr->next;
    }
}
//display the list from last to first
void displayBackward() {
    //start from the last
    Car* ptr = last;
    //navigate till the start of the list
    while (ptr != NULL) {
        //print data
        ptr->display();
        //move to next item
        ptr = ptr->prev;
    }
}
//insert link at the first location
void insertFirst(int key, string model) {
    //create a link
    Car* link = new Car();
    link->set_key(key);
    link->set_model(model);
    if (isEmpty()) {
        //make it the last link
        last = link;
    }
    else {
        //update first prev link
        head->prev = link;
    }
    //point it to old first link
    link->next = head;
    //point first to new first link
    head = link;
}
//insert link at the last location
void insertLast(int key, string model) {
    //create a link
    Car* link = new Car();
    link->set_key(key);
    link->set_model(model);
    if (isEmpty()) {
        //make it the last link
        last = link;
    }
    else {
        //make link a new last link
        last->next = link;
        //mark old last Car as prev of new link
        link->prev = last;
    }
    //point last to new last Car
    last = link;
}
//delete first item
Car* deleteFirst() {
    //save reference to first link
    Car* tempLink = head;
    //if only one link
    if (head->next == NULL) {
        last = NULL;
    }
    else {
        head->next->prev = NULL;
    }
    head = head->next;
    //return the deleted link
    return tempLink;
}
//delete link at the last location
Car* deleteLast() {
    //save reference to last link
    Car* tempLink = last;
    //if only one link
    if (head->next == NULL) {
        head = NULL;
    }
    else {
        last->prev->next = NULL;
    }
    last = last->prev;
    //return the deleted link
    return tempLink;
}
//delete a link with given key
Car* del(int key) {
    //start from the first link
    Car* current = head;
    Car* previous = NULL;
    //if list is empty
    if (head == NULL) {
        return NULL;
    }
    //navigate through list
    while (current->get_key() != key) {
        //if it is last Car
        if (current->next == NULL) {
            return NULL;
        }
        else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }
    //found a match, update the link
    if (current == head) {
        //change first to point to next link
        head = head->next;
    }
    else {
        //bypass the current link
        current->prev->next = current->next;
    }
    if (current == last) {
        //change last to point to prev link
        last = current->prev;
    }
    else {
        current->next->prev = current->prev;
    }
    return current;
}
bool insertAfter(int key, int newKey, string model) {
    //start from the first link
    Car* current = head;
    //if list is empty
    if (head == NULL) {
        return false;
    }
    //navigate through list
    while (current->get_key() != key) {
        //if it is last Car
        if (current->next == NULL) {
            return false;
        }
        else {
            //move to next link
            current = current->next;
        }
    }
    //create a link
    Car* newLink = new Car();
    newLink->set_key(newKey);
    newLink->set_model(model);
    if (current == last) {
        newLink->next = NULL;
        last = newLink;
    }
    else {
        newLink->next = current->next;
        current->next->prev = newLink;
    }
    newLink->prev = current;
    current->next = newLink;
    return true;
}
int main() {
    insertFirst(1, "cat");
    insertFirst(2, "tiger");
    insertFirst(3, "dog");
    insertFirst(4, "horse");
    insertFirst(5, "duck");
    insertFirst(6, "cow");
    printf("\nList (First to Last): \n");
    displayForward();
    printf("\n");
    printf("\nList (Last to first): \n");
    displayBackward();
    printf("\nList , after deleting first record: \n");
    deleteFirst();
    displayForward();
    printf("\nList , after deleting last record: \n");
    deleteLast();
    displayForward();
    //printf("\nList , insert after key(4) : ");
    //insertAfter(4, 7, 13);
    //displayForward();
    printf("\nList , after delete key(4) : \n");
    del(4);
    displayForward();

    return 0;
}




//implementation
//overloading
// 
// faster
bool Car::operator>(const Car& other) const
{
    if (cur_speed > other.cur_speed)
        return true;
    else
        return false;
}
//slower
bool Car::operator<(const Car& other) const
{
    if (cur_speed < other.cur_speed)
        return true;
    else
        return false;
}

// 
//overloading = copy
Car& Car :: operator = (const Car& other)
{
    if (this == &other)
        return *this;
    make = other.make;
    model = other.model;
    cur_speed = other.cur_speed;
    key = other.key;
    return *this;
}

//comparison
bool Car::operator==(const Car& other) const
{
    if (make != other.make)
        return false;
    if (model != other.model)
        return false;
    return true;
}

//destructor
Car::~Car()
{
    cout << "deallocating Car" << endl;
}

//constructor functions
Car::Car(const Car& other)
{
    make = other.make;
    model = other.model;
    cur_speed = other.cur_speed;
    key = other.key;
    //deep copy
    //for (int i = o; i<other.sz; i++) a[i] = other.a[i]
}

Car::Car()
{
    make = "generic make";
    model = "generic model";
    cur_speed = 0;
    key = 0;
}

//movement functions
int Car::accelerate() {

    if (cur_speed > 135)
        cur_speed = 135;

    cur_speed += 5;
    return cur_speed;
}

int Car::decelerate() {

    if (cur_speed <= 0)
        cur_speed = 0;
    else
        cur_speed -= 5;
    return cur_speed;
}

//display functions
void Car::display_speed()
{
    cout << "current speed: " << cur_speed << endl;
}

void Car::display()
{
    cout << "key : " << key ;
    cout << " make : " << make ;
    cout << " model : " << model ;
    cout << " cur_speed : " << cur_speed << endl;
}


//set functions
bool Car::set_make(string new_make)
{
    make = new_make;
    return true;
}

bool Car::set_model(string new_model)
{
    model = new_model;
    return true;
}

bool Car::set_speed(int new_speed)
{
    cur_speed = new_speed;
    return true;
}

bool Car::set_key(int new_key)
{
    key = new_key;
    return true;
}

//get functions
string Car::get_make()
{
    return make;
}

string Car::get_model()
{
    return model;
}

int Car::get_speed()
{
    return cur_speed;
}

int Car::get_key()
{
    return key;
}



