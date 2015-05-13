//
//  FNThreadSleep.h
//  FNFoundation
//
//  Created by Alexander Rinass on 19.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#if defined(DEBUG) && defined(FNTHREADSLEEP_ENABLED)
    #define FNThreadSleep(timeInterval) [NSThread sleepForTimeInterval:timeInterval]
#else
    #define FNThreadSleep(timeInterval)
#endif
