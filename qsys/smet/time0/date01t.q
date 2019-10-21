// @file date01t.q
// @brief UTC time functions demonstration - basic
// @author weaves
//
// @note

.time0.i.lib:`$".libs/libqtime"

0N!("Linkage: about to load"; .time0.i.lib);

.sys.qloader enlist "time0.q"

// This is a challenge for week number. It is either the last week of the year before or the
// the first week of this year.
dt0: 2000.01.01T08:11:23.4560
dt0

dt1: .time0.parts @ dt0

x0: .date0.strftime[dt1;0;"%x - %I:%M%p %V %u"]
x0

fmt0: "ISO week number: %V ; other week number: %U ; day-of-week: %u; day-of-year: %j: year: %y"

x0: .date0.strftime[dt1;0;fmt0]
x0

dt00: `date$dt0

x0: .date0.xparts[dt00;0]
x0

x0: .date0.xparts[dt00;1]
x0

x0: .date0.xparts[dt00;2]
x0

x0: .date0.xparts[dt00;3]
x0

x0: .date0.xparts[dt00;4]
x0

x0: .date0.xparts[dt00;5]
x0

dt0: 2000.01.01T08:11:23.4560
dt0

raze ( .date0.parts @ `date$dt0 ; .time0.parts @ `time$dt0 )

dt1: .datetime0.parts @ dt0

x0: .date0.strftime[dt1;0;"%x - %I:%M%p %V %u"]
x0

// returns a string
x1:.date0.strftime[dt1;0;"%u"]
x1

// list-wise
dts:(2001.01.01 2002.02.02 2003.03.03)
x1: .date0.xparts[dts;1]
x1

.date0.seq[]

.date0.seq[]

.date0.seq 6

.date0.seq 10

if[.sys.is_arg`exit; exit 0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: "-halt -load help.q -nodo -verbose -quiet"
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:
