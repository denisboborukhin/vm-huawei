#pragma once

#include <iostream>
#include <cmath>

namespace complex_num
{

class complex
{
    public:
    double re_ = 0;
    double im_ = 0;

    complex () {}
    complex (double re): re_ {re} {}
    complex (double re, double im): re_ {re}, im_ {im} {}
    complex (const complex& other): re_ {other.re_}, im_ {other.im_} {}

    complex operator+ (const complex& add)  const {return complex (re_ + add.re_, im_ + add.im_);}
    complex operator+ (const double add)    const {return (*this + complex (add));}
    complex operator+ ()                    const {return *this;}

    complex operator- (const complex& sub)  const {return complex (re_ + sub.re_, im_ + sub.im_);}
    complex operator- (const double sub)    const {return (*this - complex (sub));}
    complex operator- ()                    const {return complex (re_, - im_);}
    
    complex operator* (const complex& mul) const 
    {
        return complex (re_ * mul.re_ - im_ * mul.im_, re_ * mul.im_ + im_ * mul.re_);
    }
    complex operator* (const double mul) const {return (*this * complex(mul));}

    complex operator/ (const complex& div) const 
    {
        double denominator = div.im_ * div.im_ + div.re_ * div.re_;
        double real = (re_ * div.re_ + im_ * div.im_) / denominator;
        double img  = (im_ * div.re_ - re_ * div.im_) / denominator;

        return complex (real, img);
    }

    complex& operator=   (const complex& b) 
    {
        re_ = b.re_;
        im_ = b.im_;

        return *this;
    }
    
    bool    operator==  (const complex& b) const {return ((re_ == b.re_) && (im_ == b.im_));}
    bool    operator!=  (const complex& b) const {return !(*this == b);}
    bool    operator<   (const complex& b) const 
    {
        return (re_ * re_ + im_ * im_) < (b.re_ * b.re_ + b.im_ * b.im_);
    }

    bool    operator>   (const complex& b) const 
    {
        return (re_ * re_ + im_ * im_) > (b.re_ * b.re_ + b.im_ * b.im_);
    }

};

}
