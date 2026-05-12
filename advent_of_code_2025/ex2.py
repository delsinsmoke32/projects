#ex 2-2
def check_rec(string):
    if len(string) == 1:
        return False
    flag = True
    prev = string[0]
    for i in range(1, len(string)):
        if string[i] != prev:
            flag = False
            break
        prev = string[i]
    if flag:
        return flag
    flag2 = True
    wind_size = 2
    while (wind_size <= len(string)/2):
        flag2 = True
        if (len(string) % wind_size) != 0:
            wind_size += 1
            continue
        base = string[:wind_size]
        #print(string, base)
        for i in range(wind_size, len(string) + 1 - wind_size, wind_size):
            #print("Qua " + str(i))
            #print(string[i:i+wind_size])
            if string[i:i+wind_size] != base:
                #print("y")
                flag2 = False
                break
            base = string[i:i+wind_size]
        if flag2:
            return flag2
        wind_size += 1
    return False

#ex 2-1
def check_rec_basic(string):
    if (len(string) % 2) != 0:
        return False
    wind_size = int(len(string)/2)
    print(wind_size)
    base = string[:wind_size]
    return string[wind_size:len(string)] == base

filename = "ex2_input.txt"
s = 0
with open(filename) as f:
    ranges = f.readline().strip().split(",")
    for r in ranges:
        total = r.split("-")
        for i in range(int(total[0]), int(total[1]) + 1):
            curr = str(i)
            if check_rec(curr):
                print(i)
                s += i

print(s)
            
