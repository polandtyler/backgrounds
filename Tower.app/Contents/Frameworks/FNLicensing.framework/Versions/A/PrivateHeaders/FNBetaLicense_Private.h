//
//  FNBetaLicense_Private.h
//  FNLicensing
//
//  Created by Alexander Rinass on 14/07/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <FNLicensing/FNLicensing.h>

@interface FNBetaLicense ()
@property (nonatomic, readwrite, getter = isClosed) BOOL closed;
@property (nonatomic, readwrite) NSString *closedStatus;
@property (nonatomic, readwrite) FNProductCoupon *coupon;
@end
