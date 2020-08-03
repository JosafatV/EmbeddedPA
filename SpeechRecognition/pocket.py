from pocketsphinx import LiveSpeech

print("pocketsphinx started audio recognition")
speech = LiveSpeech(lm=False, keyphrase='machine', kws_threshold=1e-20)
for phrase in speech:
    print(phrase.segments(detailed=True))
