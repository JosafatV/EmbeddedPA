Institituto Tecnológico de Costa Rica
Computer Engineering
# EmbeddedPA
Esteban Ferarios
Josafat Vargas
Sebastián Víquez

### GPIO

Contains the thread manager and the LED controller for the system. Compiles with Cmake, instructions in the ReadMe inside assume you understand cross-compiling with Yocto and have the environment ready. Tests are made with Sumo.

### PA_app
Includes the files needed to create the mobile App.

### Server
Contains the source code for the pyrebase server.

### SpeechRecognition
Contains the source code for the audio_service and tests for both PyAudio and PocketSphinx. Dependencies not included.

### RaspFiles
Contains the files used for testing. The audio_service uses a dummy instead of speech recognition until we ca get pocketsphinx to work.

