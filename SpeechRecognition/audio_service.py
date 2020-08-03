from fileManager import writeFile
from pocketsphinx import LiveSpeech
import pyaudio
import wave

def update_leds (status):
    if(select == 0):
        # Recording    
        writeFile("led_status.txt", "1:0:0")
    if(select == 1):
        # Processing
        writeFile("led_status.txt", "0:1:0")
    if(select == 2):
        # Listening
        writeFile("led_status.txt", "0:0:1")

def start_record(audio_id):
    CHUNK = 1024
    FORMAT = pyaudio.paInt16
    CHANNELS = 2
    RATE = 44100
    RECORD_SECONDS = 5
    WAVE_OUTPUT_FILENAME = "output"+str(audio_id)+".wav"
    audio_id += 1

    p = pyaudio.PyAudio()

    stream = p.open(format=FORMAT,
	            channels=CHANNELS,
	            rate=RATE,
	            input=True,
	            frames_per_buffer=CHUNK)

    update_leds(1)
    print("* recording")
    frames = []

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
	frames.append(data)

    print("* done recording")
    update_leds(2)
    stream.stop_stream()
    stream.close()
    p.terminate()

    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(p.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))
    wf.close()



def start_pocket():
	print("* started audio recognition")
	speech = LiveSpeech(lm=False, keyphrase='machine', kws_threshold=1e-20)
	audio_id = 0
	for phrase in speech:
		print(phrase.segments(detailed=True))
		update_leds(1)
		start_record(audio_id)
		audio_id += 1

start_pocket()
