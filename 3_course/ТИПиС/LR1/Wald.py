from prettytable import PrettyTable


def printTable(td, th):

    columns = len(th)
    table = PrettyTable(th)

    while td:
        table.add_row(td[:columns])
        td = td[columns:]

    print(table)


x11 = 100
x12 = 100
x13 = 100

x21 = 70
x22 = 120
x23 = 120

x31 = -20
x32 = 30
x33 = 200

print("Дано:")
printTable(th=["", "НС", "СС", "ВС"],
           td=[
    "X1", x11, x12, x13,
    "X2", x21, x22, x23,
    "X3", x31, x32, x33])

W1 = min([x11, x12, x13])
W2 = min([x21, x22, x23])
W3 = min([x31, x32, x33])


print("Итог")
printTable(th=["", "НС", "СС", "ВС", "fмм"],
           td=[
    "X1", x11, x12, x13, W1,
    "X2", x21, x22, x23, W2,
    "X3", x31, x32, x33, W3])
print(max(W1, W2, W3))
