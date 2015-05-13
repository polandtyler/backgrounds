//
//  FNProductBeta.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 06.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import "FNAbstractLicense.h"
#import "FNProductCoupon.h"

@class FNLicenseValidator;
@interface FNBetaLicense : FNAbstractLicense
@property (nonatomic, readonly) NSString *closedStatus;
@property (nonatomic, readonly) FNProductCoupon *coupon;
@property (nonatomic, readonly, getter = isClosed) BOOL closed;

+ (instancetype)licenseWithValuesFromDictionary:(NSDictionary *)values;

@end
