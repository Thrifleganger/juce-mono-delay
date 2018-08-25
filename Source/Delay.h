//
//  Delay.hpp
//  MonoDelay - Shared Code
//
//  Created by Akash Murthy on 30/12/17.
//

#ifndef Delay_hpp
#define Delay_hpp

#include <vector>

class CustomDelay {
    int writePointer{};
    int totalSampleCount;
public:
    std::vector<double> buffer;
    CustomDelay(const int maxDuration, const int sampleRate);
    void writeToDelayBuffer(const double input);
    std::vector<double>& getBuffer();
    int getTotalSampleCount() const;
    int getWritePosition() const;
};

class CustomDelayTap {
    int readPointer;
public:
    double tap(CustomDelay& delayBuffer, int position);
};

#endif /* Delay_hpp */
