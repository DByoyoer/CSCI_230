s = "dogs do not spot hot pots or cats"
print(len(s))
d = {}
i = 0
for c in s:
    d[c]= True

for c in d:
    d[c] = s.count(c)

print(d)