//
//  BeanstalkAuth.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 13.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeanstalkAuth : NSObject
@property (nonatomic, strong, readonly) NSString *account;
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *password;

#pragma mark - Factory Methods

+ (id)authWithAccount:(NSString *)account username:(NSString *)username password:(NSString *)password;

#pragma mark - Initialization

- (id)initWithAccount:(NSString *)account username:(NSString *)username password:(NSString *)password;

@end
