#define CATCH_CONFIG_MAIN
#include "Implementation.hpp"
#include <catch2/catch.hpp>
using namespace std;

TEST_CASE("Points initialize x,y coordinates correctly") {
  Point p(1.34, 11.11);
  REQUIRE(p.x == 1.34);
  REQUIRE(p.y == 11.11);
};

TEST_CASE("Random centroids array set correctly") {
  int test_centroids = 10;
  int min = 0;
  int max = 10;

  KMeansData data;
  data.setRandomCentroidsArray(test_centroids, min, max);
  Centroid** centroids = data.getCentroidsArray();

  REQUIRE(data.getArrayLength() == test_centroids);

  int i;
  int test_min = max/2;
  int test_max = max/2;
  for (i = 0 ; centroids[i] != NULL ; i++) {
    if (centroids[i]->x > test_max) test_max = centroids[i]->x;
    if (centroids[i]->x < test_min) test_min = centroids[i]->x;
    if (centroids[i]->y > test_max) test_max = centroids[i]->y;
    if (centroids[i]->y < test_min) test_min = centroids[i]->y;
  }
  REQUIRE(test_min >= min);
  REQUIRE(test_max <= max);
  REQUIRE(i == test_centroids);
};

TEST_CASE("Random centroids vector set correctly") {
  int test_centroids = 10;
  int min = 0;
  int max = 10;

  KMeansData data;
  data.setRandomCentroidsVector(test_centroids, min, max);
  std::vector<Centroid> centroids = data.getCentroidsVector();

  int size = centroids.size();
  REQUIRE(size == test_centroids);

  int i;
  int test_min = max/2;
  int test_max = max/2;
  for (i = 0 ; i < test_centroids ; i++) {
    if (centroids[i].x > test_max) test_max = centroids[i].x;
    if (centroids[i].x < test_min) test_min = centroids[i].x;
    if (centroids[i].y > test_max) test_max = centroids[i].y;
    if (centroids[i].y < test_min) test_min = centroids[i].y;
  }
  REQUIRE(test_min >= min);
  REQUIRE(test_max <= max);
  REQUIRE(i == test_centroids);
}

TEST_CASE("Computes correct distance between points") {
  Point p1(0.0, 0.0);
  Point p2(3.0, 4.0);
  REQUIRE(p1.euclideanDistance(p2) == 5.0);
}
