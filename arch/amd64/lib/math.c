#include <math.h>

float32_t qrsqrtf(float32_t x){
	const float32_t threehalfs = 1.5;
	static uint32_t temp;
	static float32_t halfx;
	temp = 0x5f3759df - ((*(uint32_t*)&x) >> 1);
	halfx = x * 0.5;
	x = *(float32_t*)&temp;
	return x * (threehalfs - (halfx * x * x));
}

float64_t qrsqrtlf(float64_t x){

}
float128_t qrsqrtllf(float128_t x){
	
}
