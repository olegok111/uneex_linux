import roman
import sys

MAXNUM = int(sys.argv[-1])

table = []
maxlen = 0
for i in range(1, MAXNUM + 1):
    r = roman.toRoman(i)
    table.append(r)

    if len(r) > maxlen:
        maxlen = len(r)

print("static char[{}] roman_table[] = {{".format(maxlen + 1))
for i, r in enumerate(table):
    if i != len(table) - 1:
        print("    \"{}\",".format(r))
    else:
        print("    \"{}\"".format(r))
print("};")
