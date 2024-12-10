#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "audio_capture.h"
#include "wav_format.h"

#define BUFFER_SIZE 128
#define SILENCE_THRESHOLD 500 // Threshold for silence detection
#define GRACE_PERIOD 3       // Grace period in seconds after silence is detected

// Function to initialize the microphone for ALSA capture
snd_pcm_t* init_mic() {
    int err;
    unsigned int rate = 44100; // Sample rate
    snd_pcm_t *capture_handle;
    snd_pcm_hw_params_t *hw_params;

    if ((err = snd_pcm_open(&capture_handle, "hw:0", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf(stderr, "unable to open audio device %s (%s)\n", "hw:0", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
        fprintf(stderr, "unable to allocate memory for the param struct (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
        fprintf(stderr, "can't init hw_params with default values. (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf(stderr, "attempt to set interleaved mode has failed. (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        fprintf(stderr, "setting audio format failed. (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0) {
        fprintf(stderr, "setting sample rate failed. (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
        fprintf(stderr, "unable to set channels to stereo. (%s)\n", snd_strerror(err));
        exit(1);
    }

    if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
        fprintf(stderr, "unable to assign parameters to capture handle. (%s)\n", snd_strerror(err));
        exit(1);
    }

    snd_pcm_hw_params_free(hw_params);

    return capture_handle;
}

// Function to capture audio and write to a WAV file
int capture_audio_to_wav(snd_pcm_t *capture_handle, const char *filename) {
    int err;
    short buf[BUFFER_SIZE * 2];  // Buffer for capturing audio data (stereo, 2 channels)
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    unsigned int data_size = 0;

    // Write the initial WAV header (we'll update the data size later)
    write_wav_header(file, data_size);

    // Grace period timer variable
    int silent_counter = 0;

    // Capture audio and write to file
    while (1) {
        int silent = 1;

        if ((err = snd_pcm_readi(capture_handle, buf, BUFFER_SIZE)) != BUFFER_SIZE) {
            fprintf(stderr, "Read error: %s\n", snd_strerror(err));
            break;
        }

        // Detect silence by checking the buffer
        for (int i = 0; i < BUFFER_SIZE * 2; ++i) { // Stereo: 2 samples per frame
            if (abs(buf[i]) > SILENCE_THRESHOLD) {
                silent = 0;
                break;
            }
        }

        if (silent) {
            if (silent_counter >= GRACE_PERIOD * SAMPLE_RATE / BUFFER_SIZE) {
                printf("Silence detected. Stopping capture.\n");
                break; // Stop capture after grace period
            } else {
                silent_counter++;
                printf("Silence detected. Grace period remaining: %d seconds\n", GRACE_PERIOD - (silent_counter * BUFFER_SIZE / SAMPLE_RATE));
            }
        } else {
            silent_counter = 0; // Reset grace period if there's audio
        }

        // Write the captured data to the file
        int bytes_to_write = BUFFER_SIZE * 2 * sizeof(short);  // 2 channels, 16 bits per sample
        data_size += bytes_to_write;
        fwrite(buf, bytes_to_write, 1, file);

    }

    // Update the WAV header with the correct data size
    fseek(file, 4, SEEK_SET);  // Move to chunk size position
    fwrite(&data_size, sizeof(data_size), 1, file);

    fseek(file, 40, SEEK_SET);  // Move to data size position
    fwrite(&data_size, sizeof(data_size), 1, file);

    fclose(file);
    return 0;
}
