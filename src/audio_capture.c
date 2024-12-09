#include <stdio.h>
#include <stdlib.h>
#include "audio_capture.h"
#include <alsa/asoundlib.h>

snd_pcm_t* init_mic(){
	
	int i;
	int err;  // Stores error codes returned by ALSA functions
	unsigned int rate = 44100; // sample rate
	snd_pcm_t *capture_handle;  // Handle for the audio capture device
    snd_pcm_hw_params_t *hw_params;  // Structure for hardware parameters

	if((err = snd_pcm_open(&capture_handle, "hw:0", SND_PCM_STREAM_CAPTURE, 0)) < 0){
		fprintf(stderr, "unable to open audio device %s (%s)\n", "hw:0", snd_strerror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "unable to allocate memory for the param struct (%s)\n", snd_strerror(err));
		exit(1);
	}  // Allocate memory for hw_params

	if((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0){
		fprintf(stderr, "can't init hw_params with default values. (%s)\n", snd_strerror(err));
		exit(1);
	} // Initialize hw_params with default values

	if((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){
		fprintf(stderr, "attempt to set interleaved mode has failed. (%s)\n", snd_strerror(err));
		exit(1);
	} // In interleaved mode, audio samples for each channel are stored sequentially (e.g., Left-Right-Left-Right).

	if((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0){
		fprintf(stderr, "setting audio format failed. (%s)\n", snd_strerror(err));
		exit(1);
	} // Sets the format to 16-bit little-endian. This is a common format that balances quality and memory usage.

	if((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0){
		fprintf(stderr, "setting sample rate failed. (%s)\n", snd_strerror(err));
		exit(1); // Set sample rate to int rate
	}

	if((snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0){
		fprintf(stderr, "unable to set channels to stereo. (%s)\n", snd_strerror(err));
		exit(1);
	} // Setup stereo channels (2)

	if((snd_pcm_hw_params(capture_handle, hw_params)) < 0){
		fprintf(stderr, "unable to assign parameters to capture handle. (%s)\n", snd_strerror(err));
		exit(1);
	} // Assign all parameters to the capture handle.

	snd_pcm_hw_params_free(hw_params); // Free memory allocated for hw_params struct.

	return capture_handle; // Return pointer to device

}

int capture_audio(snd_pcm_t* capture_handle){
    
	int err;
	int silent = 1;
	short buf[BUFFER_SIZE * 2];  // Buffer for storing audio data (128 frames × 2 channels = 256 samples for Stereo)

	snd_pcm_prepare(capture_handle); // Prepare the device for capturing

	while(1){

		int silent = 1; // Reset silent flag for each iteration

        if ((err = snd_pcm_readi(capture_handle, buf, BUFFER_SIZE)) != BUFFER_SIZE) {
            fprintf(stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
            break;
        } // Capture audio data into buffer

		// Analyze buffer for silence detection
        for (int i = 0; i < BUFFER_SIZE * 2; ++i) {  // For stereo: 2 samples per frame
            if (abs(buf[i]) > SILENCE_THRESHOLD) {  
                silent = 0;
                break;
            } // Detect non-silent samples
		}

        if (silent) {
            printf("Silence detected. Stopping capture.\n");
            break;
        } // Stop capturing if silence is detected

		// TODO:
        // Process the audio data here (e.g., send it over a network or encode it)
	}

	snd_pcm_close(capture_handle);
	return 0;
}
