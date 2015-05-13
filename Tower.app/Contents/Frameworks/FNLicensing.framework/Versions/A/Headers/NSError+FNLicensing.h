//
//  NSError+FNLicensing.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 31.10.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


extern NSString *const FNLicensingErrorDomain;


typedef NS_ENUM(NSInteger, ErrorCodes) {
	FNLicensingServerError = 1,
    FNLicensingTrialRegistrationInfoError,
    FNLicensingTrialNotExpandable,
    FNLicensingBetaRegistrationInfoError,
    FNLicensingInvalidActivationInfoError,
	FNLicensingActivationLimitReachedError,
    FNLicensingDeactivationFailedError
};


@interface NSError (FNLicensing)

+ (NSError *)serverErrorWithResponseData:(NSData *)responseData;
+ (NSError *)invalidTrialRegistrationInfo:(NSData *)responseData;
+ (NSError *)trialNotExpandable:(NSData *)responseData;
+ (NSError *)invalidBetaRegistrationInfo:(NSData *)responseData;
+ (NSError *)invalidLicenseActivationInfo:(NSString *)failureDescription;
+ (NSError *)activationLimitReachedError:(NSData *)responseData;
+ (NSError *)deactivationFailedError:(NSData *)responseData;

@end
