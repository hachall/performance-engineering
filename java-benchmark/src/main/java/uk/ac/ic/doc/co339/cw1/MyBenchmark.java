/*
 * Copyright (c) 2014, Oracle America, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *  * Neither the name of Oracle nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

package uk.ac.ic.doc.co339.cw1;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;


import java.io.Serializable;
import java.util.Collection;
import java.util.Random;
import java.util.concurrent.TimeUnit;

public class MyBenchmark {

    //Point & Centroid Classes
    public static class Point implements Serializable {

        public double x, y;

        public Point() {}

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public double euclideanDistance(Point other) {
            return Math.sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
        }

        @Override
        public String toString() {
            return x + " " + y;
        }
    }
    public static class Centroid extends Point {

        public int id;

        public Centroid() {}

        public Centroid(int id, double x, double y) {
            super(x, y);
            this.id = id;
        }

        public Centroid(int id, Point p) {
            super(p.x, p.y);
            this.id = id;
        }

        @Override
        public String toString() {
            return id + " " + super.toString();
        }
    }

    @State(Scope.Thread)
    public static class MyState {

        @Setup(Level.Trial)
        public void doSetup() {
            Random rand = new Random();
            double x = -60 + rand.nextDouble() * 120; //scale to region of centroids
            double y = -60 + rand.nextDouble() * 120;
            //Initialize a random test point (in the range, (0,0) to (60,60))
            test_point = new Point(x, y);
            System.out.println("Test point: " + test_point.toString());
            //Initialize 100 random centroids
            centroids = new KMeansData().getRandomCentroidDataSet(10000);
        }

        public Collection<Centroid> centroids;
        public Point test_point;
    }

    @Benchmark @BenchmarkMode(Mode.AverageTime) @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public void baseFlink_SelectNearestCenterMap(MyState state, Blackhole blackhole) {
        double minDistance = Double.MAX_VALUE;
        int closestCentroidId = -1;

        // check all cluster centers
        for (Centroid centroid : state.centroids) {
            // compute distance
            double distance = state.test_point.euclideanDistance(centroid);

            // update nearest cluster if necessary
            if (distance < minDistance) {
                minDistance = distance;
                closestCentroidId = centroid.id;
            }
        }

        // emit a new record with the center id and the data point.
        blackhole.consume(closestCentroidId);
        blackhole.consume(state.test_point);
    }

    @Benchmark @BenchmarkMode(Mode.AverageTime) @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public void inlineDistanceFunction_SelectNearestCenterMap(MyState state, Blackhole blackhole) {
        double minDistance = Double.MAX_VALUE;
        int closestCentroidId = -1;

        // check all cluster centers
        for (Centroid centroid : state.centroids) {
            // compute distance
            double distance = Math.sqrt((state.test_point.x - centroid.x) * (state.test_point.x - centroid.x) + (state.test_point.y - centroid.y) * (state.test_point.y - centroid.y));

            // update nearest cluster if necessary
            if (distance < minDistance) {
                minDistance = distance;
                closestCentroidId = centroid.id;
            }
        }

        // emit a new record with the center id and the data point.
        blackhole.consume(closestCentroidId);
        blackhole.consume(state.test_point);
    }

    @Benchmark @BenchmarkMode(Mode.AverageTime) @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public void removeUnnecessarySQRT_SelectNearestCenterMap(MyState state, Blackhole blackhole) {
        double minDistance = Double.MAX_VALUE;
        int closestCentroidId = -1;

        // check all cluster centers
        for (Centroid centroid : state.centroids) {
            // compute distance
            double distance = (state.test_point.x - centroid.x) * (state.test_point.x - centroid.x) + (state.test_point.y - centroid.y) * (state.test_point.y - centroid.y);

            // update nearest cluster if necessary
            if (distance < minDistance) {
                minDistance = distance;
                closestCentroidId = centroid.id;
            }
        }

        // emit a new record with the center id and the data point.
        blackhole.consume(closestCentroidId);
        blackhole.consume(state.test_point);
    }

    @Benchmark @BenchmarkMode(Mode.AverageTime) @OutputTimeUnit(TimeUnit.NANOSECONDS)
    public void eliminateCandidatesFromDistanceCalc_SelectNearestCenterMap(MyState state, Blackhole blackhole) {
        double minDistance = Double.MAX_VALUE;
        int closestCentroidId = -1;

        // check all cluster centers
        for (Centroid centroid : state.centroids) {
            // compute distance
            double x_diff = state.test_point.x - centroid.x;
            double y_diff = state.test_point.y - centroid.y;
            //Skip candidate centroids when the x or y difference is greater than the minDistance (to cut down expensive double multiplications)
            if (x_diff < minDistance && y_diff < minDistance) {
                double distance = Math.sqrt((x_diff) * (x_diff) + (y_diff) * (y_diff));
                // update nearest cluster if necessary
                if (distance < minDistance) {
                    minDistance = distance;
                    closestCentroidId = centroid.id;
                }
            }

        }

        // emit a new record with the center id and the data point.
        blackhole.consume(closestCentroidId);
        blackhole.consume(state.test_point);
    }

}
