
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
