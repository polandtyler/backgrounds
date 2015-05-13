//
//  NSDate+FNCommon.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef MINUTES
    #define MINUTES 60
#endif

#ifndef HOURS
    #define HOURS (60 * MINUTES)
#endif

#ifndef DAYS
    #define DAYS (24 * HOURS)
#endif

@interface NSDate (FNCommon)

/**
 Returns a NSDate with the given number of days from now.
 */
+ (id)dateWithNumberOfDaysFromNow:(NSUInteger)numberOfDays;

/**
 Returns a NSDate with the given number of days ago.
 */
+ (id)dateWithNumberOfDaysAgo:(NSUInteger)numberOfDays;

/**
 Returns a NSDate with the given number of hours from now.
 */
+ (id)dateWithNumberOfHoursFromNow:(NSUInteger)numberOfHours;

/**
 Returns a NSDate with the given number of hours ago.
 */
+ (id)dateWithNumberOfHoursAgo:(NSUInteger)numberOfHours;

- (NSDate *)firstMomentOfDay;
- (NSDate *)lastMomentOfDay;

/**
 Returns an absolute and ceiled number of days (e.g. 0.27 days => 1 day) to the 
 given reference date.  
 */
- (NSUInteger)absoluteNumberOfDaysUntilDate:(NSDate *)anotherDate;

/**
 Returns a ceiled number of days (e.g. 0.27 days => 1 day) to the 
 given reference date.  
 */
- (NSInteger)numberOfDaysUntilDate:(NSDate *)anotherDate;

@end
