#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include "Point.h"

class Grem {
private:
    std::vector<Point> points;
    Point startPoint;

public:
    enum SortMethod {
        QUICK_SORT,
        HEAP3_SORT
    };

    Grem(const std::vector<Point>& inputPoints) : points(inputPoints) {}

    // быстрая сортировка
    void quickSort(std::vector<Point>& points, int left, int right) {
        int tl = left, tr = right;
        if (left >= right) { return; }
        quickSplit(points, tl, tr);
        quickSort(points, left, tr);
        quickSort(points, tl, right);
    }

    void quickSplit(std::vector<Point>& points, int& l, int& r) {
        Point pivot = points[(l + r) / 2];
        while (l <= r) {
            while (points[l] < pivot) {
                l++;
            }
            while (pivot < points[r]) {
                r--;
            }
            if (l <= r) {
                std::swap(points[l++], points[r--]);
            }
        }
    }

    // сортировка 3-кучей
    void heapify(std::vector<Point>& arr, int n, int i) {
        int largest = i;
        int child1 = 3 * i + 1;
        int child2 = 3 * i + 2;
        int child3 = 3 * i + 3;

        if (child1 < n && arr[largest] < arr[child1]) {
            largest = child1;
        }
        if (child2 < n && arr[largest] < arr[child2]) {
            largest = child2;
        }
        if (child3 < n && arr[largest] < arr[child3]) {
            largest = child3;
        }

        // Если наибольший не текущий - меняем и рекурсивно heapify
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heap3Sort(std::vector<Point>& arr) {
        int n = arr.size();

        for (int i = n / 3; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }


    // общие методы
    int findLexMin(const std::vector<Point>& points) const {
        int minIndex = 0;
        for (int i = 1; i < points.size(); i++) {
            if (points[i].getx() < points[minIndex].getx() ||
                (points[i].getx() == points[minIndex].getx() &&
                    points[i].gety() < points[minIndex].gety())) {
                minIndex = i;
            }
        }
        return minIndex;
    }

    std::vector<Point> removeCollinearPoints(std::vector<Point>& points) const {
        std::vector<Point> filtered;
        if (points.empty()) return filtered;

        filtered.push_back(points[0]);

        for (int i = 1; i < points.size(); i++) {
            while (i < points.size() - 1 &&
                points[i].crossProduct(points[i + 1]) == 0) {
                i++;
            }
            filtered.push_back(points[i]);
        }

        return filtered;
    }

    std::vector<Point> buildConvexHull(const std::vector<Point>& filteredPoints) const {
        if (filteredPoints.size() <= 2) return filteredPoints;

        std::vector<Point> hull;
        hull.push_back(filteredPoints[0]);
        hull.push_back(filteredPoints[1]);

        for (int i = 2; i < filteredPoints.size(); i++) {
            while (hull.size() >= 2) {
                Point a = hull[hull.size() - 2];
                Point b = hull[hull.size() - 1];
                Point c = filteredPoints[i];

                Point ab = b - a;
                Point bc = c - b;

                if (ab.crossProduct(bc) <= 1e-9) { // c лежит слева от вектора ab
                    hull.pop_back();
                }
                else {
                    break;
                }
            }
            hull.push_back(filteredPoints[i]);
        }

        return hull;
    }

    // основной метод с выбором сортировки
    std::vector<Point> compute(SortMethod method = QUICK_SORT) {
        if (points.size() <= 2) return points;

        int minIndex = findLexMin(points);
        std::swap(points[0], points[minIndex]);
        startPoint = points[0];

        // сдвигаем координаты
        for (int i = 0; i < points.size(); i++) {
            points[i] = points[i] - startPoint;
        }

        switch (method) {
        case QUICK_SORT:
            quickSort(points, 1, points.size() - 1);
            break;
        case HEAP3_SORT:
            // копия для heap3Sort, так как она работает со всем массивом
            std::vector<Point> heapPoints(points.begin() + 1, points.end());
            heap3Sort(heapPoints);
            for (int i = 0; i < heapPoints.size(); i++) {
                points[i + 1] = heapPoints[i];
            }
            break;
        }

        std::vector<Point> filteredPoints = removeCollinearPoints(points);
        std::vector<Point> hull = buildConvexHull(filteredPoints);

        for (auto& p : hull) {
            p = p + startPoint;
        }

        return hull;
    }
    // измерение времени
    static double measureTime(const std::vector<Point>& points, SortMethod method) {
        std::vector<Point> pointsCopy = points;
        Grem grem(pointsCopy);

        auto start = std::chrono::high_resolution_clock::now();
        grem.compute(method);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }

};