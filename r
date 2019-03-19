here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
here
room 1 id 0
room 0 id 1
room 2 id 2
room 3 id 3
room 4 id 4
room 5 id 5
room 6 id 6
room 7 id 7
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 0 done 0 include 
0
stop
clone
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 1 done 0 include 
0
6
stop
clone
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 2 done 0 include 
0
6
5
stop
clone
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 3 done 0 include 
0
6
5
3
stop
clone
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 4 done 0 include 
0
6
5
3
4
stop
clone
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 5 done 0 include 
0
6
5
3
4
7
stop
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 6 done 0 include 
0
6
5
3
4
7
2
stop
$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$
way length 7 done 1 include 
0
6
5
3
4
7
2
1
stop
first way done
5
##start
1 23 3
##end
0 9 5
2 16 7
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
0-4
0-6
1-3
4-3
5-2
3-5
4-2
2-1
7-6
7-2
7-4
6-5

L1-3 L2-2 
L1-4 L3-3 L2-7 L4-2 
L1-0 L3-4 L5-3 L2-6 L4-7 
L3-0 L5-4 L2-0 L4-6 
L5-0 L4-0 

Lines: 5
Process:         lem-in [59390]
Path:            /Users/ybuhai/Documents/new/lem-in
Load Address:    0x106084000
Identifier:      lem-in
Version:         ???
Code Type:       X86-64
Parent Process:  bash [34334]

Date/Time:       2019-03-19 13:14:26.957 +0200
Launch Time:     2019-03-19 13:14:26.761 +0200
OS Version:      Mac OS X 10.13.3 (17D47)
Report Version:  7
Analysis Tool:   /Applications/Xcode.app/Contents/Developer/usr/bin/leaks
Analysis Tool Version:  Xcode 9.2 (9C40b)
----

leaks Report Version:  2.0
Process 59390: 288 nodes malloced for 16 KB
Process 59390: 20 leaks for 640 total leaked bytes.
Leak: 0x7fe0b0402860  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000001 0x00000000 0x00000001 	................
	0xb0403210 0x00007fe0 0x00000000 0x00000000 	.2@.............
Leak: 0x7fe0b0403210  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000004 0x00000000 0x00000000 	................
	0x00000000 0x00000000 0x00000000 0x00000000 	................
Leak: 0x7fe0b0403230  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000001 0x00000000 0x00000002 	................
	0xb0403250 0x00007fe0 0x00000000 0x00000000 	P2@.............
Leak: 0x7fe0b0403250  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000006 0x00000000 0x00000000 	................
	0xb0403270 0x00007fe0 0x00000000 0x00000000 	p2@.............
Leak: 0x7fe0b0403270  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000007 0x00000000 0x00000000 	................
	0x00000000 0x00000000 0x00000000 0x00000000 	................
Leak: 0x7fe0b0403290  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000001 0x00000000 0x00000003 	................
	0xb04032b0 0x00007fe0 0x00000000 0x00000000 	.2@.............
Leak: 0x7fe0b04032b0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000006 0x00000000 0x00000000 	................
	0xb04032d0 0x00007fe0 0x00000000 0x00000000 	.2@.............
Leak: 0x7fe0b04032d0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000005 0x00000000 0x00000000 	................
	0xb04032f0 0x00007fe0 0x00000000 0x00000000 	.2@.............
Leak: 0x7fe0b04032f0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000002 0x00000000 0x00000000 	................
	0x00000000 0x00000000 0x00000000 0x00000000 	................
Leak: 0x7fe0b0403310  size=32  zone: DefaultMallocZone_0x106090000
	0x00000001 0x00000001 0x00000000 0x00000004 	................
	0xb0403330 0x00007fe0 0x00000000 0x00000000 	03@.............
Leak: 0x7fe0b0403330  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000006 0x00000000 0x00000000 	................
	0xb0403350 0x00007fe0 0x00000000 0x00000000 	P3@.............
Leak: 0x7fe0b0403350  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000005 0x00000000 0x00000000 	................
	0xb0403370 0x00007fe0 0x00000000 0x00000000 	p3@.............
Leak: 0x7fe0b0403370  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000003 0x00000000 0x00000000 	................
	0xb0403390 0x00007fe0 0x00000000 0x00000000 	.3@.............
Leak: 0x7fe0b0403390  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000000 0x00000000 0x00000000 	................
	0x00000000 0x00000000 0x00000000 0x00000000 	................
Leak: 0x7fe0b04033b0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000001 0x00000000 0x00000005 	................
	0xb04033d0 0x00007fe0 0x00000000 0x00000000 	.3@.............
Leak: 0x7fe0b04033d0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000006 0x00000000 0x00000000 	................
	0xb04033f0 0x00007fe0 0x00000000 0x00000000 	.3@.............
Leak: 0x7fe0b04033f0  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000005 0x00000000 0x00000000 	................
	0xb0403410 0x00007fe0 0x00000000 0x00000000 	.4@.............
Leak: 0x7fe0b0403410  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000003 0x00000000 0x00000000 	................
	0xb0403430 0x00007fe0 0x00000000 0x00000000 	04@.............
Leak: 0x7fe0b0403430  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000004 0x00000000 0x00000000 	................
	0xb0403450 0x00007fe0 0x00000000 0x00000000 	P4@.............
Leak: 0x7fe0b0403450  size=32  zone: DefaultMallocZone_0x106090000
	0x00000000 0x00000002 0x00000000 0x00000000 	................
	0x00000000 0x00000000 0x00000000 0x00000000 	................
