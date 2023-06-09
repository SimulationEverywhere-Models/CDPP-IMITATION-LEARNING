''' Author: Michael W. Floyd '''
''' Generates some artificial inputs for the RoboArm model '''
import random

'''the event file we are generating'''
f = open('arm.ev',"w")
NUM_VALS = 500

for ii in range(NUM_VALS):
    '''the first input generates a 1000 value (touch)'''
    in1 = random.randint(0,1)
    '''the second input generates a value between 25 and 50 (sound)'''
    in2 = random.uniform(25,50)
    '''the third input generates a a 5 or 15 (color)'''
    in3 = random.randint(0,1)
    if in3 == 0:
	in3 = 5
    else:
        in3 = 15
    
    '''convert into hours/minutes'''
    h = ii/60
    m = (ii)%60
    
    '''This is used as the time of the event'''
    eventTime = str(h/10) + str(h%10) + ":" + str(m/10) + str(m%10) + ":00:000"
    event = " "
    
    '''We only generate one event at once, so we randomly select in1, in2 or in3'''
    which = random.randint(0,2)
    if which == 0 and in1 == 1:
        event += "in1 1000"
    elif which == 1:
        event += "in " + str(in2)
    else:
        event += "in_ls " + str(in3)

    f.write(eventTime + event + "\n")
    
f.close()
    
