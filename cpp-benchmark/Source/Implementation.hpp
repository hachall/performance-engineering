#include <functional>
#include <cmath>
#include <memory>
#include <optional>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <nmmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

/*------------------------------------------------------------------------------*/

/*
  Point class
  a simple 2 dimensional point (x,y) with simple functionality to calculate euclidean
  distance to another Point
*/
class Point {
  private:

  public:
  /*co-ordinates x & y - public for testing accessibility*/
  double x, y;

  /*  Constructor
      initializes x & y
  */
  Point(double x, double y): x(x), y(y) {};

  /*  euclideanDistance(Point other)
      calculates euclidean distance to another point
      - returns distance
  */
  double euclideanDistance(Point other);

  /*  toString()
      string parsing of point visualization
  */
  std::string toString() {return std::to_string(x) + " " + std::to_string(y);}
};

/*------------------------------------------------------------------------------*/

/*
  Centroid class
  a simple 2 dimensional point (x,y) with simple functionality to calculate euclidean
  distance to another Point
*/
class Centroid : public Point {
  private:
    /*  id
        centroids are identified by id
        NB - only relevant for benchmarking in emulating true data stucture of
        flink centroid
    */
    int id;

  public:
    /*  Constructor
        initializes id, x & y
    */
    Centroid(int id, double x, double y): Point(x, y), id(id) {};

    /*  getID()
        returns id
    */
    int getID() {return id;};

};

/*------------------------------------------------------------------------------*/

/*
  KMeansData class
  class responsible for initializing and offering (random) data of different forms
*/
class KMeansData {
  /*  num_data_points
      number of data points for a dataset. KMeansData set can store an array and
      vector representation
  */
  int num_arr_points = 0;
  int num_vec_points = 0;

  /*  centroids
      array of centroid pointers
  */
  Centroid** centroids;

  /*  centroids_vec
      standard library vector of centroids
  */
  std::vector<Centroid> centroids_vec = {};

  public:
  /*  Constructor
      set num_data_points attributes (optional)
  */
  KMeansData() {};
  // KMeansData(int num_data_points): num_data_points(num_data_points) {};

  /*  setRandomCentroidsArray()
      internal function allocates num_centroids amount of Centroid objects on
      heap, with random coordinates between min-max. Pointers to Centroids stored
      in centroids
  */
  void setRandomCentroidsArray(int num_centroids, double min, double max, bool verbose = false);

  /*  setRandomCentroidsVector()
      internal function creates num_centroids amount of Cantroids, with random
      coordinates between min-max. Centroids pushed in centroids_vec
  */
  void setRandomCentroidsVector(int num_centroids, double min, double max, bool verbose = false);

  /*  getCentroidsArray()
      getter function for centroids. Returns pointer to first Centroid pointer
      on heap
  */
  Centroid** getCentroidsArray() {return centroids;};

  /*  getCentroidsVector()
      getter function for centroids_vec. Returns Centroid vector
  */
  std::vector<Centroid> getCentroidsVector() {return centroids_vec;};

  /*  getArrayLength()/getVectorLength()
      getter function for dataset lengths
  */
  int getArrayLength() {return num_arr_points;};
  int getVectorLength() {return num_vec_points;};

  ~KMeansData();
};

/*------------------------------------------------------------------------------*/

/*
  Helper Functions for Benchmark.cpp
*/

/*  randNum()
    returns random double betwee min & max
*/
double randNum(double min, double max);

/*  getPoint()
  initializes a point with random x/y coordinates between min/max
*/
Point getPoint(double min, double max, bool verbose = false);
