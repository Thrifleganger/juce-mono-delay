//
//  TempoController.h
//  MaximilianTest
//
//  Created by Akash Murthy on 26/12/17.
//

#ifndef TempoController_h
#define TempoController_h

#include "../JuceLibraryCode/JuceHeader.h"
class TempoController {
  
private:
    float calculateTimeFromTimeFactor(const float factor) const;
public:
    
    TempoController() {
        previousTime = Time().currentTimeMillis();
    }
    
    int64 currentTime, previousTime, timeDifference;
    int bpm{120};
    int tapBpm{120};
    int hostBpm{120};
    int generateTimeInMillisFromTimeSelection(const int timeSelection) const;
    int generateBpmFromTapTempo();
};

#endif /* TempoController_h */
