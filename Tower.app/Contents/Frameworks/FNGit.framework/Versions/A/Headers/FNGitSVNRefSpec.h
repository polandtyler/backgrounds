//
//  FNGitSVNRefSpec.h
//  FNGit
//
//  Created by Alexander Rinass on 23.08.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNGitSVNRefSpec : NSObject <NSCopying>
@property (nonatomic) NSString *remotePath;
@property (nonatomic) NSString *localRefName;

#pragma mark - Factory Methods

+ (id)SVNRefSpecFromString:(NSString *)SVNRefSpecString;
+ (id)SVNRefSpecWithRemotePath:(NSString *)remotePath localRefName:(NSString *)localRefName;

#pragma mark - Initialization

- (id)initWithRemotePath:(NSString *)remotePath localRefName:(NSString *)localRefName;

#pragma mark - Converting to String Format

- (NSString *)stringValue;

@end
