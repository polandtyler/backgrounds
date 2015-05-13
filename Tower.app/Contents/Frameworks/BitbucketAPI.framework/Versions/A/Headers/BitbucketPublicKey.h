//
//  BitbucketPublicKey.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketPublicKey : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *content;

#pragma mark - Factory Methods

+ (id)publicKeyFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBitbucketPublicKey:(BitbucketPublicKey *)otherObject;

@end
