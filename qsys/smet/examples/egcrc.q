// weaves

/ CRC checks

/ Using my q script loader
.sys.qloader enlist("regex.q")

.crc.i.str["ab"]
.crc.i.str["ab"]
.crc.i.str["ab1"]

.crc.str2str["this that those them"]
.crc.str2str["This That Those Them"]
.crc.str2str["THIS THAT THOSE THEM"]
.crc.str2str["THIS THAT THOSE THEN"]

if[.sys.is_arg`exit; exit 0]

/  Local Variables: 
/  mode:q 
/  q-prog-args: " -p 1445 -halt -debug -nodo -verbose -quiet -load ports.lst super0.q "
/  fill-column: 75
/  comment-column:50
/  comment-start: "/  "
/  comment-end: ""
/  End:



