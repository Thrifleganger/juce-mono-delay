//
//  TempoController.cpp
//  MaximilianTest - App
//
//  Created by Akash Murthy on 26/12/17.
//

#include "TempoController.h"

int TempoController::generateTimeInMillisFromTimeSelection(const int timeSelection) const {
    switch (timeSelection) {
        case 0:
            return calculateTimeFromTimeFactor(1/4.0);
        case 1:
            return calculateTimeFromTimeFactor(1/3.0);
        case 2:
            return calculateTimeFromTimeFactor(1/2.0);
        case 3:
            return calculateTimeFromTimeFactor(1/1.5);
        case 4:
            return calculateTimeFromTimeFactor(1/1.3333333);
        case 5:
            return calculateTimeFromTimeFactor(1.0);
        case 6:
            return calculateTimeFromTimeFactor(1.33333333);
        case 7:
            return calculateTimeFromTimeFactor(1.5);
        case 8:
            return calculateTimeFromTimeFactor(2);
        case 9:
            return calculateTimeFromTimeFactor(3);
        default:
            return calculateTimeFromTimeFactor(4);
    }
}

float TempoController::calculateTimeFromTimeFactor(const float factor) const {
    return (60.0/bpm) * factor * 1000;
}

int TempoController::generateBpmFromTapTempo() {
    int tapTempo = bpm;
    currentTime = Time().currentTimeMillis();
    timeDifference = currentTime - previousTime;
    if(timeDifference < 3000) {
        tapTempo = 60.0/(timeDifference * 0.001);
    }
    previousTime = currentTime;
    return jlimit(30, 400, tapTempo);
}
