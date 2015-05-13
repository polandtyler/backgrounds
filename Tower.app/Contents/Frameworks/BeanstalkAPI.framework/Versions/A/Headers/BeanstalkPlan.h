//
//  BeanstalkPlan.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 12.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeanstalkPlan : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger planID;
@property (nonatomic, strong, readonly) NSString *name;
@property (nonatomic, readonly) NSInteger price;
@property (nonatomic, readonly) NSInteger repositories;
@property (nonatomic, readonly) NSInteger users;
@property (nonatomic, readonly) NSInteger servers;
@property (nonatomic, readonly) NSInteger storage;

#pragma mark - Factory Methods

+ (id)planFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBeanstalkPlan:(BeanstalkPlan *)otherObject;

@end
