//
//  FNHTTPBasicAuth.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 31.05.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNHTTPAuth.h"

@interface FNHTTPBasicAuth : NSObject <FNHTTPAuth>
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *password;

#pragma mark - Factory Methods

+ (id)basicAuthWithUsername:(NSString *)username password:(NSString *)password;

#pragma mark - Initialization

- (id)initWithUsername:(NSString *)username password:(NSString *)password;

@end
