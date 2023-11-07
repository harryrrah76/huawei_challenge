file = open("route.txt", "r").readlines()[1:]

planets = {}
for i in range(len(file)):
    line = file[i].split()
    planet = str(line[0])
    time = line[1]
    previous_planet = str(file[i-1].split()[0])
    planets[planet] = {}

for i in range(len(file)):
    line = file[i].split()
    planet = str(line[0])
    time = line[1]
    previous_planet = str(file[i-1].split()[0])
    planets[planet][previous_planet]= {
            "day" : 0,
            "night" : 0
        }

for i in range(len(file)):
    line = file[i].split()
    planet = str(line[0])
    time = line[1]
    previous_planet = str(file[i-1].split()[0])
    if time=="DAY":
        planets[planet][previous_planet]["day"] += 1
    elif time=="NIGHT":
        planets[planet][previous_planet]["night"] += 1

print(len(planets))

print(planets)