#include <iostream>

class vec256f {

public:

    vec256f(float a, float b, float c, float d, float e, float f, float g, float h);
    vec256f(float a);

    vec256f operator + (const vec256f& vecf);
    void operator += (const vec256f& vecf);
    vec256f operator * (const vec256f& vecf);
    vec256f operator / (const vec256f& vecf);
    friend std::ostream& operator << (std::ostream& ostr, const vec256f& vecf);

    std::string to_string();
    void print();

private:

    float vectorf[8];

};

vec256f::vec256f(float a, float b, float c, float d, float e, float f, float g, float h) {
    
    vectorf[0] = a;
    vectorf[1] = b;
    vectorf[2] = c;
    vectorf[3] = d;
    vectorf[4] = e;
    vectorf[5] = f;
    vectorf[6] = g;
    vectorf[7] = h;

}

vec256f::vec256f(float a) {
        
    for (int i = 0; i != 8; ++i) vectorf[i] = a;
}

vec256f vec256f::operator + (const vec256f& vecf) {

    return vec256f(

        vectorf[0] + vecf.vectorf[0],
        vectorf[1] + vecf.vectorf[1],
        vectorf[2] + vecf.vectorf[2],
        vectorf[3] + vecf.vectorf[3],
        vectorf[4] + vecf.vectorf[4],
        vectorf[5] + vecf.vectorf[5],
        vectorf[6] + vecf.vectorf[6],
        vectorf[7] + vecf.vectorf[7]

    );
}

void vec256f::operator += (const vec256f& vecf) {

    vectorf[0] += vecf.vectorf[0];
    vectorf[1] += vecf.vectorf[1];
    vectorf[2] += vecf.vectorf[2];
    vectorf[3] += vecf.vectorf[3];
    vectorf[4] += vecf.vectorf[4];
    vectorf[5] += vecf.vectorf[5];
    vectorf[6] += vecf.vectorf[6];
    vectorf[7] += vecf.vectorf[7];

}

vec256f vec256f::operator * (const vec256f& vecf) {


    return vec256f(

        vectorf[0] * vecf.vectorf[0],
        vectorf[1] * vecf.vectorf[1],
        vectorf[2] * vecf.vectorf[2],
        vectorf[3] * vecf.vectorf[3],
        vectorf[4] * vecf.vectorf[4],
        vectorf[5] * vecf.vectorf[5],
        vectorf[6] * vecf.vectorf[6],
        vectorf[7] * vecf.vectorf[7]

    );
}

vec256f vec256f::operator / (const vec256f& vecf) {

    return vec256f(

        vectorf[0] / vecf.vectorf[0],
        vectorf[1] / vecf.vectorf[1],
        vectorf[2] / vecf.vectorf[2],
        vectorf[3] / vecf.vectorf[3],
        vectorf[4] / vecf.vectorf[4],
        vectorf[5] / vecf.vectorf[5],
        vectorf[6] / vecf.vectorf[6],
        vectorf[7] / vecf.vectorf[7]

    );
}

std::ostream& operator << (std::ostream& ostr, const vec256f& vecf) {

    for (unsigned int i = 0; i != 8; ++i) {

        ostr << vecf.vectorf[i] << '\n';
    }
    
    return ostr;
}

std::string vec256f::to_string() {

    std::stringstream ostr;

    for (unsigned int i = 0; i != 8; ++i) {

        ostr << vectorf[i] << ' ';
    }
    
    return ostr.str();
}

void vec256f::print() {

    for (unsigned int i = 0; i != 8; ++i) {
            
        std::cout << vectorf[i] << '\n';
    }

}