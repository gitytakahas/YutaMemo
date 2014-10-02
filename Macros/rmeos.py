# 
# Simple macro to delete cmgTuples from eos to cmscastor
# 


import re, os.path, subprocess, sys, time, ConfigParser, os
from optparse import OptionParser, OptionGroup

origin="/eos/cms/store/cmst3/group/htautau/CMG/"
eos="/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select"

def eosls(dir, dataset, pattern, isdo=False):

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

        count += 1

        if isdo:
            _rmcmd_ = eos + ' rm ' + ('%s/%s' % (dir, file))
            
            print _rmcmd_
            subprocess.call(_rmcmd_, shell=True)


    if not isdo:
        print '[delete]', dataset, '(', count ,')'


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

    f = open(options.list)

    for dir in f:
        raw = dir.rstrip()
        dataset = raw.split()[0]

#        import pdb; pdb.set_trace()
        if dataset.find('#')!=-1:
            continue
        
        eosls(origin + dataset, dataset, re.compile(r".*\.root"), False)

    _ans_ = raw_input('[delete] Can I delete these dataset  ? [y/n] : ')
    
    if _ans_ in ['y','Y','yes']:
        pass
    else:
        sys.exit(1)
                                


    print 'start deleting'

    f = open(options.list)
    for dir in f:

        raw = dir.rstrip()
        dataset = raw.split()[0]
        if dataset.find('#')!=-1:
            continue

        eosls(origin + dataset, dataset, re.compile(r".*\.root"), True)
