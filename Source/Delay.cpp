//
//  Delay.cpp
//  MonoDelay - Shared Code
//
//  Created by Akash Murthy on 30/12/17.
//

#include "Delay.h"

CustomDelay::CustomDelay(const int maxDuration, const int sampleRate) {
    totalSampleCount = maxDuration * sampleRate;
    buffer.resize(totalSampleCount);
}

int CustomDelay::getTotalSampleCount() const {
    return totalSampleCount;
}

std::vector<double>& CustomDelay::getBuffer() {
    return buffer;
}

int CustomDelay::getWritePosition() const {
    return writePointer;
}

void CustomDelay::writeToDelayBuffer(const double input) {
    if(writePointer >= totalSampleCount) {
        writePointer = 0;
    }
    buffer[writePointer++] = input;
}

double CustomDelayTap::tap(CustomDelay &delayBuffer, int position) {
    if(position >= delayBuffer.getTotalSampleCount() || position < 0) {
        readPointer = 0;
    } else {
        readPointer = delayBuffer.getWritePosition() - position;
        if(readPointer < 0) {
            readPointer = delayBuffer.getTotalSampleCount() - abs(readPointer);
        }
    }
    return delayBuffer.buffer[readPointer];
}
