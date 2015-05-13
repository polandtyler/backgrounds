//
//  FNGitRemoteConfig.h
//  FNGit
//
//  Created by Alexander Rinass on 19.12.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@interface FNGitRemoteConfig : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *URL;
@property (nonatomic, readonly) NSString *pushURL;
@property (nonatomic, readonly) NSArray *fetchRefSpecs;
@property (nonatomic, readonly) NSArray *pushRefSpecs;
@property (nonatomic, readonly) BOOL skipsDefaultUpdate;
@property (nonatomic, readonly) BOOL skipsFetchAll;

/** @name Getting Remote Configs */

+ (NSArray *)allRemoteConfigsForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSDictionary *)allRemoteConfigsByRemoteNameForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/** @name Creating Remote Config Objects */

- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Getting Custom Values */

- (id)valueForConfigKey:(NSString *)key;

- (NSDictionary *)dictionaryRepresentation;

@end
