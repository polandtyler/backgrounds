//
//  FNProductStatus.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 07.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, FNProductStatusMode) {
    FNProductStatusModeNone,
    FNProductStatusModeBeta,
    FNProductStatusModeBetaExpired,
    FNProductStatusModeBetaClosed,
    FNProductStatusModeTrial,
    FNProductStatusModeTrialExpired,
    FNProductStatusModeLicensed
};

@class FNProductConfig;
@class FNBetaLicense;
@class FNTrialLicense;
@class FNProductLicense;
@interface FNProductStatus : NSObject
@property (nonatomic, readonly) FNProductConfig *productConfig;
@property (nonatomic, readonly) FNProductStatusMode mode;
@property (nonatomic) FNBetaLicense *betaLicense;
@property (nonatomic) FNTrialLicense *trialLicense;
@property (nonatomic) FNProductLicense *productLicense;
@property (nonatomic, readonly, getter = isWithoutStatus) BOOL withoutStatus;
@property (nonatomic, readonly, getter = isBeta) BOOL beta;
@property (nonatomic, readonly, getter = isExpiredBeta) BOOL expiredBeta;
@property (nonatomic, readonly, getter = isBetaClosed) BOOL betaClosed;
@property (nonatomic, readonly, getter = isTrial) BOOL trial;
@property (nonatomic, readonly, getter = isExpiredTrial) BOOL expiredTrial;
@property (nonatomic, readonly, getter = isLicensed) BOOL licensed;
@property (nonatomic, readonly, getter = isValid) BOOL valid;

- (id)initWithProductConfig:(FNProductConfig *)productConfig;

- (void)reloadStatus;

@end
