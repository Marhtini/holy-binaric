#include <stdio.h>
#include "audio_capture.h"

int main(int argc, char *argv[]) {
    
    snd_pcm_t* capture_handle = init_mic(); // Initialize the microphone
    capture_audio(capture_handle); // Start capturing audio
    return 0;

}