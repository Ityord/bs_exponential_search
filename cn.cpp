#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void simulateStopAndWait(int totalFrames) {
    int currentFrame = 1;
    srand(time(0));

    while (currentFrame <= totalFrames) {
        cout << "\n[Sender]: Sending Frame " << currentFrame << "... ";
        
        // Simulate 30% chance of packet loss
        if (rand() % 10 < 3) {
            cout << "FAILED (Timeout!)" << endl;
            cout << "[Sender]: Resending Frame " << currentFrame << "...";
        }
        
        cout << " SUCCESS (ACK Received)" << endl;
        currentFrame++;
    }
    cout << "\nAll frames sent successfully using Stop-and-Wait." << endl;
}

void simulateGoBackN(int totalFrames, int windowSize) {
    int nextFrameToSend = 1;
    srand(time(0));

    while (nextFrameToSend <= totalFrames) {
        // Send a window of frames
        for (int i = 0; i < windowSize && (nextFrameToSend + i) <= totalFrames; i++) {
            cout << "[Sender]: Sending Frame " << nextFrameToSend + i << endl;
        }

        // Simulate which frame fails (if any)
        int failedAt = rand() % (windowSize + 2); // Random failure point

        if (failedAt < windowSize && (nextFrameToSend + failedAt) <= totalFrames) {
            int lostFrame = nextFrameToSend + failedAt;
            cout << "!!! Frame " << lostFrame << " LOST !!!" << endl;
            cout << "[Receiver]: Discarding subsequent frames. Requesting Resend from " << lostFrame << endl;
            // Go back to the lost frame
            nextFrameToSend = lostFrame;
        } else {
            cout << "[Receiver]: ACK received for window up to " << min(nextFrameToSend + windowSize - 1, totalFrames) << endl;
            nextFrameToSend += windowSize;
        }
        cout << "------------------------------------" << endl;
    }
}

#include <vector>

void simulateSelectiveRepeat(int totalFrames, int windowSize) {
    vector<bool> ackReceived(totalFrames + 1, false);
    int base = 1;
    srand(time(0));

    while (base <= totalFrames) {
        // Send frames in current window that haven't been ACKed
        for (int i = 0; i < windowSize && (base + i) <= totalFrames; i++) {
            int current = base + i;
            if (!ackReceived[current]) {
                cout << "[Sender]: Sending Frame " << current << endl;
            }
        }

        // Simulate random ACKs for the window
        for (int i = 0; i < windowSize && (base + i) <= totalFrames; i++) {
            int current = base + i;
            if (!ackReceived[current]) {
                if (rand() % 10 > 2) { // 70% success rate
                    cout << "[Receiver]: Frame " << current << " received. Sending ACK." << endl;
                    ackReceived[current] = true;
                } else {
                    cout << "!!! Frame " << current << " DROPPED !!!" << endl;
                }
            }
        }

        // Slide the window base if the first frame(s) in window are ACKed
        while (base <= totalFrames && ackReceived[base]) {
            base++;
        }
        cout << "--- Window slides to base " << base << " ---" << endl;
    }
}

int main() {
    int frames = 10;
    int window = 3;

    cout << "=== SIMULATING STOP-AND-WAIT ===" << endl;
    simulateStopAndWait(frames);

    cout << "\n=== SIMULATING GO-BACK-N (Window: " << window << ") ===" << endl;
    simulateGoBackN(frames, window);

    cout << "\n=== SIMULATING SELECTIVE REPEAT (Window: " << window << ") ===" << endl;
    simulateSelectiveRepeat(frames, window);

    return 0;
}
