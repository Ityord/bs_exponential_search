#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

enum AppType { VOIP, VIDEO, BROWSING, BACKGROUND_SYNC };

struct Packet {
    int id;
    int priority; // 1 (Highest) to 5 (Lowest)
    AppType type;
    
    std::string getTypeName() const {
        switch(type) {
            case VOIP: return "VoIP";
            case VIDEO: return "Video";
            case BROWSING: return "Browsing";
            case BACKGROUND_SYNC: return "Background Sync";
            default: return "Unknown";
        }
    }
};

void randomSelectionDrop(std::vector<Packet>& queue) {
    if (queue.empty()) return;
    
    int index = rand() % queue.size();
    std::cout << "[Random Drop] Dropping Packet ID: " << queue[index].id << "\n";
    queue.erase(queue.begin() + index);
}


void applicationBasedDrop(std::vector<Packet>& queue) {
    // Strategy: Find and drop the least critical application type first
    auto it = std::find_if(queue.begin(), queue.end(), [](const Packet& p) {
        return p.type == BACKGROUND_SYNC;
    });

    if (it != queue.end()) {
        std::cout << "[App Drop] Dropping Background Sync Packet ID: " << it->id << "\n";
        queue.erase(it);
    } else if (!queue.empty()) {
        // Fallback to dropping whatever is at the front if no background sync exists
        queue.erase(queue.begin());
    }


void priorityBasedDrop(std::vector<Packet>& queue) {
    if (queue.empty()) return;

    // Find the packet with the highest priority value (lowest importance)
    auto worstPacket = std::max_element(queue.begin(), queue.end(), [](const Packet& a, const Packet& b) {
        return a.priority < b.priority;
    });

    std::cout << "[Priority Drop] Dropping Low Priority (" << worstPacket->priority 
              << ") Packet ID: " << worstPacket->id << "\n";
    queue.erase(worstPacket);
}

class REDSimulator {
    double avg_q = 0.0;
    double w_q = 0.002; // Weight for moving average
    int min_th = 5;
    int max_th = 15;
    double max_p = 0.1; // Max drop probability

public:
    bool shouldDrop(int current_q_size) {
        // Calculate Exponential Weighted Moving Average (EWMA)
        avg_q = (1 - w_q) * avg_q + w_q * current_q_size;

        if (avg_q < min_th) {
            return false; // Queue is safe
        } else if (avg_q >= max_th) {
            return true;  // Queue is too full, drop everything
        } else {
            // Calculate probability of drop
            double pb = max_p * (avg_q - min_th) / (max_th - min_th);
            double random_val = (double)rand() / RAND_MAX;
            return random_val < pb;
        }
    }
};

int main() {
    srand(time(0));
    std::vector<Packet> buffer;
    REDSimulator red;

    // Simulate incoming packets
    for (int i = 1; i <= 20; ++i) {
        Packet p = {i, (rand() % 5) + 1, static_cast<AppType>(rand() % 4)};
        
        // Example: Using RED to decide if we even accept the packet
        if (red.shouldDrop(buffer.size())) {
            std::cout << "RED: Proactively dropped incoming Packet " << i << "\n";
        } else {
            buffer.push_back(p);
        }

        // Example: If buffer gets too large (e.g., > 10), apply Priority Drop
        if (buffer.size() > 10) {
            priorityBasedDrop(buffer);
        }
    }

    return 0;
}
}
