global units


"""
This file serves to define the unit system 
"""

class BaseUnit():
    """
    Base unit class is used for constructing basis units
    all other units will be a combination of or conversion from base units
    """
    def __init__(self, aliases: list, basis: str) -> None:
        self.aliases = aliases
        self.basis = {basis: 1}
        self.factor = 1         
    
    def __repr__(self):
        return None


class Unit(BaseUnit):
    """
    Serve to construct conversions from base units
    things like feet or inches may be defined by this class referencing a base unit conversion
    """
    def __init__(self, aliases: list, factor: float, parent: BaseUnit) -> None:
        self.aliases = aliases
        self.basis = parent.basis
        self.factor = factor*parent.factor


class CompositeUnit(BaseUnit):
    """
    Composite units are used to represent composites,
    things like velocity or voltage
    """
    def __init__(self, aliases: list, equation: dict, factor = 1) -> None:
        self.aliases = aliases
        self.basis = self.getNewBasis(equation) 
        self.factor = self.getNewFactor(equation)*factor

    def getNewBasis(self, equation: dict):
        newbasis = {}
        for unit, power in equation.items():
            for base, exp in unit.basis.items():
                if base in newbasis:
                    newbasis[base] += exp*power
                else:
                    newbasis[base] = exp*power
        return newbasis

    def getNewFactor(self, equation: dict):
        newFactor= 1
        for unit, power in equation.items():
            newFactor *= unit.factor**power
        return newFactor



class variable():
    """
    The representation of variables used for an equation
    """
    def __init__(self, input:str) -> None:
        self.val, self.basis = self.determineunit(input)

    def determineunit(self, input:str):
        number, unit = input.split(' ')
        if not number.isdigit():
            raise Exception('Input is not a number')

        ## determine unit

        return float(number), unit
    def __mul__(self, other):
        '''
        if isinstance(other, int)
        for unit, power in equation.items():
            for base, exp in unit.basis.items():
                if base in newbasis:
                    newbasis[base]+=exp * power
                else:
                    newbasis[base] = exp * power
                    '''
    def __rmul__(self, other):
        if isinstance(other, int) or isinstance(other, float):
            pass
        #return self.factor*other
        
    
    def __truediv__(self, other):
        #return self.factor/other
        pass

class unknownVarible():
    """
    The representation of unknown variables used to solve equation
    """
    def __init__(self, input:str) -> None:
        self.basis = self.determineunit(input)

    def determineunit(self, input:str):
        number, unit = input.split(' ')
        ## determine unit
        return float(number), unit

    def __mul__(self, other):
        '''
        if isinstance(other, int)
        for unit, power in equation.items():
            for base, exp in unit.basis.items():
                if base in newbasis:
                    newbasis[base]+=exp * power
                else:
                    newbasis[base] = exp * power
                    '''
    def __rmul__(self, other):
        if isinstance(other, int) or isinstance(other, float):
            pass
        #return self.factor*other
        
    
    def __truediv__(self, other):
        #return self.factor/other
        pass
        
def makePrefix(unit, original): #use to generate easy si units like km
    Unit([], 1000, original)
    prefixes = {
        'Peta': 15,
        'Tera': 12,
        'Giga': 9,
        'Mega': 6,
        'kilo': 3,
        'hecto': 2,
        'deka': 1,
        'deci': -1,
        'centi': -2,
        'milli': -3,
        'micro': -6,
        'nano': -9,
        'pico': -12,
        'femto': -15
    }

# a = var(23, meters^-3)

#SI base units
meter = BaseUnit(["m", "meter", "meters"], "length")
kilogram = BaseUnit(["kg", "kilogram", "kilograms"], "mass")
second = BaseUnit(["s", "second", "seconds"], "time")
ampere = BaseUnit(["A", "ampere", "amperes"], "electric current")
kelvin = BaseUnit(["K", "kelvin", "kelvins"], "temperature")
mole = BaseUnit(["mol", "mole", "moles"], "amount of substance")
candela = BaseUnit(["cd", "candela"], "luminous intensity")

#SI composite units
newton = CompositeUnit(["N", "newton", "newtons"], {meter: 1, kilogram: 1, second: -2})
newton_meter = CompositeUnit(["Nm", "newton-meter", "newton-meters", "newton meter", "newton meters"], {newton: 1, meter: 1})
joule = CompositeUnit(["J", "joule", "joules"], {newton: 1, meter: 1})
watt = CompositeUnit(["W", "watt", "watts"], {joule: 1, second: -1})
pascal = CompositeUnit(["Pa", "pascal", "pascals"], {newton: 1, meter: -2})


#imperial "base" units
foot = Unit(["ft", "\'", "foot", "feet"], 0.3048, meter)
slug = Unit(["slug", "slugs"], 14.5939, kilogram)

inch = Unit(["in", "\"", "inch", "inches"], 1/12, foot)


#imperial composite units
pound = CompositeUnit(["lb", "pound", "pounds"], {foot: 1, slug: 1, second: -2})
foot_pound = CompositeUnit(["ft-lb", "ft lb", "foot-pound", "feet-pound", "foot pound", "feet pound"], {pound: 1, foot: 1})
btu = Unit(["BTU", "british thermal unit", "british thermal units"], 1/1055, joule)
horsepower = Unit(["hp", "horsepower"], 745.7, watt)
psi = CompositeUnit(["psi", "pounds per square inch"], {pound: 1, inch: -2})
liter = CompositeUnit(["L", "liter", "Litre"], {meter: 3}, 0.001)


units = [meter, kilogram, second, ampere, kelvin, mole, candela, newton, newton_meter, joule, watt, pascal, foot, inch, slug, pound, foot_pound, btu, horsepower, psi]

for u in units:
    print(u.aliases[-1],"", u.aliases[0],"", u.factor)

