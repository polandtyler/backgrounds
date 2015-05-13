//
//  FNActivationUserInput.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 14.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNProductActivationUserInput : NSObject
@property (nonatomic, readonly) NSString *userName;
@property (nonatomic, readonly) NSString *licenseCode;

- (id)initWithUserName:(NSString *)userName licenseCode:(NSString *)licenseCode;

- (BOOL)validate;

@end
