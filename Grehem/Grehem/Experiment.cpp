#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "Grem.h"
#include "Experiment.h"

using namespace std;

vector<Point> GeneratePoints(int n, int q, int w, int mode) {
    vector<Point> points;
    points.reserve(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < n; i++) {
        if (mode == 1) {
            double x = dist(gen) * q;
            double y = dist(gen) * w;
            points.emplace_back(x, y);
        }
        else {
            double r = dist(gen);
            if (r < 0.25) {
                points.emplace_back(dist(gen) * q, w);
            }
            else if (r < 0.5) {
                points.emplace_back(dist(gen) * q, 0);
            }
            else if (r < 0.75) {
                points.emplace_back(0, dist(gen) * w);
            }
            else {
                points.emplace_back(q, dist(gen) * w);
            }
        }
    }

    return points;
}


void experiment3_1() {
    const int q = 1000000;
    const int w = 1000000;
    const int step = 10000;
    const int max_n = 1000001;

    string filename_inside = "experiment_3_1_inside.txt";
    ofstream file1(filename_inside);
    string filename_boundary = "experiment_3_1_boundary.txt";
    ofstream file2(filename_boundary);

    file1 << "n\tTA_Quick\tTB_Heap3\n";
    file2 << "n\tA_Quick\tB_Heap3\n";

    for (int n = 1; n <= max_n; n += step) {
        if (n % 100000 == 1) cout << "Inside: n = " << n << endl;

        auto points = GeneratePoints(n, q, w, 1);
        double timeA = Grem::measureTime(points, Grem::QUICK_SORT);
        double timeB = Grem::measureTime(points, Grem::HEAP3_SORT);

        file1 << n << "\t" << timeA << "\t" << timeB << "\n";
    }

    for (int n = 1; n <= max_n; n += step) {
        if (n % 100000 == 1) cout << "Border: n = " << n << endl;

        auto points = GeneratePoints(n, q, w, 2);
        double timeA = Grem::measureTime(points, Grem::QUICK_SORT);
        double timeB = Grem::measureTime(points, Grem::HEAP3_SORT);

        file2 << n << "\t" << timeA << "\t" << timeB << "\n";
    }

    file1.close();
    file2.close();
}

void experiment3_2() {
    const int n = 1000000;
    const int step = 10000;
    const int max_qw = 1000000;

    string filename_inside = "experiment_3_2_inside.txt";
    ofstream file1(filename_inside);
    string filename_boundary = "experiment_3_2_boundary.txt";
    ofstream file2(filename_boundary);

    file1 << "q_w\tA_Quick\tB_Heap3\n";
    file2 << "q_w\tA_Quick\tB_Heap3\n";

    for (int qw = 0; qw <= max_qw; qw += step) {
        if (qw % 100000 == 0) cout << "Inside: q = w = " << qw << endl;

        auto points = GeneratePoints(n, qw, qw, 1);
        double timeA = Grem::measureTime(points, Grem::QUICK_SORT);
        double timeB = Grem::measureTime(points, Grem::HEAP3_SORT);

        file1 << qw << "\t" << timeA << "\t" << timeB << "\n";
    }

    for (int qw = 0; qw <= max_qw; qw += step) {
        if (qw % 100000 == 0) cout << "Border: q = w = " << qw << endl;

        auto points = GeneratePoints(n, qw, qw, 2);
        double timeA = Grem::measureTime(points, Grem::QUICK_SORT);
        double timeB = Grem::measureTime(points, Grem::HEAP3_SORT);

        file2 << qw << "\t" << timeA << "\t" << timeB << "\n";
    }

    file1.close();
    file2.close();
}

void interactiveMode() {
    int n, q, w, mode;

    cout << "Program for comparing algorithms for constructing a convex hull" << endl;
    cout << "Algorithm A: Quicksort" << endl;
    cout << "Algorithm B: 3-Heap Sort" << endl;

    cout << "Enter number of points n: ";
    cin >> n;

    cout << "Enter width of the rectangle q: ";
    cin >> q;

    cout << "Enter height of the rectangle w: ";
    cin >> w;

    cout << "Select the point placement mode( 1 - inside the rectangle, 2 - on the border of the rectangle): ";
    cin >> mode;

    if (n <= 0 || q <= 0 || w <= 0 || (mode != 1 && mode != 2)) {
        cout << "Error: Invalid input data!" << endl;
        return;
    }

    auto points = GeneratePoints(n, q, w, mode);

    cout << "Algorithm A: ";
    cout << Grem::measureTime(points, Grem::QUICK_SORT) << endl;

    cout << "Algorithm B: ";
    cout << Grem::measureTime(points, Grem::HEAP3_SORT) << endl;

}

void manualConvexHull() {
    cout << "Manual entry of points for convex hull" << endl;
    cout << "Algorithm A: Quicksort" << endl;
    cout << "Algorithm B: 3-Heap Sort" << endl;
    cout << endl;

    int n;
    cout << "Enter number of points: ";
    cin >> n;
    vector<Point> points;
    points.reserve(n);

    cout << "Enter coordinates of points (x y):" << endl;
    for (int i = 0; i < n; i++) {
        double x, y;
        cout << "Point " << (i + 1) << ": ";
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    cout << endl;
    cout << "Algorithm A: Quicksort" << endl;
    vector<Point> pointsCopyA = points;
    Grem gremA(pointsCopyA);

    vector<Point> hullA = gremA.compute(Grem::QUICK_SORT);

    if (!hullA.empty()) {
        cout << "Vertices of convex hull algorithm A:" << endl;
        for (size_t i = 0; i < hullA.size(); i++) {
            cout << "  " << (i + 1) << ". " << hullA[i] << endl;
        }
    }
    cout << endl;

    cout << "Algorithm B: 3-Heap Sort" << endl;
    vector<Point> pointsCopyB = points;
    Grem gremB(pointsCopyB);

    vector<Point> hullB = gremB.compute(Grem::HEAP3_SORT);

    if (!hullB.empty()) {
        cout << "Vertices of convex hull algorithm B:" << endl;
        for (size_t i = 0; i < hullB.size(); i++) {
            cout << "  " << (i + 1) << ". " << hullB[i] << endl;
        }
    }
    cout << endl;
}