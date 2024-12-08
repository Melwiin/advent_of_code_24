data = open("input.txt", "r")

safe_levels = []

def isSafe(level, error) -> bool:
    safe = False
    last_diff = level[0] - level[1];

    for i in range(1, len(level)):
        diff = level[i - 1] - level[i];
        
        if 1 <= abs(diff) <= 3 and (last_diff * diff) > 0 :
            safe = True
        else:
            if (error == 1): 
                safe = False;
                break
            
            safe =  (   isSafe(level[:i - 1] + level[i:] , error + 1)
                    or  isSafe(level[:i] + level[i + 1:], error + 1) 
                    or  isSafe(level[:i+1] + level[i + 2:], error + 1))
            break
        
        last_diff = level[i - 1] - level[i];
    return safe
    
for line in data:
    level = list(map(int, line.split()))
    
    if isSafe(level, 0):
        safe_levels.append(level)
    else:
        continue;

print(safe_levels)




