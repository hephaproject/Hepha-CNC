#include <iostream>
#include <cmath>

using namespace std;

float offset = 0.2;

void set_offset(float ox) { offset = ox; }

struct point {

    float x;
    float y;
    float z;

    point() : x(0), y(0), z(0) {}

    point(float xp, float yp, float zp) : x(xp), y(yp), z(zp) {}

    float x_val() { return x; };

    float y_val() { return y; };

    float z_val() { return z; };

    float z_val() const { return z; };

    float x_val() const { return z; };

    float y_val() const { return z; };

    void x_set(float xp) { x = xp; }

    void y_set(float yp) { y = yp; }

    void z_set(float zp) { z = zp; }

    point &operator=(const point &p2);


};

point &point::operator=(const point &p2) {
    if (&p2 != this) {
        this->z_set(p2.z_val());
        this->y_set(p2.y_val());
        this->x_set(p2.x_val());
    }
    return *this;
}

struct bungle {

    float fi;

    bungle() : fi(0) {}

    bungle(float fix) : fi(fix) {}

    float fi_val() { return fi; };

    float fi_val() const { return fi; };

    void fi_set(float fix) { fi = fix; }

    bungle &operator=(const bungle &a);

};

bungle &bungle::operator=(const bungle &a) {
    if (&a != this) {
        (this->fi_set(a.fi_val()));
    }
    return *this;
}

struct SEG {
    point norm;
    point s;
    bungle f;

    SEG(point sx, bungle fx) : s(sx), f(fx) {}
};

struct line {

    point norm;
    point s1;
    point s2;
    bungle f;

    line(point sx1, point sx2, point normx, bungle fx) : s1(sx1), s2(sx2), norm(normx), f(fx) {}

    line &operator=(const line &l2);
};

line &line::operator=(const line &l2) {
    if (&l2 != this) {
        (this->s1) = l2.s1;
        (this->s2) = l2.s2;
        (this->norm) = l2.norm;
        (this->f) = l2.f;
    }
    return *this;
}

bool is_two_lines(line l1, line l2) {

    if (l1.f.fi_val() == 0 && l2.f.fi_val() == 0)
        return true;
    else
        return false;
}

bool is_intersection_two_lines(line l1, line l2) {

    float a1 = (l1.s2.y_val() - l1.s1.y_val()) / (l1.s2.x_val() - l1.s1.x_val());
    float a2 = (l2.s2.y_val() - l2.s1.y_val()) / (l2.s2.x_val() - l2.s1.x_val());

    if (a1 != a2)
        return true;
    else
        return false;
}

bool is_TIP(line l1, line l2) {

    float x1 = l1.s1.x_val(), x2 = l1.s2.x_val(), x3 = l2.s1.x_val(), x4 = l2.s2.x_val();
    float y1 = l1.s1.y_val(), y2 = l1.s2.y_val(), y3 = l2.s1.y_val(), y4 = l2.s2.y_val();

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;

    // Get the x and y
    float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    // Check if the x and y coordinates are within both lines
    if (x < min(x1, x2) || x > max(x1, x2) ||
        x < min(x3, x4) || x > max(x3, x4))
        return false;
    if (y < min(y1, y2) || y > max(y1, y2) ||
        y < min(y3, y4) || y > max(y3, y4))
        return false;

    return true;
}

bool is_PFIP(line l1, line l2) {

    float x1 = l1.s1.x_val(), x2 = l1.s2.x_val(), x3 = l2.s1.x_val(), x4 = l2.s2.x_val();
    float y1 = l1.s1.y_val(), y2 = l1.s2.y_val(), y3 = l2.s1.y_val(), y4 = l2.s2.y_val();

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;

    // Get the x and y
    float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    if (x < min(x1, x2) || x > max(x1, x2) ||
        x < min(x3, x4) || x > max(x3, x4))
        return true;
    if (y < min(y1, y2) || y > max(y1, y2) ||
        y < min(y3, y4) || y > max(y3, y4))
        return true;
}

