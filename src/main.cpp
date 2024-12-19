#include <stdlib.h>
#include <iostream>
#include <portaudio.h>

static void checkError(PaError err){
    if (err != paNoError){
        printf("PortAudio error: %\n", Pa_GetErrorText(err));
        exit(EXIT_FAILURE);
    }
}

int main(){
    
    PaError p_err;
    p_err = Pa_Initialize();
    checkError(p_err);

    int numDevices = Pa_GetDeviceCount();
    
    if (numDevices < 0){
        std::cout << "Error getting device count." << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(numDevices == 0){
        std::cout << "No audio devices avaialble." << std::endl;
        exit(EXIT_SUCCESS);
    }

    const PaDeviceInfo* deviceInfo;
    for (int i = 0; i < numDevices; i++){
        deviceInfo = Pa_GetDeviceInfo(i);
        printf("Device %d:\n", i);
        printf(" name: %s\n", deviceInfo->name);
        printf(" name: %s\n", deviceInfo->name);
        printf(" name: %s\n", deviceInfo->name);
        printf(" name: %s\n", deviceInfo->name);
    }

    p_err = Pa_Terminate();
    checkError(p_err);

    return EXIT_SUCCESS;
}