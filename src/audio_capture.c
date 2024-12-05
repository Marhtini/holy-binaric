#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

void init_mic(){

	int i;
	int err;  // Stores error codes returned by ALSA functions
    short buf[128 * 2];  // Buffer for storing audio data (128 frames × 2 channels = 256 samples for Stereo)
    snd_pcm_t *capture_handle;  // Handle for the audio capture device
    snd_pcm_hw_params_t *hw_params;  // Structure for hardware parameters'

	if((err = snd_pcm_open(&capture_handle, "hw:0", SND_PCM_STREAM_CAPTURE, 0)) < 0){
		fprintf(stderr, "unable to open audio device %s (%s)\n", "hw:0", snd_stderror(err));
		exit(1);
	}

	if((err = err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "can't allocate hardware param struct (%s)\n", snd_stderror(err));
		exit(1);
	}

	if((snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "unable to allocate memory for the param struct (%s)\n", stderror(err));
		exit(1);

	}  // Allocate memory for hw_params
	snd_pcm_hw_params_any(capture_handle, hw_params);  // Initialize hw_params with default values



}

void capture_audio(){
    
}