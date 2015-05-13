//
//  BeanstalkAccount.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 12.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeanstalkAccount : NSObject
@property (nonatomic, readonly) NSInteger accountID;
@property (nonatomic, readonly) NSInteger ownerID;
@property (nonatomic, readonly) NSInteger planID;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong, readonly) NSString *thirdLevelDomain;
@property (nonatomic, strong) NSString *timeZone;
@property (nonatomic, readonly, getter = isSuspended) BOOL suspended;
@property (nonatomic, strong, readonly) NSDate *updatedAt;
@property (nonatomic, strong, readonly) NSDate *createdAt;

#pragma mark - Factory Methods

+ (id)accountFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBeanstalkAccount:(BeanstalkAccount *)otherObject;

@end
