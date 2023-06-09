''' Author: Michael W. Floyd '''
''' Parses the recorded observations '''
f_in = open('observer.txt',"r")
f_out = open('robotCases.txt','w')

max1 = 0
max2 = 0
max3 = 0
max4 = 0
min1 = 9999
min2 = 9999
min3 = 9999
min4 = 9999

'''we use dictionaries to hash inputs, actions and times'''
d_in = dict()
d_ac = dict()
d_time = dict()

'''Read through each observation and parse it'''
for line in f_in:
    '''the observations are table delimited'''
    items = line.split("\t")
    time = items[0]
    in1 = items[1]
    in2 = items[2]
    in3 = items[3]
    in4 = items[4]
    out1 = items[5]
    out2 = items[6]
    out3 = items[7]
    
    '''I just use 9999 because it is easier to deal with'''
    if in1 == "-1.79769e+308":
        in1 = "9999"
    if in2 == "-1.79769e+308":
        in2 = "9999"
    if in3 == "-1.79769e+308":
        in3 = "9999"
    if in4 == "-1.79769e+308":
        in4 = "9999"
    
    '''save the biggest and smallest values we have seen'''
    if float(in1) < min1:
        min1 = float(in1)
    if float(in1) > max1 and float(in1) != 9999:
        max1 = float(in1)
        
    if float(in2) < min2:
        min2 = float(in2)
    if float(in2) > max2 and float(in2) != 9999:
        max2 = float(in2)

    if float(in3) < min3:
        min3 = float(in3)
    if float(in3) > max3 and float(in3) != 9999:
        max3 = float(in3)

    if float(in4) < min4:
        min4 = float(in4)
    if float(in4) > max4 and float(in4) != 9999:
        max4 = float(in4)
        
    '''converiting hours:mins to mins'''
    times = time.split(":")
    minnum = 60*int(times[0]) + int(times[1])
    '''how many ms since the last event or actions'''
    msnum = 1000*int(times[2]) + int(times[3])
    
    '''perform the parsing'''
    if minnum in d_in:
        lasttime = d_time[minnum]
        tdiff = msnum - lasttime
        val = d_ac[minnum]

        if out1 != "-1.79769e+308":
	    val += ":1^" + out1 + "^" + str(tdiff)
	elif out2 != "-1.79769e+308":
            val += ":2^" + out2 + "^" + str(tdiff)
	elif out3 != "-1.79769e+308":
            val += ":3^" + out3 + "^" + str(tdiff)
	else:
	    print "Problem! No valid action!!"

        d_ac[minnum] = val
        d_time[minnum] = msnum
    else:
        d_in[minnum] = in1 + "," + in2 + "," + in3 + "," + in4
        if out1 != "-1.79769e+308":
	    d_ac[minnum] = "1^" + out1 + "^" + str(msnum)
	elif out2 != "-1.79769e+308":
            d_ac[minnum] = "2^" + out2 + "^" + str(msnum)
	elif out3 != "-1.79769e+308":
            d_ac[minnum] = "3^" + out3 + "^" + str(msnum)
	else:
	    print "Problem! No valid action!!"

        d_time[minnum] = msnum
        
'''the first line contains the normalization factors for each feature'''
if min1 == max1 or max1 < min1:
    n_in1 = 1
else:
    n_in1 = max1 - min1
if min2 == max2 or max2 < min2:
    n_in2 = 1
else:
    n_in2 = max2 - min2
if min3 == max3 or max3 < min3:
    n_in3 = 1
else:
    n_in3 = max3 - min3
if min4 == max4 or max4 < min4:
    n_in4 = 1
else:
    n_in4 = max4 - min4

f_out.write(str(n_in1) + "," + str(n_in2) + "," + str(n_in3) + "," + str(n_in4) + "\n")        

'''now all of the cases'''
for key in d_in:
    f_out.write(d_in[key] + ',' + str(d_ac[key]) + "\n")
    
f_in.close()
f_out.close()
