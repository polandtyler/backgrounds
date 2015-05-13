//
//  FNProductLicenseFaker.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 11.03.14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNProductConfig;
@class FNBetaLicense;
@class FNTrialLicense;
@class FNProductLicense;
@interface FNLicenseGenerator : NSObject
@property (nonatomic, readonly) FNProductConfig *productConfig;

- (instancetype)initWithProductConfig:(FNProductConfig *)productConfig;

- (FNBetaLicense *)generateBetaLicenseWithExpirationDate:(NSDate *)expirationDate;
- (FNTrialLicense *)generateTrialLicenseWithExpirationDate:(NSDate *)expirationDate;
- (FNProductLicense *)generateProductLicenseWithRegistrationName:(NSString *)registrationName;

@end
