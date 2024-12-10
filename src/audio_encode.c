#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Simple function to simulate the sending of a "short beep" or "long beep"
void send_beep(int duration_ms) {
    // TODO: Speaker API to generate beeps
    usleep(duration_ms * 1000); // Simulate the beep duration in milliseconds
}

void encode_and_transmit_audio(const char *audio_filename) {
    
    unsigned char byte;

    FILE *audio_file = fopen(audio_filename, "rb");
    if (!audio_file) {
        fprintf(stderr, "Failed to open audio file\n");
        return;
    }

    while (fread(&byte, sizeof(byte), 1, audio_file)) {
        for (int i = 7; i >= 0; --i) {
            if ((byte >> i) & 1) {
                send_beep(200); // Long beep for "1"
            } else {
                send_beep(100); // Short beep for "0"
            }
            usleep(100000); // Small pause between bits (100ms)
        }
        usleep(300000); // Longer pause between bytes (300ms)
    }

    fclose(audio_file);
}