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

    long GetBuffer(void* pData, uint32_t aDataSize);
};

#endif // AUDIOCAPTUREENGINE_H
