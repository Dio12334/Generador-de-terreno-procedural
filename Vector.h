#ifndef VECTOR_H
#define VECTOR_H

#include <type_traits>
#include <cmath>
#include <iostream>


namespace Math{
    
	template <typename T>
    struct Vector final{

        static_assert(std::is_arithmetic<T>::value, "T must be arithmetic");
        static_assert(!std::is_const<T>::value, "T must not be const");
        
		T x, y, z;
        
        typedef T component_type;

        Vector(): x(0), y(0), z(0){
            
        }

        explicit Vector(T inX, T inY, T inZ): x(inX), y(inY), z(inZ){

        }

        explicit Vector(T inX, T inY): x(inX), y(inY), z(0){

        }

        template <typename U>
        Vector(const Vector<U>& other): x(other.x), y(other.y), z(other.z){
        
        }

        template <typename U>
        Vector& operator=(const Vector<U>& other){
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        Vector(const Vector&) = default;

        Vector& operator=(const Vector& other) = default;

        Vector(Vector&& other) = default;

        Vector& operator=(Vector&& other) = default;

        ~Vector() = default;
        
        Vector& operator+=(const Vector& other){ 
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        Vector& operator-=(const Vector& other){
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        template <typename U>
        Vector& operator*=(const U& number){
            x *= number;
            y *= number;
            z *= number;
            return *this;
        }

		template <typename U>
        Vector& operator/=(const U& number){
            x /= number;
            y /= number;
            z /= number;
            return *this;
        }

        double length() const {
            return std::sqrt(x*x + y*y + z*z);
        }

        Vector<double> normal() const {
            auto len = (length())? length(): 1;
            return Vector<double>(x/len, y/len, z/len);
        }

        Vector& normalize() {
            auto len = (length())? length(): 1;
            x /= len;
            y /= len;
            z /= len;
            return *this;
        }


    };

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> operator+(const Vector<T>& lv, const Vector<U>& rv){
        Vector<P> result(lv);
        result += rv;
        return result;
    }

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> operator-(const Vector<T>& lv, const Vector<U>& rv){
        Vector<P> result(lv);
        result -= rv;
        return result;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<T>& vec){
        os << vec.x << " " << vec.y << " " << vec.z;
        return os;
    }

    template <typename T, typename U>
    auto dotProduct(const Vector<T>& lv, const Vector<U>& rv) -> decltype(lv.x*rv.x){
        return lv.x * rv.x + lv.y * rv.y + lv.z * rv.z;
    }

	template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
	Vector<P> operator*(const Vector<T>& lv, const Vector<U>& rv){
		return Vector<P>(lv.x*rv.x, lv.y*rv.y, lv.z*rv.z);
	}

    template <typename T, typename U, typename P = typename std::common_type<T, U>::type>
    Vector<P> crossProduct(const Vector<T>& lv, const Vector<U>& rv){
        return Vector<P>(lv.y * rv.z - lv.z * rv.y, lv.z * rv.x - rv.z * lv.x, lv.x * rv.y - lv.y * rv.x);
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator*(const Vector<T>& vec, const U& number){
        Vector<T> result(vec);
        result *= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator*(const U& number, const Vector<T>& vec){
        Vector<T> result(vec);
        result *= number;
        return result;
    }

	template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator/(const Vector<T>& vec, const U& number){
        Vector<T> result(vec);
        result /= number;
        return result;
    }

    template <typename T, typename U, typename = typename std::enable_if_t<std::is_arithmetic<U>::value>>
    Vector<T> operator/(const U& number, const Vector<T>& vec){
        Vector<T> result(vec);
        result /= number;
        return result;
    }
    template <typename T>
    Vector<double> normalize(const Vector<T>& vec){
        return vec.normal();
    }

    template <typename T, typename U>
    bool operator==(const Vector<T>& lv, const Vector<U>& rv){
        return lv.x == rv.x && lv.y == rv.y && lv.z == rv.z;
    }

    template <typename T, typename U>
    bool operator!=(const Vector<T>& lv, const Vector<U>& rv){
        return !(lv == rv);
    }

    template <typename T>
    using Point = Vector<T>;

    struct Plane{
        Vector<double> n;
        double d;
        template <typename U>
        Plane(Point<U> a, Point<U> b, Point<U> c): n(normalize(crossProduct(b - a, c - a))) {
            d = dotProduct(n, a);
        }
    };
}
#endif

