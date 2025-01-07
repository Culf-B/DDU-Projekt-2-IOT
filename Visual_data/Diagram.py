import numpy
import statistics
import math
import matplotlib.pyplot as plt
import json
import serial

SERIAL_PORT = "COM3"  # Skift til den korrekte port for din Arduino
BAUD_RATE = 9600
FILE_PATH = "C:/Users/Privat/OneDrive/Desktop/Repos/ProgRepo/DDU-Projekt-2-IOT/Visual_data/Dictionary.json"

def read_json_from_serial():
    try:
        # Opret forbindelse til den serielle port
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2) as ser:
            print("Venter på data fra Arduino...")
            line = ser.readline().decode('utf-8').strip()  # Læs linje og dekod som UTF-8
            if line:
                print(f"Modtaget data: {line}")
                return json.loads(line)  # Konverter JSON-streng til Python-dictionary
    except Exception as e:
        print(f"Fejl ved seriel kommunikation: {e}")
    return None

def save_json_to_file(data, filepath):
    try:
        with open(filepath, 'w') as file:
            json.dump(data, file, indent = 4)
    except Exception as e:
        print(f"Fejl ved skrivning til fil: {e}")

if __name__ == "__main__":
    json_data = read_json_from_serial()
    if json_data:
        save_json_to_file(json_data, FILE_PATH)

NPKdict = {
    "Nitrogen": [9.12434234, 9.0, 1.38, 5.78, 9.63, 4.87, 3.11, 8.95, 9.52, 3.1, 7.95, 7.89, 6.01, 1.63, 7.55, 5.68, 8.69, 8.17, 5.13, 5.8, 2.14, 8.16, 7.61, 1.03, 3.93, 7.21, 7.22, 3.46, 6.97, 9.53, 5.85, 5.05, 4.27, 9.6, 8.34, 7.31, 8.51, 7.33, 9.38, 6.94, 4.17, 9.25, 2.24, 5.96, 9.28, 8.87, 8.06, 5.7, 3.09, 1.92],
    "Phosphor": [9.2, 6.65, 8.49, 6.62, 1.65, 4.17, 5.93, 5.99, 3.83, 7.19, 1.16, 1.56, 8.27, 3.21, 5.72, 1.35, 3.64, 1.97, 6.86, 8.86, 6.52, 5.59, 6.6, 8.59, 1.1, 3.37, 7.03, 5.14, 1.14, 9.14, 4.35, 4.6, 1.44, 1.9, 2.77, 7.32, 7.97, 3.02, 6.81, 5.56, 5.89, 3.88, 9.31, 8.89, 4.18, 7.84, 9.47, 1.03, 3.65, 6.12],
    "Potassium": [5.95, 1.83, 8.42, 4.82, 7.09, 8.46, 3.15, 8.74, 3.62, 8.98, 3.19, 2.88, 3.82, 7.63, 8.78, 8.27, 1.17, 9.98, 9.24, 7.65, 1.1, 3.77, 9.76, 5.21, 5.29, 1.66, 6.93, 4.08, 5.27, 6.71, 5.46, 7.55, 8.79, 7.4, 8.59, 5.24, 5.54, 4.62, 1.94, 6.45, 5.35, 7.91, 7.67, 2.7, 3.57, 1.56, 3.28, 9.63, 5.17, 5.36]
}

def refineData():
    for key, values in NPKdict.items():
        NPKdict[key] = [round(value, 2) for value in values]

        

def ReadData():
    with open("C:/Users/Privat/OneDrive/Desktop/Repos/ProgRepo/DDU-Projekt-2-IOT/Visual_data/Dictionary.json", "r", encoding = "utf-8") as load_NPKdict:
        NPKdict = json.load(load_NPKdict)

    print("Keys and Values:")
    for key, value in NPKdict.items():
	    print(f"{key}: {value}")

def SaveData():
    json_object = json.dumps(NPKdict)
    with open("C:/Users/Privat/OneDrive/Desktop/Repos/ProgRepo/DDU-Projekt-2-IOT/Visual_data/Dictionary.json", "w", encoding="utf-8") as save_data:
        save_data.write(json_object)

refineData()
SaveData()
ReadData()