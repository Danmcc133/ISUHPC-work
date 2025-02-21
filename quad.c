// Computing info on a quadrilateral ( area, perimeter, inner angles) as quad.h
// main function: input nodes, call quad.area,perimeter,innerangles , print quad
// gcc source code
// update git, submit source code and screenshots
#define _USE_MATH_DEFINES //This is only for pi
#include <math.h>
#include <stdio.h>


double area(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    // This function calculates the area of a quadrilateral using the cross product
    double A = 0.5 * ((x1 * y2 + x2 * y3 + x3 * y4 + x4 * y1) - (x2 * y1 + x3 * y2 + x4 * y3 + x1 * y4));
    return A;
}

double euclidean_distance(double x1, double y1, double x2, double y2) { 
    // This is a function that calculates the distance between two points
    // This will be used to calculate perimeter
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


double inner_angle(double a, double b, double c) {
    // This uses the dot product identity c^2 = a^2 + b^2 - 2ab*cos(theta)
    return acos((a*a + b*b - c*c) / (2 * a * b)) * (180.0 / M_PI);
}

int main() {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    // This allows the user to input their own vertices instead of a preloaded example
    printf("Enter the coordinates of the first vertex (x1 y1): ");
    scanf("%lf %lf", &x1, &y1);
    printf("Enter the coordinates of the second vertex (x2 y2): ");
    scanf("%lf %lf", &x2, &y2);
    printf("Enter the coordinates of the third vertex (x3 y3): ");
    scanf("%lf %lf", &x3, &y3);
    printf("Enter the coordinates of the fourth vertex (x4 y4): ");
    scanf("%lf %lf", &x4, &y4);

    double a = euclidean_distance(x1, y1, x2, y2);
    double b = euclidean_distance(x2, y2, x3, y3);
    double c = euclidean_distance(x3, y3, x4, y4);
    double d = euclidean_distance(x4, y4, x1, y1);
    // These distances are used to calculate the total perimeter

    double perimeter = a + b + c + d;

    double A = area(x1, y1, x2, y2, x3, y3, x4, y4); // This gives us the area

    double angle1 = inner_angle(a, d, euclidean_distance(x1, y1, x3, y3));
    double angle2 = inner_angle(b, a, euclidean_distance(x2, y2, x4, y4));
    double angle3 = inner_angle(c, b, euclidean_distance(x3, y3, x1, y1));
    double angle4 = inner_angle(d, c, euclidean_distance(x4, y4, x2, y2));
    // This gives us each of the inner angles
    
    printf("Perimeter: %.2lf\n", perimeter);
    printf("Area: %.2lf\n", A);
    printf("Inner Angles: %.2lf, %.2lf, %.2lf, %.2lf\n", angle1, angle2, angle3, angle4);

    return 0;
}