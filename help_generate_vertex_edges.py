p =[]
j = raw_input()
while j != '':
        mt = [ord(k) - 97  for k in j.split()]
        print mt
        p.append(mt)
        j = raw_input()

for i in p:
        print '{' , i[0], ',', i[1], '},'
