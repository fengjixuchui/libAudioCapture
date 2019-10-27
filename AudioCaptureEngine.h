#ifndef AUDIOCAPTUREENGINE_H
#define AUDIOCAPTUREENGINE_H

#include "libAudioCapture_global.h"

class LIBAUDIOCAPTURE_EXPORT AudioCaptureEngine
{
public:
    AudioCaptureEngine();
    ~AudioCaptureEngine();

    void Init();
    void Uninit();

    long GetBuffer(void** ppData, uint32_t& aDataSize);

private:
    uint32_t PERIOD;
    uint32_t CHANNEL;
    uint32_t FORMAT;
    uint32_t SAMPLE_RATE;

    uint32_t mPcmSize;
    char* mPcmBuffer;
};

#endif // AUDIOCAPTUREENGINE_H
