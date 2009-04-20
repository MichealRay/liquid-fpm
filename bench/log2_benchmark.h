//
//
//

#ifndef __LIQUIDFPM_LOG2_BENCHMARK_H__
#define __LIQUIDFPM_LOG2_BENCHMARK_H__

#include <sys/resource.h>
#include <math.h>

#include "liquidfpm.h"

#define DEBUG 1

void precision_log2(float * _rmse)
{
    float e, mse=0.0f;
    float dyf=0.1f, yf=-7.0f;
    float xf;
    unsigned int n=0;

    q32_t x, y;
    while (yf < 3.0f) {
        xf = powf(2.0f, yf);

        x = q32_float_to_fixed(xf);
        y = q32_log2(x);

        e = yf - q32_fixed_to_float(y);
        mse += e*e;

#if DEBUG
        printf(" log2(%12.8f) = %12.8f (%12.8f, e=%12.8f)\n",
                xf, yf, q32_fixed_to_float(y), e);
#endif

        n++;
        yf += dyf;
    }
    *_rmse = sqrtf(mse/n);
}

void benchmark_log2(struct rusage *_start,
                    struct rusage *_finish,
                    unsigned long int *_num_trials)
{
    unsigned long int i;
    q32_t x;

    // start trials
    getrusage(RUSAGE_SELF, _start);
    for (i=0; i<(*_num_trials); i++) {
        x = q32_log2(0x00000234);
        x = q32_log2(0x00083018);
        x = q32_log2(0x28591728);
        x = q32_log2(0x02850337);
    }
    getrusage(RUSAGE_SELF, _finish);

    *_num_trials *= 4;
}

#endif // __LIQUIDFPM_LOG2_BENCHMARK_H__
