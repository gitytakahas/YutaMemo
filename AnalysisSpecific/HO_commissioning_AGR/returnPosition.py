import math

class findEtaPhi:
    
                                          
    def __init__(self):
        print 'Init'

        # Z coordinate
        self.etalow = (0.025,  35.195,  70.625, 106.595, 141.565, 180.765, 220.235, 261.385, 304.525, 349.975, 410.025, 452.085, 506.645, 565.025, 627.725, 660.25)
        self.etahigh = (35.145,  70.575, 106.545, 125.505, 180.715, 220.185, 261.335, 304.475, 349.925, 392.575, 452.035, 506.595, 564.975, 627.675, 661.075, 700.25)
        
        # X 
        # for YB1,2i
        self.philow = (-76.27, -35.11, 0.35, 35.81, 71.77, 108.93)
        self.phihigh = (-35.81, -0.35, 35.11, 71.07, 108.23, 140.49)
        
        # for YB0, L0
        self.philow00 = (-60.27, -32.91, 0.35, 33.61, 67.37, 102.23)
        self.phihigh00 = (-33.61, -0.35, 32.91, 66.67, 101.53, 129.49)
    
        # for YB0, L1
        self.philow01 = (-64.67, -34.91, 0.35, 35.61, 71.37, 108.33)
        self.phihigh01 = (-35.61, -0.35, 34.91, 70.67, 107.63, 138.19)


        self.netabin = 16

        
    def returnXY(self, ieta, iphi, isZ):
        
        abs_eta = abs(ieta)
        ring = -1

        R = 406.6
        
        if abs_eta <= 4:
            ring = 0
        elif abs_eta <= 10:
            ring = 1
        elif abs_eta <= self.netabin:
            ring = 2
        else:
            print 'No valid ieta'
            
        Zlow  = isZ*self.etalow[abs_eta]
        Zhigh = isZ*self.etahigh[abs_eta]

        phi = iphi + 1
        if phi >= 72:
            phi -= 72
        
        phi_sect = phi/6 # should run from 0 - 11
        phi_res = phi%6 # should run from 0 - 5

#        print 'iphi', iphi, 'phi_sector', phi_sect, 'phi_res', phi_res, 'Z', Zlow, Zhigh

        Xlow = -1
        Xhigh = -1
        Ylow = -1
        Yhigh = -1

        if ring > 0:
            Ylow_base = self.philow[phi_res]
            Yhigh_base = self.phihigh[phi_res]

            angle_low = math.asin(Ylow_base/R) + (phi_sect*math.pi/6.)
            angle_high = math.asin(Yhigh_base/R) + (phi_sect*math.pi/6.)

            Xlow = R*math.cos(angle_low)
            Xhigh = R*math.cos(angle_high)

            Ylow = R*math.sin(angle_low)
            Yhigh = R*math.sin(angle_high)

        elif ring == 0:
            Ylow_base = (self.philow00[phi_res] + self.philow01[phi_res])/2.
            Yhigh_base = (self.phihigh00[phi_res] + self.phihigh01[phi_res])/2.

            angle_low = math.asin(Ylow_base/R) + (phi_sect*math.pi/6.)
            angle_high = math.asin(Yhigh_base/R) + (phi_sect*math.pi/6.)

            Xlow = R*math.cos(angle_low)
            Xhigh = R*math.cos(angle_high)

            Ylow = R*math.sin(angle_low)
            Yhigh = R*math.sin(angle_high)

        else:
            print 'Invalid ring ID !'

        return Xlow, Xhigh, Ylow, Yhigh, Zlow, Zhigh

        
#        Xlow = philow[]    philow = (-76.27, -35.11, 0.35, 35.81, 71.77, 108.93)
#    phihigh = (-35.81, -0.35, 35.11, 71.07, 108.23, 140.49)



    
#import config as tool
#test = tool.jetobj
#test. ...
