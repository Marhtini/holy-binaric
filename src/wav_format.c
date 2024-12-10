#include <stdio.h>
#include "wav_format.h"  // Include the header file that contains the wav_header_t struct

// Function to write the WAV header
void write_wav_header(FILE *file, unsigned int data_size) {
    wav_header_t header;

    // Fill in the WAV header fields
    header.riff[0] = 'R';
    header.riff[1] = 'I';
    header.riff[2] = 'F';
    header.riff[3] = 'F';
    
    header.chunk_size = 36 + data_size;  // Chunk size (data + header)
    
    header.wave[0] = 'W';
    header.wave[1] = 'A';
    header.wave[2] = 'V';
    header.wave[3] = 'E';

    header.fmt[0] = 'f';
    header.fmt[1] = 'm';
    header.fmt[2] = 't';
    header.fmt[3] = ' ';

    header.fmt_size = 16;  // Size of fmt chunk
    header.format = 1;     // PCM format
    header.channels = 2;   // Stereo (2 channels)
    header.sample_rate = 44100;  // Sample rate (44.1 kHz)
    header.byte_rate = 44100 * 2 * 16 / 8;  // byte_rate = sample_rate * channels * bits_per_sample / 8
    header.block_align = 2 * 16 / 8;  // block_align = channels * bits_per_sample / 8
    header.bits_per_sample = 16;  // 16-bit sample size

    header.data[0] = 'd';
    header.data[1] = 'a';
    header.data[2] = 't';
    header.data[3] = 'a';

    header.data_size = data_size;  // Size of the audio data (in bytes)

    // Write the header to the file
    fwrite(&header, sizeof(wav_header_t), 1, file);
}
