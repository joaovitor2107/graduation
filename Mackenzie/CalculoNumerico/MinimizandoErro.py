def Error(sum:int) -> int:
    return abs((E-sum)/E)


n = int(input())
E = (n*(n+1))/2

e = 0.15
s = 0
i = 1
while Error(s) > e:
    s += i
    i += 1

print(s)
print(Error(s))
print(i)
