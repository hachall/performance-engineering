# Performance Engineering
1)Vtune \
Applying Vtune hotspot analysis reveals a critical code section mapping points to
their nearest centroid – this requires looping through the whole centroid dataset
(in SelectNearestCenter.map()), and comparing to each using Point.euclideanDistance().
This offers room for optimization, both in the processing of a set of points, and
in the distance calculation. Note, the largest CPU utilization involves moving
data (__memcpy_sse2_unaligned_erms) – but this is system code, outside of our
optimization capacity.

2)Java \
An initial micro-benchmark was gauged by recreating the map functionality in JMH
using stripped down flink classes, and running a random point against 10,000 random
centroids. Already, a couple of improvements can be made to performance, with small
changes to the code: 1) move the distance calculation inline to reduce context
switching, 2) eliminate candidate centroids beyond min_distance in either x/y axis,
to skip expensive distance calculations (multiplication and sqrt()), 3) remove the
redundant and expensive sqrt() altogether and compare squared distance directly;
with performance improvements in respective order. Option 2) has large variance in
effectiveness, potentially the branch prediction is particularly sensitive to the
random location of a point/centroids.

3)C++ \
Google/benchmark confirms rewriting this critical section in lower level code has
potential to shave significant time for the same functionality – even just mimicking
the baseline code. As an experiment, both a C array, and standard template library
vector of Centroid objects were compared – to little significance. However, the
power of inlining the calculation and avoiding the sqrt() function is especially
evident – with the processing of 10,000 centroids many times (>3x typically) faster
than the original Java. As C is compiled rather than interpreted (Java), inlining
can bloat byte code, but has large impacts on runtime speed.

Further potential:\
-An array of centroids can’t be loaded directly, due to the ids also being in contiguous
memory (array of structs) – if restructured, and centroid id inferred by loop number,
this would increase points in a cache line, and speed up loading registers.

Note: in some LabTS instances Java’s JIT compiler produces superior performance,
(it can query the exact structure of the running machine and optimize specifically)

4)Pushing the boundaries of performance \
  i)  John Bentley, in Programming Pearls, Confessions of a Coder, devised a crafty way
      of calculating the distance between 2 points, while avoiding a dreaded sqrt() call.
      This was recreated in obscureDistAlgo– note at double precision it is actually
      (not always) faster than the baseline! Probably not enough to justify the loss in
      accuracy – especially, as we can just avoid the sqrt() altogether.

  ii) The centroids loop was successfully unrolled, so the squared distance between
      the point and 2 centroids could be calculated simultaneously, using 128b SSE
      registers. This exhibits the largest performance increase of all the benchmarks,
      but not as much as might be hoped. This is probably in the final stage of
      transferring the doubles to normal registers for the min_distance comparison.
      (Note, parallelization was also achieved on a lab machine using AVX registers
      comparing 4 doubles, giving further performance increase)
