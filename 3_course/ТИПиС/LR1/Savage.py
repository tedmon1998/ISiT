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

y1 = max([x11, x21, x31])
y2 = max([x12, x22, x32])
y3 = max([x13, x23, x33])

r11 = y1 - x11
r12 = y2 - x12
r13 = y3 - x13

r21 = y1 - x21
r22 = y2 - x22
r23 = y3 - x23

r31 = y1 - x31
r32 = y2 - x32
r33 = y3 - x33

X1 = max(r11, r12, r13)
X2 = max(r21, r22, r23)
X3 = max(r31, r32, r33)

Y1 = min([x11, x12, x13])
Y2 = min([x21, x22, x23])
Y3 = min([x31, x32, x33])

print("Итог")
printTable(th=["", "НС", "СС", "ВС", "fмм", "ΔS"],
           td=[
    "X1", x11, x12, x13, Y1, X1,
    "X2", x21, x22, x23, Y2, X2,
    "X3", x31, x32, x33, Y3, X3])
print(max(X1, X2, X3))
