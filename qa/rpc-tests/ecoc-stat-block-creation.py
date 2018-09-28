#!/usr/bin/env python3
# Copyright (c) 2018 The Ecochain Core developers
# Distributed under the GPLv3 software license,
# more info at https://www.gnu.org/licenses/gpl-faq.en.html
# get mean and standard deviation of creation of blocks from debug.log file
# first and only argument is the location of the debug file 

import sys
import numpy as np
import re
import time
import datetime

fn=sys.argv[1]
def get_timestamps():
    data = open(fn, "r")
    creation_time=[]
    stamp=[]
    for line in data:
        if re.search("ACCEPTED", line):
            t=line[0:19]
            creation_time.append(t)
            line_stamp=time.mktime(datetime.datetime.strptime(t, "%Y-%m-%d %H:%M:%S").timetuple())
            stamp.append(line_stamp)
        if re.search("out ", line):
            t=line[0:19]
            creation_time.append(t)
            line_stamp=time.mktime(datetime.datetime.strptime(t, "%Y-%m-%d %H:%M:%S").timetuple())
            stamp.append(line_stamp)
    return stamp

def orphaned():
    orph=0
    data = open(fn, "r")
    for line in data:
        if re.search("orphaned", line):
            orph=orph+1    
    return orph

def extra_slow():
    stamps=get_timestamps()
    diff=[]
    es=0
    delay=300
    
    for c in range(1,len(stamps)):
        d = stamps[c]-stamps[c-1]
        if (d>delay):
            es=es+1
    return es

def average_block_time_creation():
    stamps=get_timestamps()
    diff=[]
    
    for c in range(1,len(stamps)):
        d = stamps[c]-stamps[c-1]
        if (d>0):
            diff.append(d)
    avg = sum(diff)/(len(diff)-1)
    return avg

def st_dev_of_block_time_creation():
    stamps=get_timestamps()
    diff=[]
    
    for c in range(1,len(stamps)):
        d = stamps[c]-stamps[c-1]
        if (d>0):
            diff.append(d)
    varnc = np.std(diff) #np.sqrt(np.var(diff))
    return varnc

orphaned=orphaned()
posb=len(get_timestamps())-1000
extr= extra_slow()
avr_time =average_block_time_creation()
st_dev = st_dev_of_block_time_creation()

print "number of PoS blocks: " +str(posb)
print "orphaned blocks: " +str(orphaned)
print "number of PoS blocks greater then 5 mins: " +str(extr)
print "average creation block time: " +str(avr_time)
print "standard deviation (sigma) of creation block time: "+str(st_dev)
