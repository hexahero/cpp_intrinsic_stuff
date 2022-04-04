#include <iostream>

#define ANKERL_NANOBENCH_IMPLEMENT
#include "../dependencies/nanobench.h"

#ifdef __AVX__
  #include <immintrin.h>
#else
  #warning No AVX support.
#endif

#include "vec256f.hpp"
#include "vecAVX256f.hpp"

vec256f vec1(10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0);
vec256f vec2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

vec256f vec3(2.0);
vec256f vec4(2.0);

vecAVX256f vec5(10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0);
vecAVX256f vec6(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

vecAVX256f vec7(2.0);
vecAVX256f vec8(2.0);

#ifdef TESTS

    #define CATCH_CONFIG_MAIN
    #include"../dependencies/catch.hpp"

    TEST_CASE("Test vec256f add", "[op+]") {

        vec256f addResult = vec1 + vec2;

        REQUIRE(strcmp(addResult.to_string().c_str(), "11 22 33 44 55 66 77 88 ") == 0);

        addResult = vec3 + vec4;

        REQUIRE(strcmp(addResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }
    
    TEST_CASE("Test vec256f addeq", "[op+=]") {

        vec256f addeqResult = vec1;
        addeqResult += vec2;

        REQUIRE(strcmp(addeqResult.to_string().c_str(), "11 22 33 44 55 66 77 88 ") == 0);

        addeqResult = vec3;
        addeqResult += vec4;

        REQUIRE(strcmp(addeqResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }   

    TEST_CASE("Test vec256f mul", "[op*]") {

        vec256f mulResult = vec1 * vec2;

        REQUIRE(strcmp(mulResult.to_string().c_str(), "10 40 90 160 250 360 490 640 ") == 0);

        mulResult = vec3 * vec4;

        REQUIRE(strcmp(mulResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }   

    TEST_CASE("Test vec256f div", "[op/]") {

        vec256f divResult = vec1 / vec2;

        REQUIRE(strcmp(divResult.to_string().c_str(), "10 10 10 10 10 10 10 10 ") == 0);

        divResult = vec3 / vec4;

        REQUIRE(strcmp(divResult.to_string().c_str(), "1 1 1 1 1 1 1 1 ") == 0);

    }

    TEST_CASE("Test vecAVX256f add", "[op+]") {

        vec256f addResult = vec1 + vec2;

        REQUIRE(strcmp(addResult.to_string().c_str(), "11 22 33 44 55 66 77 88 ") == 0);

        addResult = vec3 + vec4;

        REQUIRE(strcmp(addResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }
    
    TEST_CASE("Test vecAVX256f addeq", "[op+=]") {

        vec256f addeqResult = vec1;
        addeqResult += vec2;

        REQUIRE(strcmp(addeqResult.to_string().c_str(), "11 22 33 44 55 66 77 88 ") == 0);

        addeqResult = vec3;
        addeqResult += vec4;

        REQUIRE(strcmp(addeqResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }   

    TEST_CASE("Test vecAVX256f mul", "[op*]") {

        vec256f mulResult = vec1 * vec2;

        REQUIRE(strcmp(mulResult.to_string().c_str(), "10 40 90 160 250 360 490 640 ") == 0);

        mulResult = vec3 * vec4;

        REQUIRE(strcmp(mulResult.to_string().c_str(), "4 4 4 4 4 4 4 4 ") == 0);

    }   

    TEST_CASE("Test vecAVX256f div", "[op/]") {

        vec256f divResult = vec1 / vec2;

        REQUIRE(strcmp(divResult.to_string().c_str(), "10 10 10 10 10 10 10 10 ") == 0);

        divResult = vec3 / vec4;

        REQUIRE(strcmp(divResult.to_string().c_str(), "1 1 1 1 1 1 1 1 ") == 0);

    }   

#endif

#ifdef BENCHMARKS

    void sum_sets() {
	
	    float evens[] = { 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0 };
	    float odds[] = { 1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0 };
	    float result[8] = { 0 };
	
	    for (int i = 0; i != sizeof(evens) / sizeof(float); ++i) {

            result[i] = evens[i] + odds[i];
        }
	
    }

    void sum_sets_avx() {
		
	    __m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
	    __m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);
        __m256 result = _mm256_set1_ps(1.0);

	    result = _mm256_add_ps(evens, odds);
	
    }

    int main() {

        ankerl::nanobench::Bench().minEpochIterations(400000).run("sum_sets()", [&]{
        
            sum_sets();
    
            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(sum_sets);
            #endif

        });

        ankerl::nanobench::Bench().run("sum_sets_avx()", [&]{
        
            sum_sets_avx();
    
            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(sum_sets_avx);
            #endif

        });
    
    	ankerl::nanobench::Bench().minEpochIterations(1500000).run("vec256f op+", [&]{
        
    		vec256f result = vec1 + vec2;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec1 + vec2);
            #endif

        });

        ankerl::nanobench::Bench().minEpochIterations(500000).run("vecAVX256f op+", [&]{
        
    		vecAVX256f result = vec5 + vec6;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec5 + vec6);
            #endif

        });

        ankerl::nanobench::Bench().minEpochIterations(500000).run("vec256f op*", [&]{
        
    		vec256f result = vec1 * vec2;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec1 * vec2);
            #endif

        });

        ankerl::nanobench::Bench().minEpochIterations(500000).run("vecAVX256f op*", [&]{
        
    		vecAVX256f result = vec5 * vec6;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec5 * vec6);
            #endif

        });

        ankerl::nanobench::Bench().minEpochIterations(500000).run("vec256f op/", [&]{
        
    		vec256f result = vec1 / vec2;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec1 / vec2);
            #endif

        });

        ankerl::nanobench::Bench().minEpochIterations(500000).run("vecAVX256f op/", [&]{
        
    		vecAVX256f result = vec5 / vec6;

            #ifdef NOPTIMIZE
                ankerl::nanobench::doNotOptimizeAway(vec5 / vec6);
            #endif

        });

    }

#endif

#ifdef BUILD

    int main() {

        

        return 0;
    }

#endif