#include "Implementation.hpp"

/*------------------------------------------------------------------------------*/
/* Point */
double Point::euclideanDistance(Point other) {
  return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
};

/*------------------------------------------------------------------------------*/
/* KMeansData */
void KMeansData::setRandomCentroidsArray(int num_centroids, double min, double max, bool verbose) {
  num_arr_points = num_centroids;
  std::srand(std::time(NULL));
  centroids = new Centroid*[num_centroids + 1];
  int i;
  for (i = 0 ; i < num_centroids ; i++) {
    Centroid* centroid = new Centroid(i, randNum(min, max), randNum(min, max));
    centroids[i] = centroid;
  }
  centroids[i] = nullptr;
  if (verbose) {
    std::cout << "Centroids: " << "\n";
    for (int i = 0 ; i < num_centroids ; i++) {
      std::cout << centroids[i]->toString() << std::endl;
    }
  }
};

void KMeansData::setRandomCentroidsVector(int num_centroids, double min, double max, bool verbose) {
  num_vec_points = num_centroids;
  std::srand(std::time(NULL));
  for (int i = 0 ; i < num_centroids ; i++) {
    Centroid centroid(i, randNum(min, max), randNum(min, max));
    centroids_vec.push_back(centroid);

  }
  if (verbose) {
    std::cout << "Centroids: " << "\n";
    for (int i = 0 ; i < num_centroids ; i++) {
      std::cout << centroids[i]->toString() << std::endl;
    }
  }
};

KMeansData::~KMeansData() {
  if (num_arr_points > 0) {
    for (int i = 0 ; i < num_arr_points ; i++) { //deallocate centroids array
      delete centroids[i];
    }
    delete [] centroids;
  }
};

/*------------------------------------------------------------------------------*/
/* Helper Functions */
// Centroid** getCentroidsArray(int num_centroids, double min, double max, bool verbose) {
//   KMeansData dataFactory(num_centroids);
//   dataFactory.setRandomCentroidsArray(num_centroids, min, max);
//   if (verbose) {
//     std::cout << "Centroids: " << "\n";
//     for (int i = 0 ; i < num_centroids ; i++) {
//       std::cout << dataFactory.getCentroidsArray()[i]->toString() << std::endl;
//     }
//   }
//   return dataFactory.getCentroidsArray();
// }
//
// std::vector<Centroid> getCentroidsVector(int num_centroids, double min, double max, bool verbose) {
//   KMeansData dataFactory(num_centroids);
//   dataFactory.setRandomCentroidsVector(num_centroids, min, max);
//   if (verbose) {
//     std::cout << "Centroids: " << "\n";
//     for (int i = 0 ; i < num_centroids ; i++) {
//       std::cout << dataFactory.getCentroidsVector()[i].toString() << std::endl;
//     }
//   }
//   return dataFactory.getCentroidsVector();
// }

Point getPoint(double min, double max, bool verbose) {
  Point p(randNum(min, max), randNum(min, max));
  if (verbose) {
    std::cout << "Point: " << std::endl << p.toString() << std::endl;
  }
  return p;
}

double randNum(double min, double max) {
  double n = (double) rand() / RAND_MAX;
  return min + n * (max - min);
};
