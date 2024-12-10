#include <stdio.h>
#include "include/audio_capture.h"

int main(int argc, char *argv[]) {
    snd_pcm_t *capture_handle = init_mic();  // Initialize the microphone

    // If a filename is passed as an argument, use it for the output WAV file
    const char *filename = (argc > 1) ? argv[1] : "output.wav";  // Default to "output.wav" if no filename is provided

    // Capture audio and write to WAV file
    int result = capture_audio_to_wav(capture_handle, filename);

    if (result == 0) {
        printf("Audio successfully captured to %s\n", filename);
    } else {
        printf("Error capturing audio to file.\n");
    }

    snd_pcm_close(capture_handle);  // Close the capture device
    return 0;
}