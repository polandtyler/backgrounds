//
//  BeanstalkPublicKey.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 12.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BeanstalkPublicKey : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, readonly) NSInteger accountID;
@property (nonatomic, readonly) NSInteger userID;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *content;
@property (nonatomic, strong, readonly) NSDate *updatedAt;
@property (nonatomic, strong, readonly) NSDate *createdAt;

#pragma mark - Factory Methods

+ (id)publicKeyFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBeanstalkPublicKey:(BeanstalkPublicKey *)otherObject;

@end
