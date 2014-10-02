from DataFormats.FWLite import Events, Handle
handle  = Handle ('std::vector<reco::GenParticle>')
label = ("genParticlesPruned")
events = Events('tmpYuta.root')
ntau = 0
nw = 0
ngamma = 0
nother = 0
for ev in events:
    ev.getByLabel(label, handle)
    gps = handle.product()
    gps3 = [p for p in gps if p.status()==3] 
    # print [p.pdgId() for p in gps3]

    for p in gps3:
        if p.pdgId() == 25:
            for i in range(p.numberOfDaughters()):
                # print p.daughter(i).pdgId()
                if i==0 and abs(p.daughter(i).pdgId()) == 15:
                    ntau += 1
                elif i==0 and abs(p.daughter(i).pdgId()) == 24:
                    nw += 1
                elif i==0 and abs(p.daughter(i).pdgId()) == 22:
                    ngamma += 1
                elif i==0 and abs(p.daughter(i).pdgId()) not in (15, 24, 22):
                    nother += 1
                    print p.daughter(i).pdgId()
print 'n tau', ntau, 'n W', nw, 'n other', nother, 'n gamma', ngamma
print 'Ratio', float(ntau)/float(nw)

   # import pdb; pdb.set_trace()
