#ifndef INCLUDE_UTILS_HPP
#define INCLUDE_UTILS_HPP

#include <algorithm>
#include <cmath>

template <typename T>
class rectangle {
public:
    rectangle() : x{0}, y{0}, width{0}, height{0} { }
    rectangle(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {    }

    T area() const {
        return width * height;
    }

    T x, y, width, height;
};

template<typename T>
rectangle<T>& operator&=(rectangle<T>& lhs, const rectangle<T>& rhs)
{
    T left_x = std::max(lhs.x - lhs.width/2, rhs.x - rhs.width/2);
    T left_y = std::max(lhs.y - lhs.height/2, rhs.y - rhs.height/2);
    T right_x = std::min(lhs.x + lhs.width/2, rhs.x + rhs.width/2);
    T right_y = std::min(lhs.y + lhs.height/2, rhs.y + rhs.height/2);
    
    T width = right_x - left_x;
    T height = right_y - left_y;
    if(width  <= 0 || height <= 0) {
        lhs = rectangle<T>();
        return lhs;
    }

    lhs.x = (right_x + left_x)/2;
    lhs.y = (right_y + left_y)/2;
    lhs.width = width;
    lhs.height = height;
    return lhs;
}

template<typename T>
rectangle<T> operator&(const rectangle<T>& lhs, const rectangle<T>& rhs) {
    rectangle<T> temp = lhs;
    return temp &= rhs;
}

template <typename T>
class rotated_rectangle {
public:
    rotated_rectangle() : x{0}, y{0}, width{0}, height{0}, angle{0} { }
    rotated_rectangle(T x, T y, T width, T height, T angle) 
    : x(x), y(y), width(width), height(height), angle(angle) {    }
    rotated_rectangle(const rectangle<T>& rect) {
       *this = rect;
    }

    rotated_rectangle operator=(const rectangle<T>& rect) {
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
        angle = T();
    }  

    T area() const {
        return width * height;
    }

    rectangle<T> bounding_rect() const {
        rectangle<T> rect;
        rect.height = width * std::sin(angle) + height * std::cos(angle);
        rect.width = width * std::cos(angle) + height * std::sin(angle);
        rect.x = x;
        rect.y = y;
        return rect;
    }

    T x, y, width, height, angle;
};

template<typename T>
rotated_rectangle<T>& operator&=(rotated_rectangle<T>& lhs, const rotated_rectangle<T>& rhs)
{
    rectangle<T> intersection = lhs.bounding_rect() & rhs.bounding_rect();
    lhs = intersection;
    return lhs;
}

template<typename T>
rotated_rectangle<T> operator&(const rotated_rectangle<T>& lhs, const rotated_rectangle<T>& rhs)
{
    rotated_rectangle<T> temp = lhs;
    return temp &= rhs;
}

template <typename T> inline constexpr
int signum(T x, std::false_type is_signed) {
    return T(0) < x;
}

template <typename T> inline constexpr
int signum(T x, std::true_type is_signed) {
    return (T(0) < x) - (x < T(0));
}

template <typename T> inline constexpr
int signum(T x) {
    return signum(x, std::is_signed<T>());
}

#endif /* INCLUDE_UTILS_HPP */