// @file mcast01t.q
// @brief UTC mcast functions demonstration - basic
// @author weaves
//
// @note

.mcast01t.lib:`$".libs/libqmcast"

0N!("Linkage: about to load"; .mcast01t.lib);

/ Simplest interface, take one (null sym) argument
/ This returns 1j

umcast0:.mcast01t.lib 2:(`q_umcast0;1)

if[.sys.is_arg`exit; exit 0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: "-halt -load help.q -nodo -verbose -quiet"
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:
