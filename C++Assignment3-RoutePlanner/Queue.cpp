#include "Queue.h"
#include <iostream>

const std::string cities[81] = {
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik",
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne",
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta",
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya",
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya",
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat",
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir",
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce"
};

// Constructor to initialize an empty queue
Queue::Queue(){
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cerr << "Queue Overflow! Cannot enqueue province " << province << std::endl;
        return;
    }
    // if province already in the queue
    if(contains(province)) {
        return;
    }

    if (isEmpty()) {
        front = 0;
        rear = 0;

    }else {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
    }
    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    int temp = data[front];

    if(front == rear) {
        front = -1;
        rear = -1;

    }else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }

    return temp;
}

// Returns the front province without removing it
int Queue::peek() const {
    if (isEmpty()) {
        return -1;
    }
    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    if (front == -1 && rear == -1) {
        return true;
    }
    return false;
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cerr << "Queue Overflow! Cannot enqueue priority province " << province << std::endl;
        return;
    }

    // if province already in the queue
    if(contains(province)) {
        return;
    }

    if (isEmpty()) {
        enqueue(province);
        return;
    }

    front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    data[front] = province;
}
void Queue::printQueue() const {
    if (isEmpty()) {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    std::cout << "Queue elements: ";
    int i = front;
    while (i != rear) {
        std::cout << cities[data[i]] <<" "<< data[i] << " ";
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    std::cout << cities[data[rear]] <<" "<< data[rear]<< std::endl;

}
bool Queue::contains(int element) const {
    if (isEmpty()) {
        return false;
    }

    int i = front;
    while (i != rear) {
        if (data[i] == element) {
            return true;
        }
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    if (data[rear] == element) {
        return true;
    }
    return false;
}