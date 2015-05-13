//
//  FNGitCommitGraphDrawerCommitLine.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNGitCommitGraphDrawerCommitLine : NSObject
@property NSUInteger lineID;
@property (nonatomic) NSString *commitHash;

#pragma mark - Factory Methods

+ (id)commitLineWithLineID:(NSUInteger)aLineID commitHash:(NSString *)aCommitHash;

#pragma mark - Initialization

- (id)initWithLineID:(NSUInteger)aLineID commitHash:(NSString *)aCommitHash;

@end
