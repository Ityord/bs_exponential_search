#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class LeakyBucket {
private:
    int bucket_capacity;
    int output_rate;
    int current_bucket_size;

public:
    LeakyBucket(int capacity, int out_rate) {
        bucket_capacity = capacity;
        output_rate = out_rate;
        current_bucket_size = 0;
    }

    void addPacket(int packet_size) {
        cout << "\nIncoming packet size: " << packet_size;
        
        if (packet_size > (bucket_capacity - current_bucket_size)) {
            cout << " -> [REJECTED] Bucket overflow!";
        } else {
            current_bucket_size += packet_size;
            cout << " -> [ACCEPTED] Current bucket status: " 
                 << current_bucket_size << "/" << bucket_capacity;
        }
    }

    void transmit() {
        if (current_bucket_size > 0) {
            int transmitted = min(current_bucket_size, output_rate);
            current_bucket_size -= transmitted;
            cout << "\n[LEAKING] Transmitted: " << transmitted 
                 << " units. Remaining in bucket: " << current_bucket_size;
        } else {
            cout << "\n[IDLE] Bucket is empty. No data to transmit.";
        }
    }
};

int main() {
    int capacity, out_rate, num_packets;

    cout << "Enter Bucket Capacity: ";
    cin >> capacity;
    cout << "Enter Output Rate (units per second): ";
    cin >> out_rate;

    LeakyBucket bucket(capacity, out_rate);

    vector<int> packets = {4, 8, 2, 12, 5}; // Example packet sizes

    for (int p_size : packets) {
        bucket.addPacket(p_size);
        bucket.transmit();
        // Simulating a time interval between packet arrivals
        this_thread::sleep_for(chrono::milliseconds(500)); 
    }

    // Empty the remaining bucket
    cout << "\n\n--- Finalizing transmission ---";
    while (true) {
        bucket.transmit();
        if (packets.empty()) break; // Logic placeholder for remaining data
    }

    return 0;
}
