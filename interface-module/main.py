import json
from prettytable import PrettyTable


def output(data):
    input_json = json.loads(data)
    table = PrettyTable()
    max_length = 0
    for i in input_json.keys():
        if len(input_json[i]) > max_length:
            max_length = len(input_json[i])
    for i in input_json.keys():
        if len(input_json[i]) < max_length:
            while len(input_json[i]) != max_length:
                input_json[i].append("-")
    for i in input_json.keys():
        table.add_column(i, input_json[i])
    print(table)
