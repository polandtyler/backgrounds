//
//  FNProductCoupon.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 25.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface FNProductCoupon : NSObject

@property (nonatomic, readonly) NSString *couponCode;
@property (nonatomic, readonly) NSDate *couponExpires;

- (id)initWithCouponCode:(NSString *)couponCode couponExpires:(NSDate *)couponExpires;

@end
