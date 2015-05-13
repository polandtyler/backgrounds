//
//  FNProductLicense.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 07.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import "FNAbstractLicense.h"

@class FNProductLicenseValidator;
@interface FNProductLicense : FNAbstractLicense
@property (nonatomic, readonly) NSString *license;
@property (nonatomic, readonly) NSString *masked;

+ (instancetype)licenseWithValuesFromDictionary:(NSDictionary *)values;

@end
