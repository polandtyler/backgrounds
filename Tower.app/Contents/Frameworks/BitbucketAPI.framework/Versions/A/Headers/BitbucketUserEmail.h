//
//  BitbucketEmail.h
//  BitbucketAPI
//
//  Created by Marc Beyerlin on 13.05.14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketUserEmail : NSObject
@property (nonatomic, readonly) NSString *email;
@property (nonatomic, readonly) BOOL active;
@property (nonatomic, readonly) BOOL primary;

#pragma mark - Factory Methods

+ (id)userEmailFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Init
- (id)initWithUserEmail:(NSString *)email;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBitbucketUserEmail:(BitbucketUserEmail *)otherObject;

@end
