# Holy Binaric

Holy Binaric is an experimental project that demonstrates data transmission through sound. This project is designed for wearable Raspberry Pi devices running Ubuntu Server, enabling communication by encoding and decoding binary data into audible beeps. It serves as a proof-of-concept for low-cost, sound-based data transfer in constrained environments.

## Features [Present and Future]

- **Microphone Input**: Capture audio data using a connected microphone.
- **Binary Encoding**: Convert textual or binary input into an audio signal represented by a sequence of beeps.
- **Sound Transmission**: Transmit the encoded audio signal over the air.
- **Decoding and Reconstruction**: Decode the received audio signal back into its original binary format.
- **Cross-Device Communication**: Send and receive data between multiple Raspberry Pi devices.

## Prerequisites

- A Raspberry Pi running Ubuntu Server.
- A connected microphone and speaker for sound input/output.
- GCC or Clang for C compilation.
- Basic tools for C development (e.g., `make`, `gcc`).

## Getting Started

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Marhtini/holy-binaric.git
   cd holy-binaric
   ```

2. **Build the Project**

   Use the provided `Makefile` to build the project:

   ```bash
   make
   ```

3. **Run the Program**

   To start the encoding/decoding process:

   ```bash
   ./holy-binaric
   ```

4. **Configure Audio Devices**

   Ensure your microphone and speaker are correctly configured. Use tools like `alsamixer` or `arecord` to manage audio devices.

   ```bash
   alsamixer
   ```

## Usage

### Encoding and Transmission

1. Input data to be transmitted (text or binary).
2. The program will encode the data into a sequence of beeps.
3. Play the audio through the speaker.

### Receiving and Decoding

1. Capture the transmitted audio using the microphone.
2. The program will decode the audio back into the original binary format.
3. Verify the received data.

## Project Structure

```
.
├── src
│   ├── encoder.c        # Handles binary-to-sound conversion
│   ├── decoder.c        # Handles sound-to-binary conversion
│   ├── audio_io.c       # Manages microphone and speaker interactions
│   └── main.c           # Entry point of the application
├── include              # Header files
├── Makefile             # Build automation
└── README.md            # Project documentation
```

## Future Improvements

- **Error Correction**: Implement robust error-detection and correction mechanisms.
- **Signal Optimization**: Optimize sound frequency ranges for better clarity and performance.
- **Real-Time Processing**: Improve decoding speed for near real-time communication.
- **Cross-Platform Compatibility**: Extend support to other hardware and operating systems.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests to improve this project.

1. Fork the repository.
2. Create a new branch for your feature or bug fix:

   ```bash
   git checkout -b feature-name
   ```

3. Commit your changes:

   ```bash
   git commit -m "Add feature-name"
   ```

4. Push to your branch:

   ```bash
   git push origin feature-name
   ```

5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to the open-source community for providing inspiration and tools to make this project possible.
