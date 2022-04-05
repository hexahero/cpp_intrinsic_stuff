#include <iostream>

#ifdef __AVX__
  #include <immintrin.h>
#else
  #warning No AVX support.
#endif

class vecAVX256f {

public:

    vecAVX256f(float a, float b, float c, float d, float e, float f, float g, float h);
    vecAVX256f(float a);
    vecAVX256f(const __m256& vecf);

    vecAVX256f operator + (const vecAVX256f& vecf);
    void operator += (const vecAVX256f& vecf);
    vecAVX256f operator * (const vecAVX256f& vecf);
    vecAVX256f operator / (const vecAVX256f& vecf);
    friend std::ostream& operator << (std::ostream& ostr, const vecAVX256f& vecf);
	
	std::string to_string();
    void print();

private:

    __m256 vectorf;

};

vecAVX256f::vecAVX256f(float a, float b, float c, float d, float e, float f, float g, float h) {
        
    vectorf = _mm256_set_ps(h, g, f, e, d, c, b, a);
}

vecAVX256f::vecAVX256f(float a) {
        
    vectorf = _mm256_set1_ps(a);
}

vecAVX256f::vecAVX256f(const __m256& vecf) {

    vectorf = vecf;
}

vecAVX256f vecAVX256f::operator + (const vecAVX256f& vecf) {

    return vecAVX256f(_mm256_add_ps(vectorf, vecf.vectorf));
}

void vecAVX256f::operator += (const vecAVX256f& vecf) {

    vectorf = _mm256_add_ps(vectorf, vecf.vectorf);
}

vecAVX256f vecAVX256f::operator * (const vecAVX256f& vecf) {

    return vecAVX256f(_mm256_mul_ps(vectorf, vecf.vectorf));
}

vecAVX256f vecAVX256f::operator / (const vecAVX256f& vecf) {

    return vecAVX256f(_mm256_div_ps(vectorf, vecf.vectorf));
}

std::ostream& operator << (std::ostream& ostr, const vecAVX256f& vecf) {

    float* vecTemp = reinterpret_cast<float*>(const_cast<__m256*>(&vecf.vectorf));

    for (unsigned int i = 0; i != 8; ++i) {
            
        ostr << vecTemp[i] << '\n';
    }

    return ostr;
}

std::string vecAVX256f::to_string() {

    std::stringstream ostr;

    for (unsigned int i = 0; i != 8; ++i) {

        ostr << vectorf[i] << ' ';
    }
    
    return ostr.str();
}

void vecAVX256f::print() {

    float* vecTemp = reinterpret_cast<float*>(&vectorf);

    for (unsigned int i = 0; i != 8; ++i) {
            
        std::cout << vecTemp[i] << '\n';
    }

}