#include <iostream>
#include "KPolynomial.h"

using namespace std;

int find_iter(const KPolynomial& poly, const int value) {
    Iterator *it = poly.createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        if (it->current() == value) {
            return it->getIndex();
        }
    }
    return -1;
}

int find_iterv2(const KPolynomial& poly, const int value) {
    for (Iteratorv2 it(poly); it(); ++it) {
        if (*it == value) {
            return it.getIndex();
        }
    }
    return -1;
}

int main() {
    int coeffs1[] = {1, 2, 3};
    KPolynomial poly1(coeffs1, 3);
    cout << "Polynomial 1: " << poly1 << endl;

    KPolynomial poly2 = {4, 5, 6};
    cout << "Polynomial 2: " << poly2 << endl;

    KPolynomial poly3(5);
    cout << "Polynomial 3: " << poly3 << endl;


    cout << "Poly1 + Poly3 = " << poly1 + poly3 << endl;

    poly1 += poly2;
    cout << "Poly1 += poly2: poly1 = " << poly1 << endl;

    cout << "Find with Iterator v1:" << endl;
    cout << "Find 5 in poly3:\n" << find_iter(poly3, 5) << endl;
    cout << "Find 5 in poly2:\n" << find_iter(poly2, 5) << endl;

    cout << "Find with Iterator v2:" << endl;
    cout << "Find 5 in poly3:\n" << find_iterv2(poly3, 5) << endl;
    cout << "Find 5 in poly2:\n" << find_iterv2(poly2, 5) << endl;

    return 0;
}
