#include "AudioCaptureEngine.h"

#include <alsa/asoundlib.h>

static snd_pcm_t *capture_handle = nullptr;

AudioCaptureEngine::AudioCaptureEngine()
{
}

AudioCaptureEngine::~AudioCaptureEngine()
{
    assert(capture_handle == nullptr);
}

void AudioCaptureEngine::Init()
{
    if (capture_handle) {
        return;
    }

    snd_pcm_hw_params_t *hw_params = nullptr;

    snd_pcm_stream_t const CAPTURE = SND_PCM_STREAM_CAPTURE;
    snd_pcm_access_t const ACCESS = SND_PCM_ACCESS_RW_INTERLEAVED;
    snd_pcm_format_t const FORMAT = SND_PCM_FORMAT_S16;
    uint32_t SAMPLE_RATE = 44100;
    uint32_t const CHANNEL = 2;

    int err;

    if ((err = snd_pcm_open (&capture_handle, "default", CAPTURE, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", "default", snd_strerror (err));
        return;
    }
    fprintf(stdout, "audio interface opened\n");

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params allocated\n");

    if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params initialized\n");

    if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, ACCESS)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params access setted\n");

    if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, FORMAT)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params format setted\n");

    if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &SAMPLE_RATE, nullptr)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params rate setted\n");

    if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, CHANNEL)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params channels setted\n");

    if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "hw_params setted\n");

    snd_pcm_hw_params_free (hw_params);
    hw_params = nullptr;
    fprintf(stdout, "hw_params freed\n");

    if ((err = snd_pcm_prepare (capture_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror (err));
        return;
    }
    fprintf(stdout, "audio interface prepared\n");
}

void AudioCaptureEngine::Uninit()
{
    if (capture_handle) {
        snd_pcm_close(capture_handle);
        capture_handle = nullptr;
    }
}

long AudioCaptureEngine::GetBuffer(void* pData, uint32_t aDataSize)
{
    auto ret = snd_pcm_readi(capture_handle, pData, aDataSize);
    if (ret < 0) {
        if (capture_handle) {
            snd_pcm_prepare(capture_handle);
        }
    }
    return ret;
}
