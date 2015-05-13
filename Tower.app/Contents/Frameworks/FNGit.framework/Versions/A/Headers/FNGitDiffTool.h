//
//  FNGitDiffTool.h
//  FNGit
//
//  Created by Alexander Rinass on 09.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"

@class FNGitRepository;
@class FNGitDiffToolCommand;
@interface FNGitDiffTool : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *name;

/** @name Creating Diff Tool Objects */

+ (id)diffToolWithRepository:(FNGitRepository *)repository name:(NSString *)name;
- (id)initWithRepository:(FNGitRepository *)repository name:(NSString *)name command:(FNGitDiffToolCommand *)command;

/** @name Launching the Diff Tool */

- (void)launchWithRevisions:(NSArray *)revisions filePaths:(NSArray *)filePaths options:(FNGitDiffToolOptions)options completionHandler:(void (^)(NSInteger exitCode, NSError *error))completionHandler;
- (void)cancel;

@end
