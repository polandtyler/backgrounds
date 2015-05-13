//
//  FNGitRefSpec.h
//  FNGit
//
//  Created by Alexander Rinass on 31.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNGitRefSpec : NSObject <NSCopying>
@property (nonatomic) NSString *localRefName;
@property (nonatomic) NSString *remoteRefName;

+ (id)refSpecFromString:(NSString *)refSpecString;
+ (id)matchingRefsRefSpec;
+ (id)deleteRefSpecWithRemoteRefName:(NSString *)remoteRefName;
+ (id)refSpecWithLocalRefName:(NSString *)localRefName;
+ (id)refSpecWithLocalRefName:(NSString *)localRefName remoteRefName:(NSString *)remoteRefName;

- (id)initWithLocalRefName:(NSString *)localRefName remoteRefName:(NSString *)remoteRefName;

- (NSString *)stringValue;

@end
