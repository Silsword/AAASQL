import json
from prettytable import PrettyTable


def output(data):
    input_json = json.loads(data)
    table = PrettyTable()
    for i in input_json.keys():
        table.add_column(i, input_json[i])
    print(table)
