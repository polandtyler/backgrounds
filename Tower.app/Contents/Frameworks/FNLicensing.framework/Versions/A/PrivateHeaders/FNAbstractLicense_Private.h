//
//  FNAbstractLicense_Private.h
//  FNLicensing
//
//  Created by Alexander Rinass on 13/07/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <FNLicensing/FNLicensing.h>

@interface FNAbstractLicense ()
@property (nonatomic, readwrite) NSString *productName;
@property (nonatomic, readwrite) NSString *productVersion;
@property (nonatomic, readwrite) NSString *name;
@property (nonatomic, readwrite) NSString *machine;
@property (nonatomic, readwrite) NSString *expires;
@property (nonatomic, readwrite) NSDate *expirationDate;
@property (nonatomic, readwrite) NSString *type;
@property (nonatomic, readwrite) NSString *code;
@end
