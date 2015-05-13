//
//  BeanstalkUser.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 12.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface BeanstalkUser : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger userID;
@property (nonatomic, readonly) NSInteger accountID;
@property (nonatomic, strong) NSString *login;
@property (nonatomic, strong) NSString *password;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *firstName;
@property (nonatomic, strong) NSString *lastName;
@property (nonatomic, readonly, getter = isOwner) BOOL owner;
@property (nonatomic, getter = isAdmin) BOOL admin;
@property (nonatomic, strong) NSString *timeZone;
@property (nonatomic, readonly, strong) NSDate *updatedAt;
@property (nonatomic, readonly, strong) NSDate *createdAt;

#pragma mark - Factory Methods

+ (id)userFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBeanstalkUser:(BeanstalkUser *)otherObject;

@end
