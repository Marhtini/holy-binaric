#ifndef WAV_FORMAT_H
#define WAV_FORMAT_H

// WAV file header structure
typedef struct {
    char riff[4]; // "RIFF"
    unsigned int chunk_size;
    char wave[4]; // "WAVE"
    char fmt[4];  // "fmt "
    unsigned int fmt_size;
    unsigned short format;
    unsigned short channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short block_align;
    unsigned short bits_per_sample;
    char data[4]; // "data"
    unsigned int data_size;
} wav_header_t;

// Constants for WAV format
#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BITS_PER_SAMPLE 16

void write_wav_header(FILE *file, unsigned int data_size);

#endif // WAV_FORMAT_H