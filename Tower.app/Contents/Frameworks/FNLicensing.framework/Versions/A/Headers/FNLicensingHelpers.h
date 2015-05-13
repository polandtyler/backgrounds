//
//  FNLicensingHelpers.h
//  FNLicensing
//
//  Created by Alexander Rinass on 30/06/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNLicensingHelpers : NSObject

+ (NSString *)obfuscatedMachineUUID;
+ (NSString *)obfuscatedUserName;
+ (NSUInteger)convertTimeIntervalToDaysLeft:(NSTimeInterval)timeInterval;

+ (NSString *)legacyExpirationDateStringForExpirationDate:(NSDate *)expirationDate;
+ (NSString *)expirationDateStringForExpirationDate:(NSDate *)expirationDate;
+ (NSDate *)expirationDateForExpirationDateString:(NSString *)expirationDateString;

@end
