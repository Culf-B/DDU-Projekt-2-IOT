import json
import serial
from os import path

SERIAL_PORT = "COM9"  # Skift til den korrekte port for din Arduino
BAUD_RATE = 9600
PATH_TO_HERE = path.dirname(path.abspath(__file__))
FILE_PATH = path.join(PATH_TO_HERE, "Dictionary.json")

def Read_json_from_serial():
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout = 2) as ser:
            print("Venter på data fra Arduino...")
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(f"Modtaget data: {line}")
                return json.loads(line)
    except Exception as e:
        print(f"Fejl ved seriel kommunikation: {e}")
    return None

def Save_json_to_file(data, filepath):
    try:
        with open(filepath, 'w') as file:
            json.dump(data, file, indent = 4)
    except Exception as e:
        print(f"Fejl ved skrivning til fil: {e}")

if __name__ == "__main__":
    global NPKdict
    NPKdict = Read_json_from_serial()
    if NPKdict:
        Save_json_to_file(NPKdict, FILE_PATH)


