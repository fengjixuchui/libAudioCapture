#include <cassert>
#include <atomic>
#include <fstream>
#include <iostream>
#include <thread>

#include "AudioCaptureEngine.h"

int main()
{
    AudioCaptureEngine ENGINE;
    ENGINE.Init();

    std::atomic<bool> bStop(false);
    std::thread t = std::thread([&](){
        std::cout << "\n";
        for (auto i=0; i<10; i++) {
            std::cout << "\rrecording ... " << i+1 << "/10" << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "\n";
        bStop.store(true);
    });

    uint32_t const PERIOD = 1024;   // 1024 frames per period
    uint32_t const CHANNEL = 2;     // stereo
    uint32_t const bufferSize = 2 * CHANNEL * PERIOD; // 2 means 16 bits (2 bytes)
    char* buffer = new char [bufferSize];

    std::ofstream output("./sound.pcm", std::ios::binary | std::ios::trunc);

    while (!bStop) {
        long ret = -1;
        ret = ENGINE.GetBuffer(buffer, PERIOD);
        if (ret < 0) {
            std::clog << "XRUN...\n";
            continue;
        }

        if (output.is_open()) {
            output.write(buffer, bufferSize);
            assert(output.good());
        }
    }

    if (output.is_open()) {
        output.close();
    }

    if (buffer) {
        delete [] buffer;
    }

    if (t.joinable()) {
        t.join();
    }

    ENGINE.Uninit();
}