point do_TIP_point(line l1, line l2) {

    float x1 = l1.s1.x_val(), x2 = l1.s2.x_val(), x3 = l2.s1.x_val(), x4 = l2.s2.x_val();
    float y1 = l1.s1.y_val(), y2 = l1.s2.y_val(), y3 = l2.s1.y_val(), y4 = l2.s2.y_val();

    float d = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));


    float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    point n_point(x, y, l1.s2.z_val());

    return n_point;

}

point do_PFIP_point(line l1, line l2) {

    float x1 = l1.s1.x_val(), x2 = l1.s2.x_val(), x3 = l2.s1.x_val(), x4 = l2.s2.x_val();
    float y1 = l1.s1.y_val(), y2 = l1.s2.y_val(), y3 = l2.s1.y_val(), y4 = l2.s2.y_val();

    float d = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));


    float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

    point n_point(x, y, l1.s2.z_val());

    return n_point;

}

line do_offset(line l1, float off) {

    point n1(l1.s1.x_val() + l1.norm.x_val() * off, l1.s1.y_val() + l1.norm.y_val() * off, l1.s1.z_val());
    point n2(l1.s2.x_val() + l1.norm.x_val() * off, l1.s2.y_val() + l1.norm.y_val() * off, l1.s2.z_val());
    point nor(l1.norm.x_val(), l1.norm.y_val(), l1.norm.z_val());
    bungle bu(l1.f.fi_val());

    line l_off(n1, n2, nor, bu);

    return l_off;
}

line add_point_to_line_TIP(line l1, point p1, int i) {

    if (i == 1) {
        point n1(p1.x_val(), p1.y_val(), p1.z_val());
        point n2(l1.s2.x_val(), l1.s2.y_val(), l1.s2.z_val());
        point nor(l1.norm.x_val(), l1.norm.y_val(), l1.norm.z_val());
        bungle bu(l1.f.fi_val());

        line l_off(n1, n2, nor, bu);
        return l_off;
    } else if (i == 2) {
        point n2(p1.x_val(), p1.y_val(), p1.z_val());
        point n1(l1.s1.x_val(), l1.s1.y_val(), l1.s1.z_val());
        point nor(l1.norm.x_val(), l1.norm.y_val(), l1.norm.z_val());
        bungle bu(l1.f.fi_val());

        line l_off(n1, n2, nor, bu);
        return l_off;
    } else {
        point n1(l1.s1.x_val(), l1.s1.y_val(), l1.s1.z_val());
        point n2(l1.s2.x_val(), l1.s2.y_val(), l1.s2.z_val());
        point nor(l1.norm.x_val(), l1.norm.y_val(), l1.norm.z_val());
        bungle bu(l1.f.fi_val());
        line l_off(n1, n2, nor, bu);
        return l_off;

    }


}

void do_all() {

    point p1(0.0, 0.0, 0.0);
    point p2(1.0, 0.0, 0.0);
    point p3(1.0, 1.0, 0.0);
    point p4(1.0, 2.0, 0.0);
    point norm(0.0, 1.0, 0.0);
    point norm2(-1.0, 0.0, 0.0);
    bungle f1(0.0);
    line l1(p1, p2, norm, f1);
    line l2(p3, p4, norm2, f1);

    // line-line
    if (is_two_lines(l1, l2)) {
        // case 1
        if (is_intersection_two_lines(l1, l2) && is_TIP(l1, l2)) {

            line l3 = do_offset(l1, offset);
            line l4 = do_offset(l2, offset);

            point p7 = do_TIP_point(do_offset(l1, offset), do_offset(l2, offset));

            line l5 = add_point_to_line_TIP(l3, p7, 2);
            line l6 = add_point_to_line_TIP(l4, p7, 1);
            cout << "a_1_case1" << endl;
        }
        // case
        if (is_intersection_two_lines(l1, l2) && is_PFIP(l1, l2)) {

            line l3 = do_offset(l1, offset);
            line l4 = do_offset(l2, offset);

            point p7 = do_PFIP_point(do_offset(l1, offset), do_offset(l2, offset));

            line l5 = add_point_to_line_TIP(l3, p7, 2);
            line l6 = add_point_to_line_TIP(l4, p7, 1);

            cout << "a_1_case2a" << endl;
        }


    }

}

int main() {


    do_all();


    return 0;
}