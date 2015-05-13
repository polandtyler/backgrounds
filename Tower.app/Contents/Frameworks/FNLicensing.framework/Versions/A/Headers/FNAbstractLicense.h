//
//  FNProduct.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 06.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const FNLicenseTypeBeta;
extern NSString *const FNLicenseTypeTrial;
extern NSString *const FNLicenseTypeProductSingle;
extern NSString *const FNLicenseTypeProductMulti;

@interface FNAbstractLicense : NSObject
@property (nonatomic, readonly) NSString *productName;
@property (nonatomic, readonly) NSString *productVersion;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *machine;
@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *code;
@property (nonatomic, readonly) NSString *expires;
@property (nonatomic, readonly) NSDate *expirationDate;
@property (nonatomic, readonly) NSTimeInterval timeLeft;
@property (nonatomic, readonly, getter = isExpired) BOOL expired;

- (void)setValuesFromDictionary:(NSDictionary *)values;

- (NSDictionary *)dictionaryRepresentation;

@end
