#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#include <alsa/asoundlib.h>

// Constants
#define BUFFER_SIZE 128
#define SILENCE_THRESHOLD 500

snd_pcm_t* init_mic();
int capture_audio(snd_pcm_t* capture_handle);

#endif // AUDIO_CAPTURE_H