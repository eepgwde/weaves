/// @author weaves
/// @brief Test: str2num.
///
/// And other examples.

/// @ is indexing at top-level
/// . is indexing at all levels and d . (x;y) is identical to d[x;y]

d:((1 2 3;4 5 6 7);(8 9;10;11 12);(13 14;15 16 17 18;19 20))
d[1;2]
d . (1;2)

d @ (1;2)

/// Functional forms of amend

/// dyadic - add 42 and 43 to the I'th elements in L
L:100 200 300 400
I:1 2
@[L;I;+;42 43]

/// assigning within a table
t:([] c1:`a`b`c; c2:10 20 30)
@[t;0;:;(`aa;100)]

idx: where t[;`c2] > 20
@[t;idx;:;(`aa;100)]

/// Similarly for dot but indexing is by level.
/// So good for dictionaries and grouped tables.

d:`a`b`c!(100 200;300 400 500;600)
.[d;(`b;1);+;42]

/// enlist can have a functional form: concatenate to an empty list
type x1:enlist 4h
type x0:((),4h)
type x0:((),((),4h))

type x1:(4h, 5h)
type x0:((),((),4h,5h))

/// txf[] has gone.

c:2 3 5 7
p:1 2 3 4
r:10 20 30 40
t:([s;c];p;r)

/ txf[t;(s;c);`p`r]

t[([]s;c);`p`r]             / equivalent without txf

/ txf[t;(`d`a;5 2);`p`r]

t[([]s:`d`a;c:5 2);`p`r]    / equivalent without txf

q:([]s:`d`f`s;c:5 7 3;k:"DFS")

/ select s,k,txf[t;(s;c);`p] from q

select s,k,t[([]s;c);`p] from q    / equivalent without txf

q:([]s:`d`f`s;c:5 7 3;k:"DFS")

/ select s,k,txf[t;(s;c);`p] from q

select s,k,t[([]s;c);`p] from q    / equivalent without txf


x1:2f

s0:"02"

x0: .sch.str2num @ s0

if[ x0 <> x1; .sys.exit[1] ]

s0:enlist "2"
x0: .sch.str2num @ s0
if[ x0 <> x1; .sys.exit[1] ]

s0:enlist "2"
x0: .sch.str2num @ s0
if[ x0 <> x1; .sys.exit[1] ]

x1:0f
s0:enlist "0"
x0: .sch.str2num @ s0
if[ x0 <> x1; .sys.exit[1] ]

x1:0f
s0:""
x0: .sch.str2num @ s0
if[ not null x0; .sys.exit[1] ]

.sys.exit[0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: "-load help.q -nodo -verbose -halt"
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:
