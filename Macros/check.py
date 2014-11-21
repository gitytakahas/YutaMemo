
f1 = open('inc_list')
evt1 = []

for line in f1:
    try:
        evt1.append(int(line.split(':')[2]))
    except:
        pass

f1.close()

f2 = open('EventList/f12_signal_tH_YtMinus1.list')
evt2 = []

for line in f2:
    try:
        evt2.append(int(line.split(':')[2]))
    except:
        pass

f2.close()

overlap12 = [evt for evt in evt1 if evt in evt2]
overlap21 = [evt for evt in evt2 if evt in evt1]

noverlap = [evt for evt in evt1 if evt not in evt2]

for a in noverlap:
    print '1:1:' + str(a)

print len(evt1)
print len(evt2)
print len(overlap12)
print len(overlap21)
print 'No-overlaop', len(noverlap)

print 'Armin, Only Armin ', len(evt1), len(evt1) - len(overlap12)
print 'Yuta, Only Yuta ', len(evt2), len(evt2) - len(overlap21)
