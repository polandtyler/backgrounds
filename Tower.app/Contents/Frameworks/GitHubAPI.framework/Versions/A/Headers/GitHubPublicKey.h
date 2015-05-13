//
//  GitHubSSHKey.h
//  Tower
//
//  Created by Alexander Rinass on 12.04.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface GitHubPublicKey : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger publicKeyID;
@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) NSString *key;
@property (nonatomic, strong, readonly) NSString *URL;

#pragma mark - Factory Methods

+ (id)publicKeyFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable Properties as JSON

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToGitHubPublicKey:(GitHubPublicKey *)otherObject;

@end

