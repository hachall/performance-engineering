#include "Implementation.hpp"
#include <benchmark/benchmark.h>
#include <iostream>
using namespace std;
const int NUM_CENTROIDS = 10000;
const double MIN_LIMIT = -60;
const double MAX_LIMIT = 60;

/*
Benchmarks investigating optimizations of SelectNearestPoint.map()
  function takes in a single Point, and compares to all centroids
  returns id of geometrically closest centroid (and point itself)
*/

/*
  C++ recreation of the method in flink JAVA library
  this is the baseline to optimize against
*/
static void flinkBaseline(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      double distance = point.euclideanDistance(*(centroids[i]));

      if (distance < min_distance) {
        min_distance = distance;
        closest_centroid_id = centroids[i]->getID();
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(flinkBaseline);

/*
  identical functionality to baseline, but uses c++ vector as data structure
*/
static void usingVector(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsVector(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  std::vector<Centroid> centroids = data.getCentroidsVector();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      double distance = point.euclideanDistance(centroids[i]);
      if (distance < min_distance) {
        min_distance = distance;
        closest_centroid_id = centroids[i].getID();
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(usingVector);

/*
  inlining distance calculation function to reduce context switching
*/
static void functionInline(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      Centroid centroid = *(centroids[i]);
      double distance = sqrt((point.x - centroid.x) * (point.x - centroid.x) +
        (point.y - centroid.y) * (point.y - centroid.y));

      if (distance < min_distance) {
        min_distance = distance;
        closest_centroid_id = centroids[i]->getID();
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(functionInline);

/*
  distance is not explicitly used, it is only required for comparisons
  this comparison of points can be achieved identically without using computationally
  expensive sqrt of doubles
*/
static void removeRedundantSQRT(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 + MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      Centroid centroid = *(centroids[i]);
      double distance = (point.x - centroid.x) * (point.x - centroid.x) + (point.y - centroid.y) * (point.y - centroid.y);

      if (distance < min_distance) {
        min_distance = distance;
        closest_centroid_id = centroids[i]->getID();
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(removeRedundantSQRT);

/*
  candidate centroids are automatically infeasible (not closer) if the difference
  in x or y value exceeds the current min_distance, and hence can skip the stage of
  multiplication and sqrt. NB - sqrt is necessary again, as distance is used explicitly
*/
static void skipInfeasibleCandidates(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      Centroid centroid = *(centroids[i]);
      double x_diff = point.x - centroid.x;
      double y_diff = point.y - centroid.y;
      if (x_diff < min_distance && y_diff < min_distance) {
        double distance = sqrt((x_diff) * (x_diff) + (y_diff) * (y_diff));

        if (distance < min_distance) {
          min_distance = distance;
          closest_centroid_id = centroids[i]->getID();
        }
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(skipInfeasibleCandidates);

/*
  alternative distance calculation algorithm that avoids sqrt
  the precision of comparison depends on iterations (passed as args of 1, 2, 3)
*/
static void obscureDistAlgo(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {
    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    for (int i = 0; i < NUM_CENTROIDS ; i++) {
      Centroid centroid = *(centroids[i]);
      double P = point.x - centroid.x;
      double Q = point.y - centroid.y;
      if (P < min_distance && Q < min_distance) {

        double R;
        int i;
        P = fabs(P);
        Q = fabs(Q);
        if (P < Q) {
          R = P;
          P = Q;
          Q = R;
        }

        if (Q != 0.0) {
           // ITER affects the precision (3 iterations for double precision)
          for (i=0 ; i<state.range(0) ; i++) {
            R = Q / P;
            R = R * R;
            R = R / (4.0 + R);
            P = P + 2.0 * R * P;
            Q = Q * R;
          }
        }

        if (P < min_distance) {
          min_distance = P;
          closest_centroid_id = centroids[i]->getID();
        }
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(obscureDistAlgo)->Arg(1)->Arg(2)->Arg(3);

/*
  SIMD processing using 128b SSE vector registers to parallelize distance computation
  sqrt avoided
*/

/*
  v2d union
  holds 2 doubles/128bit SIMD vector overlayed
*/
union v2d {
  double doubles[2];
  __m128d simdVector;
};
static void vectorParallelizationSSE(benchmark::State& state) {
  KMeansData data;
  data.setRandomCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
  Centroid** centroids = data.getCentroidsArray();
  Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
  for(auto _ : state) {

    double min_distance = 2 * MAX_LIMIT;
    int closest_centroid_id = -1;
    const __m128d point_x = _mm_set_pd(point.x, point.x);
    const __m128d point_y = _mm_set_pd(point.y, point.y);

    int i = 0;
    for (; i+2 < NUM_CENTROIDS ; i+=2) {
      __m128d x_values = _mm_set_pd(centroids[i]->x, centroids[i + 1]->x);
      __m128d y_values = _mm_set_pd(centroids[i]->y, centroids[i + 1]->y);

      x_values = _mm_sub_pd(point_x, x_values);
      y_values = _mm_sub_pd(point_y, y_values);

      x_values = _mm_mul_pd(x_values, x_values);
      y_values = _mm_mul_pd(y_values, y_values);

      v2d distances {};
      distances.simdVector = _mm_add_pd(x_values, y_values);

      for (int j = 0 ; j < 2 ; j++) {
        if (distances.doubles[j] < min_distance) {
          min_distance = distances.doubles[j];
          closest_centroid_id = centroids[i+j]->getID();
        }
      }
    }
    // clear up last few
    for ( ; i < NUM_CENTROIDS ; i++) {
      // Centroid centroid = *(centroids[i]);
      double distance = (point.x - centroids[i]->x) * (point.x - centroids[i]->x) + (point.y - centroids[i]->y) * (point.y - centroids[i]->y);

      if (distance < min_distance) {
        min_distance = distance;
        closest_centroid_id = centroids[i]->getID();
      }
    }
    benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
  }
}
BENCHMARK(vectorParallelizationSSE);

/*
  similar parallelization using AVX regsters - double the size (256b)
  works on lab machine (requires -mavx flags), but not LabTS
  v4d union {
  double doubles[4];
  __m256d simdVector;
  }
*/

// static void vectorParallelizationAVX(benchmark::State& state) {
//   Centroid** centroids = getCentroidsArray(NUM_CENTROIDS, MIN_LIMIT, MAX_LIMIT);
//   Point point = getPoint(MIN_LIMIT, MAX_LIMIT);
//   for(auto _ : state) {
//
//     double min_distance = 2 * MAX_LIMIT;
//     int closest_centroid_id = -1;
//     const __m256d point_x = _mm256_setr_pd(point.x, point.x, point.x, point.x);
//     const __m256d point_y = _mm256_setr_pd(point.y, point.y, point.y, point.y);
//
//     int i = 0;
//     for (; i+4 < NUM_CENTROIDS ; i+=4) {
//       __m256d x_values = _mm256_setr_pd(centroids[i]->x, centroids[i + 1]->x, centroids[i + 2]->x, centroids[3]->x);
//       __m256d y_values = _mm256_setr_pd(centroids[i]->y, centroids[i + 1]->y, centroids[i + 2]->y, centroids[3]->y);
//
//       x_values = _mm256_sub_pd(point_x, x_values);
//       y_values = _mm256_sub_pd(point_y, y_values);
//
//       x_values = _mm256_mul_pd(x_values, x_values);
//       y_values = _mm256_mul_pd(y_values, y_values);
//
//       v4d distances {};
//       distances.simdVector = _mm256_add_pd(x_values, y_values);
//
//       for (int j = 0 ; j < 4 ; j++) {
//         if (distances.doubles[j] < min_distance) {
//           min_distance = distances.doubles[j];
//           closest_centroid_id = centroids[i+j]->getID();
//         }
//       }
//     }
//     // clear up last few
//     for ( ; i < NUM_CENTROIDS ; i++) {
//       // Centroid centroid = *(centroids[i]);
//       double distance = (point.x - centroids[i]->x) * (point.x - centroids[i]->x) + (point.y - centroids[i]->y) * (point.y - centroids[i]->y);
//
//       if (distance < min_distance) {
//         min_distance = distance;
//         closest_centroid_id = centroids[i]->getID();
//       }
//     }
//     benchmark::DoNotOptimize(closest_centroid_id); //simulate usage like a return (ensures loop not optimized out)
//   }
// }
// BENCHMARK(vectorParallelizationAVX);

BENCHMARK_MAIN();
