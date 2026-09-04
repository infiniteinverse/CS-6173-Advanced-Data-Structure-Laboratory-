#include <iostream>

// z = x + iy form
class complex{
    private:
        double real;
        double img;
    
    public:
        complex(double r, double i): real(r), img(i) {}
        complex operator+(const complex& other){
            return complex(real + other.real, img + other.img);
        }
        complex operator-(const complex& other){
            return complex(real - other.real, img - other.img);
        }

        complex operator+(const complex& other){
            return complex(real + other.real, img + other.img);
        }
        complex operator*(const complex& other){
            return complex(real * other.real - img * other.img, real * other.img + img * other.real);
        }
        void display(){
            std::cout << real << " + " << img << "i" << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const complex& c){
            os << c.real << " + " << c.img << "i";
            return os;
        }


};
int main(){
    complex c1(1.0, 2.0);
    complex c2(3.0, 4.0);   
    std::cout << "c1 + c2 " << c1 + c2 << std::endl;

    return EXIT_SUCCESS;
}