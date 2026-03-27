#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class TokenBucket {
private:
    int capacity;
    int tokens;
    int refill_rate; // tokens per second
    time_point<steady_clock> last_refill_time;

public:
    TokenBucket(int cap, int rate) 
        : capacity(cap), refill_rate(rate), tokens(cap) {
        last_refill_time = steady_clock::now();
    }

    // Update token count based on elapsed time
    void refill() {
        auto now = steady_clock::now();
        double elapsed = duration_cast<milliseconds>(now - last_refill_time).count() / 1000.0;
        
        int new_tokens = static_cast<int>(elapsed * refill_rate);
        if (new_tokens > 0) {
            tokens = min(capacity, tokens + new_tokens);
            last_refill_time = now;
            cout << "\n[REFILL] Added " << new_tokens << " tokens. Total: " << tokens;
        }
    }

    bool handlePacket(int packet_size) {
        refill(); // Always check for new tokens before processing

        cout << "\nIncoming packet (Size: " << packet_size << ")";
        if (tokens >= packet_size) {
            tokens -= packet_size;
            cout << " -> [ACCEPTED] Tokens remaining: " << tokens;
            return true;
        } else {
            cout << " -> [DROPPED] Not enough tokens!";
            return false;
        }
    }
};

int main() {
    // Capacity of 10 tokens, refill rate of 2 tokens per second
    TokenBucket bucket(10, 2);

    // Simulated packet arrivals
    int packet_sizes[] = {5, 3, 4, 2, 8};

    for (int size : packet_sizes) {
        bucket.handlePacket(size);
        
        // Wait 1.5 seconds between packets
        this_thread::sleep_for(milliseconds(1500));
    }

    return 0;
}
