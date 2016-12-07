fact0: { [n] 1*/1 + til n }

// Using a dictionary for memoize
// then this will delete key `a from a dict abc, enlist `a _ abc

// Initialize the memo table 
if[.sys.undef . `.memo`fact0; .memo.fact0: (`long$())!`long$() ]

fact1: { [n] $[null r:.memo.fact0[n]; { r:fact0[x]; .memo.fact0[x]::r; r }[n]; r] }

