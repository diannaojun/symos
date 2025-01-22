#include <math.h>

float32_t absf(float32_t x){
	return (x < 0)?-x:x;
}
float32_t sqrtf(float32_t x) {
	register float32_t now = qrsqrtf(x);
	while(absf(x - now * now) > 1e-15)
		now = (now + x / now) * 0.5f;
	return now;
}
float32_t qrsqrtf(float32_t x){
	union {
        float32_t f;
        uint32_t i;
    } conv = { .f = x };
    conv.i  = 0x5f3759df - (conv.i >> 1);
	return conv.f * 1.5f - (x * 0.5f * conv.f * conv.f);
}

float64_t abslf(float64_t x){
	return (x < 0)?-x:x;
}
float64_t sqrtlf(float64_t x) {
	register float64_t now = qrsqrtlf(x);
	while(abslf(x - now * now) > 1e-15)
		now = (now + x / now) * 0.5f;
	return now;
}
float64_t qrsqrtlf(float64_t x){
	union {
        float64_t f;
        uint64_t i;
    } conv = { .f = x };
    conv.i  = 0x5fe6eb50c7aa19f9ull - (conv.i >> 1);
	return conv.f * 1.5f - (x * 0.5f * conv.f * conv.f);

}

float128_t absllf(float128_t x){
	return (x < 0)?-x:x;
}
float128_t sqrtllf(float128_t x) {
	register float128_t now = qrsqrtlf(x);
	while(absllf(x - now * now) > 1e-15)
		now = (now + x / now) * 0.5f;
	return now;
}
float128_t qrsqrtllf(float128_t x){
	return sqrtllf(x);
}
