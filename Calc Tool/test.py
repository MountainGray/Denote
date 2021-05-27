
from units import *
zig= Unit(['hi', 'test'], 0.1234567890, watt)
units.append(zig)

for u in units:
    print(u.aliases[-1],"", u.aliases[0],"", u.factor)