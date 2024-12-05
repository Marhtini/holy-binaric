#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

void init_mic(){

	int i;
	int err;  // Stores error codes returned by ALSA functions
	unsigned int rate = 44100; // sample rate
    short buf[128 * 2];  // Buffer for storing audio data (128 frames × 2 channels = 256 samples for Stereo)
    snd_pcm_t *capture_handle;  // Handle for the audio capture device
    snd_pcm_hw_params_t *hw_params;  // Structure for hardware parameters'

	if((err = snd_pcm_open(&capture_handle, "hw:0", SND_PCM_STREAM_CAPTURE, 0)) < 0){
		fprintf(stderr, "unable to open audio device %s (%s)\n", "hw:0", snd_stderror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "can't allocate hardware param struct (%s)\n", snd_stderror(err));
		exit(1);
	}

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0){
		fprintf(stderr, "unable to allocate memory for the param struct (%s)\n", snd_stderror(err));
		exit(1);
	}  // Allocate memory for hw_params

	if((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0){
		fprintf(stderr, "can't init hw_params with default values. (%s)\n", snd_stderror(err));
		exit(1);
	} // Initialize hw_params with default values

	if((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0){
		fprintf(stderr, "attempt to set interleaved mode has failed. (%s)\n", snd_stderror(err));
		exit(1);
	} // In interleaved mode, audio samples for each channel are stored sequentially (e.g., Left-Right-Left-Right).

	if((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0){
		fprintf(stderr, "setting audio format failed. (%s)\n", snd_stderr(err));
		exit(1);
	} // Sets the format to 16-bit little-endian. This is a common format that balances quality and memory usage.

	if((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0){
		fprintf(stderr, "setting sample rate failed. (%s)\n", snd_stderr(err));
		exit(1);
	}


}

void capture_audio(){
    
}