import time
from fileManager import readFile, writeFile

def choose_data (select):
    if(select == 0):
        return "1:0:0"
    if(select == 1):
        return "0:1:0"
    if(select == 2):
        return "0:0:1"

select = 0
while(True):    
    time.sleep(2.5)
    data = choose_data(select)
    writeFile("led_status.txt", data)
    print(data)
    select = (select+1)%3
    
