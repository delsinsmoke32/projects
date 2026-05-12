filename = "ex3_input.txt"

with open(filename) as f:
    arr = []
    while True:
        line = list(f.readline().strip())
        popped = False
        if not line:
            break
        t1 = (max(line), line.index(max(line)))
        if t1[1] > 0 and t1[1] < len(line) - 1:
            popped = True
            i = 0
            while (i < t1[1]):
                line.pop(0)
                i += 1
        line.remove(t1[0])
        if popped:
            t2 = (max(line), line.index(max(line)) + t1[1])
        else:
            t2 = (max(line), line.index(max(line)))
        if t1[1] <= t2[1]:
            arr.append(int(t1[0] + t2[0]))
        else:
            arr.append(int(t2[0] + t1[0]))
    
    print(sum(arr))