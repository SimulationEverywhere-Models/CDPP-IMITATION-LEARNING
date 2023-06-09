''' Author: Michael W. Floyd '''
''' Generates some artificial inputs for the RoboCart model '''
import random

'''the event file we are generating'''
f = open('robot.ev',"w")
NUM_VALS = 500

for ii in range(NUM_VALS):
    '''the first input generates a 1 value'''
    in1 = random.randint(0,1)
    '''the second input generates a value between 0 and 20'''
    in2 = random.uniform(0,20)
    
    '''convert into hours/minutes'''
    h = ii/60
    m = (ii)%60
    
    '''This is used as the time of the event'''
    eventTime = str(h/10) + str(h%10) + ":" + str(m/10) + str(m%10) + ":00:000"
    event = " "
    
    '''We only generate one event at once, so we randomly select in1 or in2'''
    which = random.randint(0,1)
    if which == 0 and in1 == 1:
        event += "intt " + str(in1)
    else:
        event += "ins " + str(in2)
    f.write(eventTime + event + "\n")
    
f.close()
    