// @file mcast01t.q
// @brief UTC mcast functions demonstration - basic
// @author weaves
//
// @note

.mcast01t.lib:`$".libs/libqmcast"

0N!("Linkage: about to load"; .mcast01t.lib);

/ Take a string for the Multicast network and a port number.

mcsetup:.mcast01t.lib 2:(`q_mc_setup;2)
mcsend:.mcast01t.lib 2:(`q_mc_send;1)

mcsetup["224.1.1.2";6001h]

// To connect to the Python server.
nw0: "239.255.255.250"
port0: 1910h
mcsetup[nw0;port0]
mcsend["working"]

\sleep 1

if[.sys.is_arg`exit; exit 0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: "-halt -load help.q -nodo -verbose -quiet"
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:
