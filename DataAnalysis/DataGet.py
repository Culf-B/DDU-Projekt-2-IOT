import json
from os import path

PATH_TO_HERE = path.dirname(path.abspath(__file__))
FILE_PATH = path.join(PATH_TO_HERE, "Dictionary.json")

def RefineData():
    for key, values in NPKdict.items():
        NPKdict[key] = [round(value, 2) for value in values]

def ReadData():
    global NPKdict
    with open(FILE_PATH, "r", encoding = "utf-8") as load_NPKdict:
        NPKdict = json.load(load_NPKdict)

    print("Keys and Values:")
    for key, value in NPKdict.items():
	    print(f"{key}: {value}")

def SaveData():
    json_object = json.dumps(NPKdict)
    with open(FILE_PATH, "w", encoding = "utf-8") as save_data:
        save_data.write(json_object)

ReadData()