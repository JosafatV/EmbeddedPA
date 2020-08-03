# -*- coding: utf-8 -*-
import pyrebase
import os
import time

#Constants
##Firebase configuration
CONFIG = {
            "apiKey": "AIzaSyCmnqe1sRfogwGpd957pOPdw7JaBqoK4Ws",
            "authDomain": "smarthouse-emb.firebaseapp.com",
            "databaseURL": "https://smarthouse-emb.firebaseio.com",
            "projectId": "smarthouse-emb",
            "storageBucket": "smarthouse-emb.appspot.com",
            "messagingSenderId": "425195900251",
            "appId": "1:425195900251:web:5d0b6a1f10c0c08f9e9e7e",
            "measurementId": "G-DBWNB0ZZCK"
        }

##Path of the audio file to upload
PATH = '/home/sebas/TEC/Sistemas Embebidos/Proyectos/Proyecto 3/Código/EmbeddedPA/Server'

##Filename extension
EXTENSION = '.wav'

#Connection to Firebase storage
##Pyrebase initializer
firebase = pyrebase.initialize_app(CONFIG)
##Storage in Firebase
storage = firebase.storage()

#Check for changes in directory, in searching for audio files
def checkFiles():
    #List that stores names of uploaded audios
    uploadedList=[]
    while(True):
        try:
            time.sleep(2)
            #Each file in the path directory
            for file in os.listdir(PATH):
                #Each file with audio extension .wav
                if (file.endswith(EXTENSION)):
                    #If file is not uploaded yet
                    if (file not in uploadedList): 
                        uploadedList.append(file)
                        storage.child("files/" + file).put(file)
                        print(os.path.join(file))
        except RuntimeError:
            print("Error")
            checkFiles()

checkFiles()
                







