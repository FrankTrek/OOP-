
2
x V 1.0
y V 2.0
5
a = ASSIGN b = a * y
c = ASSIGN d = c * x
res = d * 3
EVAL res 0
EVAL x 0
EVAL y 0
3
yo V -0.3072
w V -2.8278
eu C 0.0000
4
a = sin yo
a = ASSIGN w yo
yo = eu * a
k = ASSIGN w yo 
3
EVAL k 
0.0000
EVAL eu
0.0000
EVAL a
(-0.3072)

5
w C -4.8937
ny V -7.4334
dy P
fnp V 1.6042
ha P
5
o = PRINT ha
fnp = ASSERT fnp o
bou = PRINT dy
v =ny + fnp
v = ASSERT ny w
2
EVAL v 
(-4.8937)
EVAL fnp 1 ha 3.78
(3.78)


4
q P
ov V 0.8483
rxo V 10.0000
gd P
5
k = ov * rxo
g = ASSIGN ov k
x = gd + ov
r = PRINT x
lam = g + ov
3
EVAL r 1 gd 3.14
(3.9884)
EVAL lam 
(9.3313)
EVAL r 1 gd 3.14
(11.623)


自动求导
Tensor计算图
Session
4
x V 1
y V 1
a C 3 
b C 2 
3
k1 = a * x
k2 = b * y
k = k1 + k2
12
APPLY NEW SESSION
SETCONST x 2
SETCONST y 3
EVAL k
SETANSWER x 4
APPLY NEW SESSION
SETCONST x 1
SETCONST y 0
EVAL k
SWTICH TO SESSION 1
EVAL k
SHOW SESSION


4
x V 1
y V 1
a C 3 
b C 2 
3
k1 = a * x
k2 = b * y
k = k1 + k2
11
APPLY NEW SESSION THROUGH FILE NAMED FILE1.txt
EVAL k
//17
SETANSWER x 2
APPLY NEW SESSION THROUGH FILE NAMED FILE2.txt
EVAL k
//2
SETCONST x 1
SETCONST y 0
EVAL k
//3
SWTICH TO SESSION 1
EVAL k
//59
SHOW SESSION
//17 4


4
x V 1
y V 1
a C 3 
b C 2 
5
dummy = ASSIGN x y
k1 = a * x
k2 = b * y
k = k1 + k2
res = BING k dummy
14
APPLY NEW SESSION THROUGH FILE NAMED FILE1.txt
EVAL res
//17
EVAL res
//20
APPLY NEW SESSION THROUGH FILE NAMED FILE2.txt
EVAL res
//2
EVAL k
//5
SETCONST x 1
SETCONST y 0
EVAL k
//3
SWTICH TO SESSION 1
EVAL res
//20
EVAL k
//20
SHOW SESSION
//4.4
FILE OUT OUT1.txt
//4 4

2
x V 0
a V 0
k C 3
4
temp = x * k
in = ASSIGN a temp ;
temp = k * in 
res = temp + a
APPLY NEW SESSION THROUGH FILE NAMED FILE3.txt
FILE IN x 1
EVAL res
//9
EVAL in
//3
DELETE SESSION
SHOW SESSION
DELETE SESSION
