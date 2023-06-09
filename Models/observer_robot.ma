[top]
components : obs@Observer rob@robot
out : out
in : intt
in : ins

link : intt in1_in@obs
link : ins in2_in@obs
link : in1_out@obs intt@rob
link : in2_out@obs ins@rob
link : out1@rob out1_in@obs
link : out1_out@obs out

[rob]
preparation : 00:00:00:020
turn : 00:00:01:500
backward : 00:00:01:000


