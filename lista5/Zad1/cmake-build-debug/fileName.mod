param n, integer, >= 2;
/* number of nodes */
set V, default {..(n-1)};
/* set of nodes */
set E, within V cross V;
/* set of arcs */
param a{(i,j) in E}, > 0;
/* a[i,j] is capacity of arc (i,j) */
param s, symbolic, in V, default 0;
/* source node */
param t, symbolic, in V, != s, default (n-1);
/* sink node */
var x{(i,j) in E}, >= 0, <= a[i,j];
/* x[i,j] is elementary flow through arc (i,j) to be found */
var flow, >= 0;
/* total flow from s to t */
s.t. node{i in V}:
/* node[i] is conservation constraint for node i */
    sum{(j,i) in E} x[j,i] + (if i = s then flow)
    /* summary flow into node i through all ingoing arcs */
    = /* must be equal to */
    sum{(i,j) in E} x[i,j] + (if i = t then flow);
    /* summary flow from node i through all outgoing arcs */
maximize obj: flow;
/* objective is to maximize the total flow through the network */
solve;
printf Maximum flow from node %s to node %s is %g\n\n, s, t, flow;
data;
param n := 9;
param : E :   a :=
          0 1   2
          0 2   8
          0 4   4
          1 3   2
          1 5   4
          2 3   2
          2 6   1
          3 7   4
          4 5   2
          4 6   4
          5 7   2
          6 7   2
end;
