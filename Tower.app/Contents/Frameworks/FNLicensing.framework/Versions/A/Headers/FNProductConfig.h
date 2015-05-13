//
//  FNProductConfig.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 05.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNProductConfig : NSObject <NSCopying>
@property (nonatomic) NSString *productName;
@property (nonatomic) NSString *productVersion;
@property (nonatomic) NSString *hashingSalt;
@property (nonatomic) NSURL *licensesDirectoryURL;
@property (nonatomic, getter = isBeta) BOOL beta;
@property (nonatomic) NSString *machineUUID;
@property (nonatomic) NSString *userName;
@property (nonatomic) NSURL *licensingBaseURL;
@property (nonatomic) NSString *developerSecret;
@property (nonatomic) NSUInteger numberOfTrialDays;
@end
