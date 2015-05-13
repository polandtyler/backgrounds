//
//  BitbucketRepository.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BitbucketRepository : NSObject <NSCopying>

@property (nonatomic, readonly) NSString *slug;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *account;
@property (nonatomic, strong) NSString *scm;
@property (nonatomic, strong, readonly) NSDate *updatedAt;
@property (nonatomic, strong, readonly) NSDate *createdAt;
@property (nonatomic, strong) NSString *descr;
@property (nonatomic, getter = isPrivate) BOOL private;
@property (nonatomic, strong) NSString *forkURL;
@property (nonatomic, strong) NSString *repositoryURL;


#pragma mark - Factory Methods

+ (id)repositoryFromJSONObject:(NSDictionary *)JSONObject;

#pragma mark - Retrieving Writable JSON Properties

- (NSDictionary *)writableJSONProperties;

#pragma mark - Comparing Objects

- (BOOL)isEqualToBitbucketRepository:(BitbucketRepository *)otherObject;

- (BOOL)isGitRepository;

@end
