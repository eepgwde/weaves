// @file time01t.q
// @brief UTC time functions demonstration - basic
// @author weaves
//
// @note

.time0.i.lib:`$".libs/libqtime"

0N!("Linkage: about to load"; .time0.i.lib);

.sys.qloader enlist "time0.q"

/ Simplest interface, take one (null sym) argument
/ This returns 1j

0N!(type .time0.utime0[]; .time0.utime0[]);

x0:.time0.utime1[]
0N!(type x0; ; `int$floor x0; .Q.f[8;] x0 - floor x0 );

dt0: 2000.01.01T00:00:00.000
dt0
x0: .time0.utime2[.time0.parts @ dt0;0]

x1: .time0.utime3 @ `real$x0

dt0: .z.z
dt0

dt1: .time0.parts @ dt0
x0: .time0.utime2[dt1; 0]

" " sv string each (type x0; floor x0; x0 - floor x0)
x1: .time0.utime3 @ x0

if[.sys.is_arg`exit; exit 0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: "-halt -load help.q -nodo -verbose -quiet"
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:
