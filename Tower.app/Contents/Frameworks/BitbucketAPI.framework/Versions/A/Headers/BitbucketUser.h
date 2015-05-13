//
//  BitbucketUser.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 12.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketUser : NSObject <NSCopying>
@property (nonatomic, readonly) NSString *username;
@property (nonatomic, readwrite) NSString *email;
@property (nonatomic, readwrite) NSString *firstName;
@property (nonatomic, readwrite) NSString *lastName;
@property (nonatomic, readwrite) NSString *displayName;
@property (nonatomic, readwrite, getter = isTeamAccount) BOOL teamAccount;
@property (nonatomic, readonly) NSString *avatarURL;

#pragma mark - Factory Methods

+ (id)userFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Init
- (id)initWithUsername:(NSString *)username;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBitbucketUser:(BitbucketUser *)otherObject;


@end
