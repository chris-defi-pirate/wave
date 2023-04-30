#include <iostream>
#include <iomanip>
using namespace std;
class Car {

private:
    string make;
    string model;
    double cur_velocity;
    int key;
    double x_coord;
    double y_coord;
    double car_length;
    double safe_distance;

public:
    //default constructor
    Car();
    //paramaterized constructor
    Car(int key, string make, string model, double velocity, double xcoord, double ycoord, double car_length, double safe_distance);
    //copy constructor
    Car(const Car&);
    //destructor
    ~Car();

    //pointer to next in list
    Car* next;
    Car* prev;

    //set
    bool set_make(string);
    bool set_model(string);
    bool set_velocity(double);
    bool set_key(int);
    bool set_loc(double, double);
    bool moveby(double, double);
    bool set_x_coord(double);
    bool set_y_coord(double);
    bool set_car_length(double);
    bool set_safe_distance(double);

    //get
    string get_make();
    string get_model();
    double get_velocity();
    int get_key();
    double get_x_coord();
    double get_y_coord();
    double get_car_length();
    double get_safe_distance();

    //display
    void display();
    void display_make();
    void display_model();
    void display_velocity();
    void display_key();
    void display_x_coord();
    void display_y_coord();
    void display_car_length();
    void display_safe_distance();

