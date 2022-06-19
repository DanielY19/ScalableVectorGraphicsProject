#ifndef SCALABLEVECTORGRAPHICSAPPLICATION_POINT_H
#define SCALABLEVECTORGRAPHICSAPPLICATION_POINT_H


class Point {
public:
    Point();

    Point(float x, float y);

    void setX(float x);

    void setY(float y);

    float getX() const;

    float getY() const;

    void print() const;

    void change(float x, float y);

    void translate(float verticalTrl, float horizontalTrl);

    bool operator<(const Point &other) const;

    bool operator>(const Point &other) const;

    bool operator<=(const Point& other) const;

    bool operator>=(const Point &other) const;

private:
    float x;
    float y;
};


#endif //SCALABLEVECTORGRAPHICSAPPLICATION_POINT_H
