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

    long ret = 0;
    uint32_t aDataSize = 0;
    void* pData = nullptr;

    std::ofstream output("./sound.pcm", std::ios::binary | std::ios::trunc);

    while (!bStop) {
        ret = ENGINE.GetBuffer(&pData, aDataSize);
        if (ret < 0) {
            std::clog << "XRUN...\n";
            continue;
        }

        if (output.is_open() && pData && aDataSize > 0) {
            output.write(static_cast<char*>(pData), aDataSize);
            assert(output.good());
        }
    }

    if (output.is_open()) {
        output.close();
    }

    if (t.joinable()) {
        t.join();
    }

    ENGINE.Uninit();
}
