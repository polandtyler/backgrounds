//
//  FNGitMergeCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@interface FNGitMergeCommand : FNGitCommand
@property (nonatomic, copy) NSString *revision;
@property (nonatomic) BOOL commitsChanges;
@property (nonatomic) BOOL squashesChanges;
@property (nonatomic) BOOL fastForwards;
@property (nonatomic) BOOL abortsMerge;

/** @name Creating Merge Command Objects */

+ (id)gitMergeCommandWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;
- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
