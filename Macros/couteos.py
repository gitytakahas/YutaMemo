# 
# Simple macro to delete cmgTuples from eos to cmscastor
# 


import re, os.path, subprocess, sys, time, ConfigParser, os
from optparse import OptionParser, OptionGroup


origin="/eos/cms/store/cmst3/group/htautau/CMG/"
eos="/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select"

def eosls(dir, dataset, pattern):

    cmdline = eos + ' ls -l ' + dir
    po = subprocess.Popen(cmdline, shell=True, cwd='.',
                          stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, close_fds=True)

    (stdouterr, stdin) = (po.stdout, po.stdin)

    count = 0
    
    while True:
        line = stdouterr.readline()
        if not line: break

        output = line.split()
        if len(output) != 9: 
            print 'unexpected output length', len(output)
            break
#            print output

            
        file = output[8]

	if not re.match(pattern, file): 
            continue

        fcmdline = 'edmFileUtil root://eoscms/' + ('%s/%s' % (dir, file))
#        print fcmdline
            
        fpo = subprocess.Popen(fcmdline, shell=True, cwd='.',
                               stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, close_fds=True)

        (fstdouterr, fstdin) = (fpo.stdout, fpo.stdin)
    
        while True:
            fline = fstdouterr.readline()
            if not fline: break

            if fline.find('events')==-1 or fline.find('lumis')==-1:
                continue

            check = fline.split(' ')[5]
            count = count + int(check)

            print fline, count
            
    print 'Total = ', count




if __name__ == '__main__':
    
    parser = OptionParser(usage='usage: %prog [options] ARGs',
                          description='check consistency betwee castor and eos')

    parser.add_option('-L', '--list', dest='list', default='List.txt', action='store',
                      help='List of dataset to be checked')

    (options, args) = parser.parse_args()
    f = open(options.list)

    print 
    print "[INFO] List of files based on :", options.list
    print 
    print 'start counting'

    f = open(options.list)
    for dir in f:

        raw = dir.rstrip()
        dataset = raw.split()[0]
        if dataset.find('#')!=-1:
            continue

        eosls(origin + dataset, dataset, re.compile(r".*\.root"))
