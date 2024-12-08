import re

input = open("input.txt", "r").read()

def part1():
    result = 0
    matches = re.findall(r"mul\(\d+,\d+\)", input) # ['mul(2,4)', 'mul(5,5)', 'mul(11,8)', 'mul(8,5)']

    for match in matches:
        pair = match.removeprefix("mul(").removesuffix(")").split(",")
        result += int(pair[0]) * int(pair[1])
    
    print("Solution Part 1: ", result)

def part2():
    result = 0
    matches = re.findall(r"mul\(\d+,\d+\)|don't\(\)|do\(\)", input) # ['mul(2,4)', "don't()", 'mul(5,5)', 'mul(11,8)', 'do()', 'mul(8,5)']

    do = True

    for match in matches:
        if match == "don't()":
            do = False
            continue;
        elif match == "do()":
            do = True
            continue;
        if do:
            pair = match.removeprefix("mul(").removesuffix(")").split(",")
            result += int(pair[0]) * int(pair[1])
    
    print("Solution Part 2: ", result)

part1()
part2()