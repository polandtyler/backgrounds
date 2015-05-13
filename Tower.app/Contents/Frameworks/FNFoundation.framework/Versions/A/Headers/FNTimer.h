//
//  FNTimer.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 31.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNTimer : NSObject

+ (id)timer;

- (void)start;
- (void)stop;

- (double)timeElapsedInSeconds;
- (double)timeElapsedInMilliseconds;

- (double)stopAndTimeElapsedInSeconds;
- (double)stopAndTimeElapsedInMilliseconds;

@end
