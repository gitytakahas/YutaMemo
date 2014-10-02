from ROOT import TFile, gDirectory
import math, shelve

base_dir = '/afs/cern.ch/work/y/ytakahas/StatInt/CMSSW_5_2_5/src/setups/std-bin-by-bin/mt/unc-sm-'
#base_dir = '/afs/cern.ch/work/y/ytakahas/StatInt/CMSSW_5_2_5/src/setups/std-bin-by-bin/mt/unc-sm-'

num_index = {'00':'muTau_0jet_low',
             '01':'muTau_0jet_high',
             '02':'muTau_boost_low',
             '03':'muTau_boost_high',
             '05':'muTau_vbf'}

filelist = ['/data/ytakahas/htt_mt.input_7TeV.root',
            '/data/ytakahas/htt_mt.input_8TeV.root']

energy_index = ['7','8']

fit_result = shelve.open('/data/ytakahas/MLfit_shelve')
table = fit_result['result']

dict_7TeV = {}
dict_8TeV = {}
tes = {}

mass = '125'


for index, category in num_index.items():

    #    print index, category

    _dict_7TeV = {}
    _dict_8TeV = {}
    _tes_ = {}

    for ie, ienergy in enumerate(energy_index):

        Myroot = TFile(filelist[ie])     

        filename = base_dir + ienergy + "TeV-" + index + '.vals'
        file = open(filename, 'r')

        ocounter = 0

        for line in file:
            if(line.startswith('#')): continue
        
            val = line.split()
            if(len(val)!=4): continue
            
            if(val[0] != category):
                print "[ERROR] different categories : ", val[2], category
                continue


            Myroot.cd(category)

            # val : [category, affected_process, nuisance_name, value]

            # Take Association from the fit

            flag = False
            counter = 0
            _fit_cent_ = 0
            _fit_err_ = 0
            _bbb_ = -1


            if(val[2]=='r'): continue
            if('ZLL' in val[2]): continue

            h_up = 0
            h_down = 0
            uncertainty = 0
            
            if('_bin_' in val[2]):
                _process_ = val[2].split('_')[5]
                hname = _process_ + '_' + val[2]
                _bin_ = int(val[2].split('_')[7])
                _bbb_ = _bin_

                h_center = gDirectory.Get(_process_)
                h_up = gDirectory.Get(hname + 'Up')
                h_down = gDirectory.Get(hname + 'Down')

                if(h_up==0 or h_down==0 or h_center==0):
                    print 'Histogram not filled ! continued'
                    continue
                    
                dev = (h_up.GetBinContent(_bin_) - h_down.GetBinContent(_bin_))/2
                if(h_center.GetBinContent(_bin_)!=0):
                    uncertainty = dev/h_center.GetBinContent(_bin_)

            for table_key, table_val in sorted(table.items()):
                if(table_key=='r'): continue

                # table_key : CMS_htt_mt_03_8TeV_W_bin_7
                # table_val : ['0.00 0.99', '-0.37 0.96 -0.37 0.97', '-0.33 0.96 -0.33 0.97', '+0.02']

                if(table_key != val[2]):
                    continue
                elif(table_key == val[2]):
                    flag = True
                    counter += 1
                    _fit_cent_ = table_val[2].split(' ')[0]
                    _fit_err_ = table_val[2].split(' ')[1]

            if(flag==False): continue

            if(counter>1):
                print "Same results twice", val[0], val[2]
                continue
            
            sf = math.fabs(1-float(val[3]))
            affected = val[1].replace('signal','VH,ggH,qqH')
            __tes_dict__ = {}

            if('scale_t_' in val[2]):
                
                _process_ = affected.split(',')

                for iprocess in _process_:
                    if(iprocess=='VH' or iprocess=='ggH' or iprocess=='qqH'):
                        iprocess = iprocess + mass
                    hname = iprocess + '_' + val[2]

                    h_center = gDirectory.Get(iprocess)
                    h_up = gDirectory.Get(hname + 'Up')
                    h_down = gDirectory.Get(hname + 'Down')

                    if(h_up==0 or h_down==0 or h_center==0):
                        print 'Histogram not filled ! continued'
                        continue

                    list_bin = [0 for ii in range(h_center.GetXaxis().GetNbins())]
                    
                    for ibin in range(h_center.GetXaxis().GetNbins()):

                        bin_err = 0
                        dev = (h_up.GetBinContent(ibin) - h_down.GetBinContent(ibin))/2
                        if(h_center.GetBinContent(ibin)!=0):
                            bin_err = dev/h_center.GetBinContent(ibin)
                        list_bin[ibin-1] = bin_err

                    __tes_dict__[iprocess] = list_bin

                if(ienergy=='7'):
                    _tes_['7TeV'] = __tes_dict__
                elif(ienergy=='8'):
                    _tes_['8TeV'] = __tes_dict__

        

            if('_bin_' in val[2]):
                sf = math.fabs(uncertainty)
                                
            _dic_ = {'process':affected,
                     'orig_sys':float(sf),
                     'fit_cent':_fit_cent_,
                     'fit_err':_fit_err_,
                     'flag':False,
                     'bbb':_bbb_
                     }
        
            if(ienergy=='7'):
                if(_dict_7TeV.has_key(val[2])):
                    name = val[2] + '_num' + str(ocounter)
                    _dict_7TeV[name] = _dic_
                    ocounter = ocounter+1
                else:
                    _dict_7TeV[val[2]] = _dic_
               
            elif(ienergy=='8'):
                if(_dict_8TeV.has_key(val[2])):
                    name = val[2] + '_num' + str(ocounter)
                    _dict_8TeV[name] = _dic_
                    ocounter = ocounter+1
                else:
                    _dict_8TeV[val[2]] = _dic_

                
        

        if(ienergy=='7'): dict_7TeV[category] = _dict_7TeV
        elif(ienergy=='8'): dict_8TeV[category] = _dict_8TeV
        file.close()

    tes[category] = _tes_



for key, val in sorted(tes.items()):
    for ikey, ival in sorted(val.items()):
        for iikey, iival in sorted(ival.items()):
            pass
#            print 'category, energy, process = ', key, ikey, iikey, iival
        

save = shelve.open("/data/ytakahas/plot_shelve")
save['nuisance_7TeV'] = dict_7TeV
save['nuisance_8TeV'] = dict_8TeV
save['tau_energy_scale'] = tes
save.close()

#print 'Example : ', dict_7TeV['muTau_vbf']['CMS_htt_zttNorm_7TeV']['fit_cent']