    //movement
    double accelerate();
    double decelerate();

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

//gap between cars
void display_gap(Car& other)
{
    Car* tmp = other.next;
    //navigate till the end of the list
    if (tmp != NULL) {
        // calculate the distance between the current car and the one in front of it
        double distance = tmp->get_x_coord() - other.get_x_coord() - other.get_car_length();
        // calculate the sum of the length of the two cars and a safety gap value
        double stoppingDistance = other.get_car_length() + tmp->get_car_length() + tmp->get_safe_distance();
        // calculate the gap between the cars
        double gap = stoppingDistance - distance;
        // if the distance is less than the stopping distance, reduce the gap

        if (distance < stoppingDistance) {
            double gap = tmp->get_x_coord() - (stoppingDistance - distance);
            if (gap < 0) {
                gap = 0;
            }
        }
        cout << " | gap: " << gap;
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
        // the gap between cars isn't being calculated correctly
        // this could be improved upon
        //display_gap(*ptr);
        cout << endl;
        //move to next item
        ptr = ptr->prev;
    }
}

//insert link at the first location passing in a car reference
void insertFirst(Car& other) {
    //create a link
    Car* link = new Car();
    link->set_key(other.get_key());
    link->set_make(other.get_make());
    link->set_model(other.get_model());
    link->set_velocity(other.get_velocity());
    link->set_loc(other.get_x_coord(), other.get_y_coord());
    link->set_car_length(other.get_car_length());
    link->set_safe_distance(other.get_safe_distance());
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
void insertLast(int key, string make, string model, double velocity, double x_coord, double y_coord, double car_length, double safe_distance) {
    //create a link
    Car* link = new Car();
    link->set_key(key);
    link->set_make(make);
    link->set_model(model);
    link->set_velocity(velocity);
    link->set_x_coord(x_coord);
    link->set_y_coord(y_coord);
    link->set_car_length(car_length);
    link->set_safe_distance(safe_distance);
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
bool insertAfter(int key, string make, string model, double velocity, double x_coord, double y_coord, double car_length, double safe_distance) {
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
    newLink->set_key(key);
    newLink->set_make(make);
    newLink->set_model(model);
    newLink->set_velocity(velocity);
    newLink->set_x_coord(x_coord);
    newLink->set_y_coord(y_coord);
    newLink->set_car_length(car_length);
    newLink->set_safe_distance(safe_distance);
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

void hitTheBreaks(double breakAmt) {
    // start from the beginning
    Car* ptr = last;
    Car* tmp_prev = ptr->prev;
    double savePrevV = 0;
    double savePrevD = 0;
    double savePrevSD = 0;
    // navigate till the end of the list
    while (ptr != NULL && tmp_prev != NULL) {
        if (ptr == last){
            ptr->set_velocity(ptr->get_velocity() * breakAmt);
        }
        else{
            // calculate the distance between the current car and the one in front of it
            double distance = tmp_prev->get_x_coord() - ptr->get_x_coord() - ptr->get_car_length();
            savePrevD = distance;
            // calculate the sum of the length of the two cars and a safety gap value
            double stoppingDistance = ptr->get_car_length() + tmp_prev->get_car_length() + tmp_prev->get_safe_distance();
            savePrevSD = stoppingDistance;
            // if the distance is less than the stopping distance, reduce the velocity of the current car
            if (distance < stoppingDistance) {
                double newVelocity = (tmp_prev->get_velocity() - (stoppingDistance + distance)) * breakAmt;
                if (newVelocity < 0) {
                    newVelocity = 0;
                }
                ptr->set_velocity(newVelocity);
                savePrevV = newVelocity;
            }


        }
        // move to the next car in the list
        ptr = ptr->prev;
        tmp_prev = ptr->prev;
        if (ptr == head)
            ptr->set_velocity( ((50 -(savePrevSD + savePrevD)) * breakAmt) * ptr->get_safe_distance());
    }
}

//reset speed to compare the differences in breaking power
void resetVelocity() {
    //start from the last
    Car* ptr = last;
    //navigate till the start of the list
    while (ptr != NULL) {
        ptr->set_velocity(50);
        ptr = ptr->prev;
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    cout << "Initial cars added into the que" << endl;
    Car c1(1, "Audi",    "A8",     50.0, 1.0, 1.0, 17.4, .1);
    Car c2(2, "Ford", "F150", 50.0, c1.get_x_coord() + c1.get_car_length(), c1.get_y_coord(), 17.42, .31);
    Car c3(3, "Honda", "CBR", 50.0, c2.get_x_coord() + c2.get_car_length(), c2.get_y_coord(), 10.98, .53);
    Car c4(4, "VW", "Golf", 50.0, c3.get_x_coord() + c3.get_car_length(), c3.get_y_coord(), 13.96, .44);
    Car c5(5, "Toyota", "Titan", 50.0, c4.get_x_coord() + c4.get_car_length(), c4.get_y_coord(), 19.01, .62);
    Car c6(6, "Porsche", "Boxter", 50.0, c5.get_x_coord() + c5.get_car_length(), c5.get_y_coord(), 14.54, .21);
    insertFirst(c1);
    insertFirst(c2);
    insertFirst(c3);
    insertFirst(c4);
    insertFirst(c5);
    insertFirst(c6);
    displayBackward();
    cout << endl;

    double breakAmt = .9;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();
    cout << endl;
    
    resetVelocity();
    cout << endl;
    breakAmt = .8;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();
    cout << endl;

    resetVelocity();
    breakAmt = .7;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = .6;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = .5;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();


    resetVelocity();
    cout << endl;
    breakAmt = .4;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = .3;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = .2;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = .1;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = 0.05;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = 0.01;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    resetVelocity();
    cout << endl;
    breakAmt = 0;
    cout << "applying the breaks with " << breakAmt << endl;
    hitTheBreaks(breakAmt);
    cout << endl;
    displayBackward();

    return 0;
}




//implementation
//overloading
// 
// faster
bool Car::operator>(const Car& other) const
{
    if (cur_velocity > other.cur_velocity)
        return true;
    else
        return false;
}
//slower
bool Car::operator<(const Car& other) const
{
    if (cur_velocity < other.cur_velocity)
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
    cur_velocity = other.cur_velocity;
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
   // cout << "deallocating Car" << endl;
}

//constructor functions
Car::Car(const Car& other)
{
    make = other.make;
    model = other.model;
    cur_velocity = other.cur_velocity;
    key = other.key;
    //deep copy
    //for (int i = o; i<other.sz; i++) a[i] = other.a[i]
}

Car::Car()
{
    make = "basic";
    model = "shiny";
    cur_velocity = 0;
    key = 0;
    x_coord = 1;
    y_coord = 1;
    car_length = 10;
    safe_distance = .25;
}

//paramaterized constructor
Car::Car(int new_key, string new_make, string new_model, double new_velocity, double new_xcoord, double new_ycoord, double new_car_length, double new_safe_distance)
{
    make = new_make;
    model = new_model;
    cur_velocity = new_velocity;
    key = new_key;
    x_coord = new_xcoord;
    y_coord = new_ycoord;
    car_length = new_car_length;
    safe_distance = new_safe_distance;
}

//movement functions
double Car::accelerate() {

    if (cur_velocity > 135)
        cur_velocity = 135;

    cur_velocity += 5;
    return cur_velocity;
}

double Car::decelerate() {

    if (cur_velocity <= 0)
        cur_velocity = 0;
    else
        cur_velocity -= 5;
    return cur_velocity;
}

//display functions
void Car::display_make()
{
    string tmp_make = get_make();
    cout << "make: " << tmp_make << endl;
}

void Car::display_model()
{
    string tmp_model = get_model();
    cout << "model: " << tmp_model << endl;
}

void Car::display_velocity()
{
    double tmp_velocity = get_velocity();
    cout << "current velocity: " << tmp_velocity << endl;
}

void Car::display_key()
{
    int tmp_key = get_key();
    cout << "key: " << tmp_key << endl;
}

void Car::display_x_coord()
{
    double tmp_x_coord = get_x_coord();
    cout << "current x_coord: " << tmp_x_coord << endl;
}

void Car::display_y_coord()
{
    double tmp_y_coord = get_y_coord();
    cout << "current x_coord: " << tmp_y_coord << endl;
}

void Car::display_car_length()
{
    double tmp_car_length = get_car_length();
    cout << "current car_length: " << tmp_car_length << endl;
}

void Car::display_safe_distance()
{
    double tmp_safe_distance = get_safe_distance();
    cout << "current safe_distance: " << tmp_safe_distance << endl;
}

void Car::display()
{
    cout << "key : " << get_key() ;
    cout << " | make : " << get_make() ;
    cout << " | model : " << get_model() ;
    cout << " | cur velocity : " << get_velocity();
    cout << " | x_coord : " << get_x_coord() ;
    //cout << " | y_coord : " << y_coord;
    cout << " | car len : " << get_car_length();
    cout << " | safe dist: " << get_safe_distance();
        //cout << endl;
}


//set functions
bool Car::set_make(string new_make)
{
    //standardize output
    int len = new_make.length();
    for (int i = 0; i < (10 - len); i++)
        new_make = new_make + " ";

    make = new_make;
    return true;
}

bool Car::set_model(string new_model)
{
    //standardize output
    int len = new_model.length();
    for (int i = 0; i < (10 - len); i++)
        new_model = new_model + " ";
    model = new_model;
    return true;
}

bool Car::set_velocity(double new_velocity)
{
    cur_velocity = new_velocity;
    return true;
}

bool Car::set_key(int new_key)
{
    key = new_key;
    return true;
}

//set location
bool Car::set_loc(double new_x, double new_y)
{
    x_coord = new_x;
    y_coord = new_y;
    return true;
}

//set x coord
bool Car::set_x_coord(double new_x)
{
    x_coord = new_x;
    return true;
}

bool Car::set_y_coord(double new_y)
{
    y_coord = new_y;
    return true;
}

bool Car::set_car_length(double new_car_length)
{
    car_length = new_car_length;
    return true;
}

bool Car::set_safe_distance(double new_safe_distance)
{
    safe_distance = new_safe_distance;
    return true;
}

//move location
bool Car::moveby(double dx, double dy)
{
    x_coord += dx;
    y_coord += dy;
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

double Car::get_velocity()
{
    return cur_velocity;
}

int Car::get_key()
{
    return key;
}

double Car::get_x_coord()
{
    return x_coord;
}

double Car::get_y_coord()
{
    return y_coord;
}

double Car::get_car_length()
{
    return car_length;
}

double Car::get_safe_distance()
{
    return safe_distance;
}

